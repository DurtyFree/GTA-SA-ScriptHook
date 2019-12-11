#include "Stdafx.h"
#include "Script.h"
#include "InternalCalls.h"
#include "ScriptLoader.h"
#include "ScriptProcessor.h"
#include "TextHook.h"
#include "Log.h"
#include "Pool.h"
#include "GameVersion.h"

using namespace System::IO;
extern bool gameInitialized;

namespace GTA {
	Assembly^ ScriptLoader::ResolveAssembly(Object^ sender, ResolveEventArgs^ args) {
		if (args->Name->Contains("GTAScriptHook")) {
			Log::Debug("oh, somebody asked for us. let's return 'us'.");
			return Assembly::GetExecutingAssembly();
		}

		for each (Assembly^ assembly in AppDomain::CurrentDomain->GetAssemblies()) {
			if (assembly->FullName == args->Name) {
				Log::Debug("found assembly " + assembly->FullName);
				return assembly;
			}
		}

		for each (String^ file in Directory::GetFiles(Environment::ExpandEnvironmentVariables("%temp%\\GTAScriptHook"))) {
			try {
				String^ name = FileInfo(file).FullName;

				if (AssemblyName::GetAssemblyName(name)->FullName == args->Name) {
					return Assembly::LoadFile(name);
				}
			} catch (Exception^) {
				// nothing
			}
		}

		for each (String^ file in Directory::GetFiles("scripts")) {
			try {
				String^ name = FileInfo(file).FullName;

				if (AssemblyName::GetAssemblyName(name)->FullName == args->Name) {
					return Assembly::LoadFile(name);
				}
			} catch (Exception^) {
				// nothing
			}
		}

		return nullptr;
	}

	bool ScriptLoader::GameInitialized::get() {
		return _gameInitialized;
	}

	void ScriptLoader::GameInitialized::set(bool value) {
		_gameInitialized = value;
	}

	void ScriptLoader::Initialize() {
		_rootDirectory = Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location);

		Log::Initialize("GTAScriptHook.log", GTA::LogLevel::Debug | GTA::LogLevel::Info | GTA::LogLevel::Warning | GTA::LogLevel::Error, false);
		Log::Debug("ScriptLoader->Initialize");

		AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&ScriptLoader::ResolveAssembly);

		ScriptProcessor::_hookVersion = Assembly::GetExecutingAssembly()->GetName()->Version->ToString();

		GameVersion::Detect();

		ScriptProcessor::Initialize();
		TextHook::Initialize();
		Pool::InitializeDefault();
	}

	void ScriptLoader::UnloadScripts() {
		ScriptProcessor::Instance->UnloadScripts();
	}

	void ScriptLoader::ProxyTick(DWORD timerDelta) {
		ScriptProcessor::Instance->Tick(timerDelta);
	}

#if GTA_SA
	const char* ScriptLoader::ProxyGetString(const char* string) {
#else
	const wchar_t* ScriptLoader::ProxyGetString(const char* string) {
#endif
		return TextHook::GetString(string);
	}

	void ScriptLoader::LoadScripts() {
		Log::Debug("ScriptLoader->LoadScripts");

		if (!Directory::Exists(Environment::ExpandEnvironmentVariables("%temp%\\GTAScriptHook"))) {
			Directory::CreateDirectory(Environment::ExpandEnvironmentVariables("%temp%\\GTAScriptHook"));
		}

		_loadedAssemblies = gcnew List<String^>();

		AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&ScriptLoader::ResolveAssembly);

		String^ baseDir = Windows::Forms::Application::StartupPath;

		LoadAssemblies(baseDir + "\\scripts", "GTAScriptAPI.dll");
		LoadAssemblies(baseDir + "\\scripts", "*.dll");
		LoadAssemblies(baseDir, "*.net"); // don't think this is going to be used anyway
	}

	void ScriptLoader::LoadAssembly(Assembly^ assembly) {
		try {
			cli::array<Type^>^ types = assembly->GetTypes();

			for each (Type^ type in types) {
				if (type->IsPublic && !type->IsAbstract) {
					try {
						if (type->IsSubclassOf(BaseScript::typeid)) {
							BaseScript^ script = (BaseScript^)Activator::CreateInstance(type);

							LoadScript(script);
						}

						if (!GameInitialized) {
							if (type->IsSubclassOf(ScriptInitializer::typeid)) {
								ScriptInitializer^ script = (ScriptInitializer^)Activator::CreateInstance(type);
								script->OnGameStart();
							}
						}

						if (type->IsSubclassOf(ScriptPostInitializer::typeid)) {
							ScriptPostInitializer^ script = (ScriptPostInitializer^)Activator::CreateInstance(type);
							script->OnGameStart();
						}
					} catch (Exception^ e) {
						Log::Error("An exception occurred during initialization of the script " + type->Name + ".");
						Log::Error(e);
					}
				}
			}
		} catch (ReflectionTypeLoadException^ e) {
			// likely a non-v2hook script
			Log::Warn("Assembly " + assembly->GetName() + " could not be loaded because of a loader exception (perhaps this is made for an older GTAScriptHook?)");
			Log::Warn("Exception: " + e->LoaderExceptions[0]->ToString()->Split('\n')[0]->Trim());
		}
	}

	void ScriptLoader::LoadAssemblies(String^ folder, String^ filter) {
		cli::array<String^>^ files = Directory::GetFiles(folder, filter);

		for each (String^ file in files) {
			String^ fileName = FileInfo(file).FullName;

			if (!_loadedAssemblies->Contains(fileName)) {
				String^ origTargetName = Environment::ExpandEnvironmentVariables("%temp%\\GTAScriptHook") + "\\" + Path::GetFileName(file);
				String^ targetName = origTargetName + "";
				bool loaded = false;
				int i = 0;

				while (!loaded) {
					try {
						File::Copy(fileName, targetName, true);
						loaded = true;
					} catch (IOException^) {
						targetName = origTargetName->Replace(".dll", "-" + i.ToString() + ".dll");
						i++;
					}
				}

				Assembly^ assembly = Assembly::LoadFile(targetName);
				
				LoadAssembly(assembly);

				_loadedAssemblies->Add(fileName);
			}
		}
	}

	void ScriptLoader::LoadScript(BaseScript^ script) {
		Log::Info("Loading script " + script->GetType()->Name);

		ScriptProcessor::Instance->AddScript(script);
	}
}