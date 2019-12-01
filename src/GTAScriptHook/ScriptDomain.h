#pragma once

#include "ScriptLoader.h"

namespace GTA {
	ref class DomainThingy : MarshalByRefObject {
	public:
		virtual Object^ InitializeLifetimeService() override {
			return nullptr;
		}
	internal:
		void SetMainDomain(AppDomain^ domain);
	};

	public ref class ScriptDomain {
	internal:
		static bool _initedOnce;

		static AppDomain^ _scriptDomain;
		static AppDomain^ _mainDomain;
		static ScriptLoader^ _loader;

		static void LoadMe();
		static void Recreate();

		static void CreateDomain();
		static ScriptLoader^ CreateScriptLoader();

		static property ScriptLoader^ Loader {
			ScriptLoader^ get() {
				return _loader;
			}
		}

	public:
		static void MarshalInDefaultDomain(CrossAppDomainDelegate^ delegat);
	};
}