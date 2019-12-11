#include "stdafx.h"
#include "Log.h"
#include "GameVersion.h"
#include "ScriptProcessor.h"
#include "ScriptLoader.h"
#include "TextHook.h"
#include "Pool.h"
#include "ScriptDomain.h"

using namespace System::Reflection;

String^ GetBuildVersion(Version^ versionID) {
	String^ time = "";

	try {
		String^ buildTime = versionID->Revision.ToString();
		String^ hour = buildTime->Substring(0, 2);
		String^ minute = buildTime->Substring(2);

		time = String::Format(" {0}:{1}", hour, minute);
	} catch (Exception^) {}

	return String::Format("{0}-{1}-{2}{3}", versionID->Major, versionID->Minor, versionID->Build, time);
}

void GoManaged() {
	// needed, since the game state does not allow initializing GDI+ any later
	Drawing::Bitmap^ bmp = gcnew Drawing::Bitmap(1, 1);

	// we're really managed now :)

	GTA::Log::Initialize("GTAScriptHook.log", GTA::LogLevel::Debug | GTA::LogLevel::Info | GTA::LogLevel::Warning | GTA::LogLevel::Error, true);
	GTA::Log::Info("DBNetwork GTA .NET Scripting API (built on " + GetBuildVersion(Assembly::GetCallingAssembly()->GetName()->Version) + ")");
#ifdef GTA_SA
	GTA::Log::Info("compiled for GTA: San Andreas");
#endif
#ifdef GTA_III
	GTA::Log::Info("compiled for GTA III");
#endif
#ifdef GTA_IV
	GTA::Log::Info("compiled for GTA IV");
#endif

	GTA::GameVersion::Detect();
	GTA::Log::Info("Game version: " + GTA::GameVersion::VersionName);

	DWORD oldProtect;
	VirtualProtect((LPVOID)0x401000, 0x4A3000, PAGE_EXECUTE_READWRITE, &oldProtect);

	AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&GTA::ScriptLoader::ResolveAssembly);

	//GTA::ScriptProcessor::Initialize();
	GTA::ScriptProcessor::Hook();
	GTA::ScriptDomain::CreateDomain();
	GTA::ScriptLoader^ loader = GTA::ScriptDomain::CreateScriptLoader();
	loader->Initialize();

	try {
		loader->LoadScripts();
	} catch (Exception^ e) {
		GTA::Log::Error(e);
	}

	//GTA::Pool::InitializeDefault();

	Sleep(1000); // make sure we are last to hook the GXT functions
	GTA::TextHook::Install();
}

#pragma unmanaged

// function to help with some stuff that comes with CLR init
DWORD GoUnmanaged() {
	GoManaged();
	return 0;
}

// DllMain, initializes the managed thread
BOOL APIENTRY DllMain (HINSTANCE hInstance, DWORD reason, LPVOID reserved) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			DWORD threadID = 0;
			HANDLE threadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GoUnmanaged, 0, 0, &threadID);

			if (threadHandle == 0 || threadHandle == INVALID_HANDLE_VALUE) {
				return false;
			}

			CloseHandle(threadHandle);
		break;
	}

	return true;
}