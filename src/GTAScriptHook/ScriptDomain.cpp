#include "Stdafx.h"
#include "ScriptDomain.h"
#include "Log.h"

using namespace System::Security;

namespace GTA {
	void ScriptDomain::MarshalInDefaultDomain(CrossAppDomainDelegate^ delegat) {
		_mainDomain->DoCallBack(delegat);
	}

	void ScriptDomain::LoadMe() {
		Log::Debug("ScriptDomain::LoadMe from " + AppDomain::CurrentDomain->FriendlyName);
		AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&ScriptLoader::ResolveAssembly);
	}

	void ScriptDomain::Recreate() {
		if (AppDomain::CurrentDomain->FriendlyName == "GTAScriptHook") {
			Log::Error("VERY BAD ERROR: destroying our current code. crash will come pick us up");
		}

		Log::Debug("Going to unload our AppDomain");
		AppDomain::Unload(_scriptDomain);
		Log::Debug("Unloaded AppDomain");
		CreateDomain();
	}

	void ScriptDomain::CreateDomain() {
		Log::Debug("Creating AppDomain");

		_mainDomain = AppDomain::CurrentDomain;

		AppDomainSetup^ domainSetup = gcnew AppDomainSetup();
		domainSetup->ApplicationBase = AppDomain::CurrentDomain->BaseDirectory;
		System::Security::NamedPermissionSet^ namedPermissionSet = Policy::PolicyLevel::CreateAppDomainLevel()->GetNamedPermissionSet("FullTrust");

		_scriptDomain = AppDomain::CreateDomain("GTAScriptHook", nullptr, domainSetup, namedPermissionSet);
		_scriptDomain->InitializeLifetimeService();

		_scriptDomain->AssemblyResolve += gcnew ResolveEventHandler(&ScriptLoader::ResolveAssembly);

		DomainThingy^ thingy = (DomainThingy^)_scriptDomain->CreateInstanceAndUnwrap(Assembly::GetExecutingAssembly()->FullName, DomainThingy::typeid->FullName);
		thingy->SetMainDomain(_mainDomain);

		//return _scriptDomain;
	}

	ScriptLoader^ ScriptDomain::CreateScriptLoader() {
		ScriptLoader^ loader = nullptr;

		try {
			loader = (ScriptLoader^)_scriptDomain->CreateInstanceAndUnwrap(Assembly::GetExecutingAssembly()->FullName, ScriptLoader::typeid->FullName);
		} catch (Exception^ e) {
			Log::Error(e);
			return nullptr;
		}

		loader->GameInitialized = _initedOnce;
		_initedOnce = true;

		_loader = loader;

		return _loader;
	}

	void DomainThingy::SetMainDomain(AppDomain^ domain) {
		ScriptDomain::_mainDomain = domain;
	}
}	