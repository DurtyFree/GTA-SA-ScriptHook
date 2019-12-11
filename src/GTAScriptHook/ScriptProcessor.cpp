#include "stdafx.h"
#include "gameversion.h"
#include "ScriptProcessor.h"
#include "ScriptLoader.h"
#include "ScriptDomain.h"
#include "Log.h"
#include "Hooking.h"

#ifndef GTA_SCO
CallHook scriptTickHook;
CallHook gameInitHook;
CallHook gameInitHookRe;
CallHook gameInitHook3;

bool gameInitialized = false;
int gameStarted = 0;
#endif

using namespace System::Threading;

namespace GTA {
#ifdef GTA_SCM
	void __stdcall ScriptTickHandler(DWORD timerDelta) {
		//ScriptProcessor::Instance->Tick(timerDelta);
		ScriptDomain::Loader->ProxyTick(timerDelta);
	}

	void KillAll(Object^ state) {
		//try {
			Log::Info("Game is reloading: reloading all scripts");

			ScriptDomain::Loader->UnloadScripts();
			ScriptDomain::Recreate();

			GTA::ScriptLoader^ loader = GTA::ScriptDomain::CreateScriptLoader();
			loader->Initialize();

			try {
				loader->LoadScripts();
			} catch (Exception^ e) {
				GTA::Log::Error(e);
			}
		/*} catch (Exception^ ex) {
			GTA::Log::Error(ex);
		}*/

		gameInitialized = false;
	}

	void __stdcall GameInitializeHandler() {
		if (gameInitialized) {
			/*ThreadPool::QueueUserWorkItem(gcnew WaitCallback(&KillAll));

			while (gameInitialized) {
				Thread::Sleep(1);
			}*/
			KillAll(nullptr);
		}

		gameInitialized = true;
	}

	void __stdcall GameInitializeHandler3() {
		if (gameStarted > 3) {
			KillAll(nullptr);
		}
	}

	#pragma unmanaged
	static void __declspec(naked) scriptHandlerStub()
	{
		__asm {
			push dword ptr [esp + 20]
			push scriptTickHook.pOriginal
			jmp ScriptTickHandler
		}
	}

	static void __declspec(naked) gameInitStub()
	{
		__asm {
			pushad
			call GameInitializeHandler
			popad
			jmp gameInitHook.pOriginal
		}
	}

	static void __declspec(naked) gameInitStubRe()
	{
		__asm {
			pushad
			call GameInitializeHandler
			popad
			jmp gameInitHookRe.pOriginal
		}
	}

	static void __declspec(naked) gameInitStub3()
	{
		__asm {
			pushad
			call GameInitializeHandler3
			popad
			jmp gameInitHook3.pOriginal
		}
	}
	#pragma managed
#endif

	void ScriptProcessor::UnloadScripts() {
		for each (ScriptContext^ script in _scripts) {
			script->Clean();
		}

		_scripts->Clear();
	}

	void ScriptProcessor::AddScript(BaseScript^ script) {
		if (!_inLock) {
			_scripts->Add(gcnew ScriptContext(script));
		} else {
			ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &ScriptProcessor::WaitForAddScript), script);
		}
	}

	void ScriptProcessor::WaitForAddScript(Object^ script) {
		while (_inLock) {
			Thread::Sleep(0);
		}

		AddScript((BaseScript^)script);
	}

	void ScriptProcessor::Hook() {
#ifdef GTA_SA
		BYTE* patchAddress = (BYTE*)0x46A22E;

		if (GameVersion::VersionNumber == 101 || GameVersion::VersionNumber == 200) {
			patchAddress = (BYTE*)0x46A2AE;
		}

		scriptTickHook.initialize("\xE8\xCD\x6A\x12", patchAddress);
		scriptTickHook.installHook(scriptHandlerStub, true);

		gameInitHook.initialize("aaaa", (PBYTE)0x53BCC4);
		gameInitHook.installHook(gameInitStub, true);

		gameInitHookRe.initialize("aaaa", (PBYTE)0x53BE88);
		gameInitHookRe.installHook(gameInitStubRe, true);

		//gameInitHook.initialize("aaaa", (PBYTE)0x5BA340);
		//gameInitHook.installHook(gameInitStub, true);

		//gameInitHookRe.initialize("aaaa", (PBYTE)0x53BDD7);
		//gameInitHookRe.installHook(gameInitStubRe, true);

		// and for save loading, this one
		gameInitHook3.initialize("aaaa", (PBYTE)0x5D18F0);
		gameInitHook3.installHook(gameInitStub3, true);
#endif
#if GTA_III
		//scriptTickHook.initialize("aaaa", (PBYTE)0x4390B1);
		scriptTickHook.initialize("aaaa", (PBYTE)0x48C8FA);
		scriptTickHook.installHook(scriptHandlerStub, true);

		gameInitHook.initialize("aaaa", (PBYTE)0x48C26B);
		gameInitHook.installHook(gameInitStub, true);

		gameInitHookRe.initialize("aaaa", (PBYTE)0x48C575);
		gameInitHookRe.installHook(gameInitStubRe, true);
#endif
	}

	void ScriptProcessor::CheckKeys() {
		for (int x = 0; x < 256; x++) {
			_keys[x] = (char) (GetAsyncKeyState(x) >> 8);
		}
	}

	void ScriptProcessor::Tick(DWORD timerDelta) {
		CheckKeys();
		List<ScriptContext^>^ toRemove = gcnew List<ScriptContext^>();

		_inLock = true;
		for each (ScriptContext^ script in _scripts) {
			script->WakeUp();

			if (script->_endNext) {
				toRemove->Add(script);
			}
		}
		_inLock = false;

		for each (ScriptContext^ script in toRemove) {
			script->Clean();
			_scripts->Remove(script);
		}

		if (gameStarted < 10) {
			gameStarted++;
		}

		RawTick(timerDelta);
	}
}