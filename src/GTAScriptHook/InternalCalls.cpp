#include "stdafx.h"
#include "internalcalls.h"
#include "GTAUtils.h"
#include "Log.h"
#include "GameVersion.h"

BYTE ScriptBuf[384];

#ifdef GTA_III
#pragma unmanaged
int ExecuteBuffer(BYTE *sbuf, DWORD *lvars, DWORD buflen, int gameVersion)
{
	DWORD ProcessOneCommand = 0x439440;

	GTA3_SCRIPT_THREAD gst, *pGst;

	//logbuffer(sbuf, buflen);

	ZeroMemory(&gst, sizeof(gst));
	//gst.bUnknown = 0xFF;
	gst.bStartNewScript = 1;
	//gst.dwBaseIP = (DWORD) sbuf;
	gst.dwScriptIP = (DWORD) (((int)sbuf) - 0x74B248);
	gst.strName[0] = 'n';
	gst.strName[1] = 'e';
	gst.strName[2] = 't';
	gst.strName[3] = '\0';
	memcpy(gst.dwLocalVar, lvars, 16 * sizeof(DWORD));
	pGst = &gst;
	__asm {
		push ecx
		mov ecx, dword ptr pGst
		call ProcessOneCommand
		pop ecx
	}
	memcpy(lvars, gst.dwLocalVar, 16 * sizeof(DWORD));
	return gst.bJumpFlag;
}
#pragma managed
#endif

#ifdef GTA_SA
#pragma unmanaged
int ExecuteBuffer(BYTE *sbuf, DWORD *lvars, DWORD buflen, int gameVersion)
{
	LPVOID ProcessOneCommand = (LPVOID)0x469F00;

	if (gameVersion == 101 || gameVersion == 200) {
		ProcessOneCommand = (LPVOID)0x469F80;
	}

	GTASA_SCRIPT_THREAD gst, *pGst;

	//logbuffer(sbuf, buflen);

	ZeroMemory(&gst, sizeof(gst));
	gst.bUnknown = 0xFF;
	gst.bStartNewScript = 1;
	gst.dwBaseIP = (DWORD) sbuf;
	gst.dwScriptIP = (DWORD) sbuf;
	gst.strName[0] = 'n';
	gst.strName[1] = 'e';
	gst.strName[2] = 't';
	gst.strName[3] = '\0';
	memcpy(gst.dwLocalVar, lvars, 32 * sizeof(DWORD));
	pGst = &gst;
	__asm {
		push ecx
		mov ecx, dword ptr pGst
		call ProcessOneCommand
		pop ecx
	}
	memcpy(lvars, gst.dwLocalVar, 32 * sizeof(DWORD));
	return gst.bJumpFlag;
}
#pragma managed
#endif

namespace GTA {
	namespace Internal {
#ifdef GTA_SCO
		static Function::Function() {
			_typeHandlers = gcnew Dictionary<Type^, Func<Object^, Object^>^>();
		}

		generic <typename TReturn>
		TReturn Function::Call(String^ identifier, ... cli::array<GTA::Internal::Parameter,1> ^parameters) {
			Object^ retval = Call(identifier, TReturn::typeid, parameters);

			// ask the type handler
			if (_typeHandlers->ContainsKey(TReturn::typeid)) {
				return (TReturn)_typeHandlers[TReturn::typeid](retval);
			}

			return (TReturn)retval;
		}

		generic <typename TReturn>
		TReturn Function::CallResult(String^ identifier, ... cli::array<GTA::Internal::Parameter,1> ^parameters) {
			Object^ retval = CallResult(identifier, TReturn::typeid, parameters);

			// ask the type handler
			if (_typeHandlers->ContainsKey(TReturn::typeid)) {
				return (TReturn)_typeHandlers[TReturn::typeid](retval);
			}

			return (TReturn)retval;
		}

		Object^ Function::CallResult(String^ identifier, Type^ returnType, ... cli::array<Parameter>^ parameters) {
			CallRaw(identifier, parameters);

			Object^ retval = nullptr;
			if (returnType == bool::typeid) {
				retval = curCxt->GetResult<bool>();
			} else if (returnType == int::typeid) {
				retval = curCxt->GetResult<int>();
			} else if (returnType == float::typeid) {
				retval = curCxt->GetResult<float>();
			} else if (returnType == String::typeid) {
				retval = gcnew String(curCxt->GetResult<char*>());
			} else {
				retval = curCxt->GetResult<int>();
			}

			return retval;
		}

		Object^ Function::Call(String^ identifier, Type^ returnType, ... cli::array<Parameter>^ parameters) {
			int pi = parameters->Length;
			Array::Resize(parameters, parameters->Length + 1);

			parameters[pi] = gcnew VarPointer();

			CallRaw(identifier, parameters);

			return ((VarPointer^)parameters[pi]._preVal)->Value;
		}

		bool Function::Call(String^ identifier, ... cli::array<Parameter>^ parameters) {
			return CallRaw(identifier);
		}

		generic <typename TReturn>
		TReturn Function::CallResult(unsigned int identifier, ... cli::array<GTA::Internal::Parameter,1> ^parameters) {
			return (TReturn)0;
		}

		generic <typename TReturn>
		TReturn Function::Call(unsigned int identifier, ... cli::array<GTA::Internal::Parameter,1> ^parameters) {
			return (TReturn)0;
		}

		bool Function::Call(unsigned int identifier, ... cli::array<Parameter>^ parameters) {
			// todo: native-to-GTA3 mappings
			return false;
		}

		void Function::RegisterType(Type^ type, Func<Object^, Object^>^ handler) {
			_typeHandlers->Add(type, handler);
		}

		bool Function::CallRaw(String^ identifier, ... cli::array<GTA::Internal::Parameter,1> ^parameters) {
			NativeContext cxt;

			for each (Parameter param in parameters) {
				if (param._preVal->GetType() == float::typeid) {
					cxt.Push<float>((float)param._preVal);
				} else if (param._preVal->GetType() == int::typeid) {
					cxt.Push<int>((int)param._preVal);
				} else if (param._preVal->GetType() == String::typeid) {
					// TODO: clean up nicely
					cxt.Push<char*>((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi((String^)param._preVal).ToPointer());
				} else if (param._isPointer) {
					cxt.Push<void*>(((VarPointer^)param._preVal)->CreatePointer());
				} else if (param._preVal->GetType() == SVector::typeid) {
					SVector^ vec = (SVector^)param._preVal;
					cxt.Push<float>(vec->pX);
					cxt.Push<float>(vec->pY);
					cxt.Push<float>(vec->pZ);
				}
			}
			
			IntPtr idptr = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(identifier);
			NativeInvoke::Invoke(&cxt, (char*)idptr.ToPointer());
			Runtime::InteropServices::Marshal::FreeHGlobal(idptr);

			curCxt = &cxt;

			return cxt.GetResult<bool>();
		}
#endif
		Parameter::Parameter(int value) {
			_preVal = value;
			_dataType = 2;
			_isPointer = false;

			Byte b0 = (Byte)value;
			Byte b1 = (Byte)(value >> 8);
			Byte b2 = (Byte)(value >> 16);
			Byte b3 = (Byte)(value >> 24);

			_internalArray = gcnew cli::array<unsigned char>(5) { 0x01, b0, b1, b2, b3 }; // 0x01 -> type 32-bit int
		}

		Parameter::Parameter(cli::array<Byte>^ value) {
			_preVal = value;
			_isPointer = false;

			_internalArray = value;
		}

		Parameter::Parameter(float value) {
			_preVal = value;
			_isPointer = false;
			_dataType = 3;

#if !GTA_III
			// this is not an int, this is just to be able to access it as an int
			int valueC = GTAUtils::ConvertFloatAsInt(value);

			Byte b0 = (Byte)valueC;
			Byte b1 = (Byte)(valueC >> 8);
			Byte b2 = (Byte)(valueC >> 16);
			Byte b3 = (Byte)(valueC >> 24);

			_internalArray = gcnew cli::array<unsigned char>(5) { 0x06, b0, b1, b2, b3 }; // 0x06 -> type float
#else
			// and GTA III has its own tiny fixed float. another change made between III and VC.
			short valueC = (short)(value * 16.0f);

			Byte b0 = (Byte)valueC;
			Byte b1 = (Byte)(valueC >> 8);

			_internalArray = gcnew cli::array<unsigned char>(3) { 0x06, b0, b1 }; // 0x06 still is 'float'
#endif
		}

		Parameter::Parameter(VarPointer^ value) {
			_isPointer = true;
			_preVal = value;
			_dataType = 4;
			_internalArray = gcnew cli::array<unsigned char>(3) { 0x03, 0, 0 };
		}

		int Parameter::ApplyPointer(unsigned short id) {
			if (!_isPointer) {
				return 0;
			}

			Byte b0 = (Byte)id;
			Byte b1 = (Byte)(id >> 8);

			_internalArray = gcnew cli::array<unsigned char>(3) { 0x03, b0, b1 };

			return ((VarPointer^)_preVal)->Value;
		}

#if GTA_SCM
		Parameter::Parameter(GlobalVariable^ value) {
			_isPointer = false;
			_preVal = value;
			_dataType = 6;

			unsigned short id = (value->ID * 4);

			Byte b0 = (Byte)id;
			Byte b1 = (Byte)(id >> 8);

			_internalArray = gcnew cli::array<unsigned char>(3) { 0x02, b0, b1 };
		}
#endif

		Parameter::Parameter(String^ value) {
			_isPointer = false;
			_preVal = value;
			_dataType = 1;
#if GTA_SCM && !GTA_SA
			_internalArray = Text::Encoding::ASCII->GetBytes(value->PadRight(8, '\0'));
#else
			_internalArray = gcnew cli::array<unsigned char>(value->Length + 2) { 0x0E };
			_internalArray[1] = value->Length;
			cli::array<unsigned char>^ text = Text::Encoding::ASCII->GetBytes(value);
			Array::Copy(text, 0, _internalArray, 2, value->Length);
#endif
		}

#ifdef GTA_SCM
		static Function::Function() {
			_typeHandlers = gcnew Dictionary<Type^, Func<Object^, Object^>^>();
		}

		bool Function::Call(unsigned int identifier, ... cli::array<GTA::Internal::Parameter,1> ^parameters) {
			return CallRaw(identifier, parameters);
		}

		generic <typename TReturn>
		TReturn Function::Call(unsigned int identifier, ... cli::array<GTA::Internal::Parameter,1> ^parameters) {
			Object^ retval = Call(identifier, TReturn::typeid, parameters);

			// ask the type handler
			if (_typeHandlers->ContainsKey(TReturn::typeid)) {
				return (TReturn)_typeHandlers[TReturn::typeid](retval);
			}

			return (TReturn)retval;
		}

		Object^ Function::Call(unsigned int identifier, Type^ returnType, ... cli::array<Parameter>^ parameters) {
			//int ptrCount = 1;
			/*
			if (returnType == Vector3::typeid) {

			}
			*/

			int pi = parameters->Length;
			Array::Resize(parameters, parameters->Length + 1);

			parameters[pi] = gcnew VarPointer();
			CallRaw(identifier, parameters);

			//if (ptrCount == 1) {
			return ((VarPointer^)parameters[pi]._preVal)->Value;
			/*} else {
			pi = parameters->Length;
			
			for (; (pi - parameters->Length) < ptrCount; pi++) {
				parameters[pi]->Value;
			}
			}*/

			return nullptr;
		}

		void Function::RegisterType(Type^ type, Func<Object^, Object^>^ handler) {
			_typeHandlers->Add(type, handler);
		}

		bool Function::CallRaw(unsigned int identifier, ... cli::array<GTA::Internal::Parameter,1> ^parameters) {
#ifdef GTA_SCM
			unsigned short scmid = (unsigned short)identifier;

			memset(&ScriptBuf, 0, sizeof(ScriptBuf));
			memcpy(&ScriptBuf, &scmid, 2);
			
			int buf_pos = 2;
			int var_id = 0;
			DWORD LocalVars[32];
			DWORD wait0 = 0x40001U;	// don't know why, but the example code used this.
									// might be to make the game immediately execute the code?
			memset(&LocalVars, 0, sizeof(DWORD) * 32);

			for each (Parameter parameter in parameters) {
				if (parameter._isPointer) {
					LocalVars[var_id] = parameter.ApplyPointer(var_id++);
				}

				size_t length = parameter._internalArray->Length;
				pin_ptr<unsigned char> bytes = &parameter._internalArray[0];
				memcpy(&ScriptBuf[buf_pos], (void*)bytes, length);
				buf_pos += length;

				/*
				// safe way, but slower
				for each (unsigned char byte in parameter._internalArray) {
					ScriptBuf[buf_pos] = byte;
					buf_pos++;
				}
				*/
			}

			memcpy(&ScriptBuf[buf_pos], &wait0, 4); // coincidence: it will end up with 00 01 04 00
			buf_pos += 4;

			/*String^ output = "Script buffer: ";

            for (int i = 0; i < buf_pos; i++) {
                    output += ScriptBuf[i].ToString("X2") + " ";
            }

            Log::Debug(output);*/

			int result = ExecuteBuffer(ScriptBuf, LocalVars, buf_pos, GameVersion::VersionNumber);

			if (var_id == 0) {
				return (result == 1);
			}

			var_id = 0;

			for each (Parameter parameter in parameters) {
				if (parameter._isPointer) {
					VarPointer^ pointer = (VarPointer^)parameter._preVal;

					pointer->Value = LocalVars[var_id];
					var_id++;
				}
			}

			return (result == 1);
#endif
		}

		DWORD* GlobalVariable::GetAddress() {
#if GTA_SA
			DWORD* baseAddress = (DWORD*)0xA49960;

			if (GameVersion::VersionNumber == 101 || GameVersion::VersionNumber == 200) {
				baseAddress = (DWORD*)0xA4BFE0;
			}
#endif
#if GTA_III
			DWORD* baseAddress = (DWORD*)0x74B248;
#endif

			baseAddress += ID;

			return baseAddress;
		}

		String^ GlobalVariable::ToString() {
			return "$" + ID.ToString();
		}

		int GlobalVariable::Value::get() {
			return *(GetAddress());
		}

		void GlobalVariable::Value::set(int value) {
			DWORD* ad = GetAddress();

			*ad = value;
		}
#endif
	}
}