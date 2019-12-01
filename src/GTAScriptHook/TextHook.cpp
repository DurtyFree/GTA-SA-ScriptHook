#include "Stdafx.h"
#include "TextHook.h"
#include "GameVersion.h"
#include "Hooking.h"
#include "GTAUtils.h"
#include "ScriptLoader.h"
#include "ScriptDomain.h"
#include "Log.h"

StompHook readGXTHook;
#if GTA_SA
const char* gxtRes = NULL;
#else
const wchar_t* gxtRes = NULL;
#endif

namespace GTA {
	static bool inTextHook = false;

	void __stdcall GetGXTString(const char* string) {
		//return TextHook::GetString(string);
		try {
			gxtRes = ScriptDomain::Loader->ProxyGetString(string);
		} catch (Runtime::Remoting::RemotingException^) {
			gxtRes = NULL;
		}
	}

#pragma unmanaged
	static void __declspec(naked) gxtHookReturn()
	{
		__asm {
#if GTA_SA
			sub esp, 32
			push esi
			push edi
#endif
#if GTA_III
			push ebx
			push esi
			sub esp, 32
#endif
			jmp eax
		}
	}

	static void __declspec(naked) gxtHookStub()
	{
		__asm {
			mov eax, dword ptr [esp + 8]
			test eax, eax
			jz short l1
			push ecx
			push eax
			call GetGXTString
			pop ecx
			mov eax, gxtRes
			test eax, eax
			jz short l1
			add esp, 4
			ret 4
	l1:
			pop eax
			jmp gxtHookReturn
		}
	}

#pragma managed

	void TextHook::Initialize() {
		if (_accessFunctions == nullptr) {
				_accessFunctions = gcnew List<Func<String^, String^>^>();
		}

		if (_filterFunctions == nullptr) {
				_filterFunctions = gcnew List<Func<String^, String^>^>();
		}

		_keyCache = gcnew Dictionary<String^, IntPtr>();
		_textMemory = 0;
	}

	void TextHook::Install() {
		// patch the memory
#if GTA_SA
		PBYTE location = (PBYTE)0x6A0050;

		if (GameVersion::VersionNumber == 101 || GameVersion::VersionNumber == 200) {
			return;
		}
#endif
#if GTA_III
		PBYTE location = (PBYTE)0x52BFB0;
#endif

#if GTA_SA | GTA_III
		BYTE originalCode[5];
		memset(&originalCode, 0, 5);
		memcpy(&originalCode, location, 5);

		GTAUtils::RebaseNearOpcode(originalCode, location, (PBYTE)&gxtHookReturn);

		DWORD oldProtect;
		VirtualProtect(&gxtHookReturn, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(&gxtHookReturn, &originalCode, 5);
		VirtualProtect(&gxtHookReturn, 5, oldProtect, &oldProtect);

		readGXTHook.initialize("aaaaa", 5, location);
		readGXTHook.installHook(gxtHookStub, false, true);
#endif
	}

#pragma unmanaged
	const char* CallOriginalGXT(const char* key, int _VersionNumber) {
		char* retval = NULL;

#ifdef GTA_SA
		DWORD function = 0x6A0050;
		DWORD classn = 0xC1B340;
#endif
#if GTA_III
		DWORD function = 0x52C5A0;
		DWORD classn = 0x941520;
#endif

#if GTA_SA | GTA_III
		if (_VersionNumber == 101 || _VersionNumber == 200) {
			return NULL;
		}

		_asm {
			push dword ptr key
			mov ecx, classn
			call dword ptr function
			mov retval, eax
		}
#endif

		return retval;
	}
#pragma managed

	String^ TextHook::Get(String^ label) {
		return gcnew String(CallOriginalGXT((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(label).ToPointer(), GameVersion::VersionNumber));
	}

	void TextHook::RemoveCache(String^ name) {
		if (_keyCache->ContainsKey(name)) {
			//int len = strlen((char*)_keyCache[name].ToPointer());

			Runtime::InteropServices::Marshal::FreeHGlobal(_keyCache[name]);
			_keyCache->Remove(name);

			//_textMemory -= len + 1;
		}
	}

#if GTA_SA
	const char* TextHook::GetString(const char* string) {
#else
	const wchar_t* TextHook::GetString(const char* string) {
#endif
		//Log::Debug(gcnew String(string));
		if (inTextHook) {
			return NULL;
		}

		inTextHook = true;

		String^ name = gcnew String(string);
		name = name->Trim();

		String^ retval = "";

		if (name == "_TMEMO") {
			retval = "Text memory: " + (_textMemory / 1024.0f).ToString("F4") + "K";
		}

		if (!_keyCache->ContainsKey(name)) {
			// check who knows this string
			for each (Func<String^, String^>^ function in _accessFunctions) {
				String^ val = function(name);

				if (val != nullptr) {
					//return (char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(retval).ToPointer();
					retval = val;
					break;
				}
			}

			if (retval == "") {
#if GTA_SA
				const char* val = CallOriginalGXT(string, GameVersion::VersionNumber);

				if (val == NULL) { inTextHook = false; return NULL; }

				retval = gcnew String(val);
#else
				inTextHook = false; return NULL;
#endif
			}

			for each (Func<String^, String^>^ function in _filterFunctions) {
				retval = function(retval);
			}

			inTextHook = false;

#if GTA_SA
			IntPtr rvalue = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(retval);
			_keyCache->Add(name, rvalue);

			//_textMemory += retval->Length + 1;

			return (char*)rvalue.ToPointer();
#else
			IntPtr rvalue = Runtime::InteropServices::Marshal::StringToHGlobalUni(retval);
			_keyCache->Add(name, rvalue);

			//_textMemory += retval->Length + 1;

			return (wchar_t*)rvalue.ToPointer();
#endif
		}

		IntPtr value = _keyCache[name];

		inTextHook = false;

		if (value == IntPtr::Zero) {
#if GTA_SA
			return "";
#else
			return L"";
#endif
		}

#if GTA_SA
		return (char*)value.ToPointer();
#else
		return (wchar_t*)value.ToPointer();
#endif
	}
}