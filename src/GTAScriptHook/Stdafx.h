// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <windows.h>

#if GTA_III | GTA_VC | GTA_SA
#define GTA_SCM 1
#else
#define GTA_SCO 1
#endif

using namespace System;
using namespace System::Collections::Generic;

#ifdef GTA_IV
#pragma unmanaged
#include "../ScriptHook/ScriptThread.h"
#include "../ScriptHook/NativeInvoke.h"
#include "../ScriptHook/NativeContext.h"
#include "../ScriptHook/Game.h"
#include "../ScriptHook/GameTypes.h"
#include "../ScriptHook/ScriptingHelpers.h"
#pragma managed
#endif

namespace GTA {
	public ref class SVector {
	public:
		float pX, pY, pZ;

		SVector(float X, float Y, float Z) : pX(X), pY(Y), pZ(Z) { } 
	};
}