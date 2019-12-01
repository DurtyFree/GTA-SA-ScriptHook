#pragma once

#if defined ( Yield ) 
#undef Yield 
#endif 

using namespace System::Threading;

namespace GTA {
/*	public ref class BaseTickScript : BaseScript {
	private:
		int _interval;
	public:
		BaseTickScript() { _interval = 0; }

		property int Interval {
			int get() {
				return _interval;
			}
			void set(int value) {
				_interval = value;
			}
		}

		event EventHandler^ Tick;

		virtual void OnTick() {
			Tick(this, EventArgs::Empty);
		}

		void Run();
	};*/

	value class BoundKeyData {
	public:
		int _keyCode;
		Action^ _call;
	};

	public ref class BaseScript {
	private:
		static bool _keyBindingsDisabled;
	internal:
		List<BoundKeyData>^ _boundKeys;
	public:
		virtual void OnStart() { }
		virtual void Run();

		static property bool DisableKeyBindings {
			bool get() {
				return _keyBindingsDisabled;
			}

			void set(bool value) {
				_keyBindingsDisabled = value;
			}
		}

		void Wait() { Wait(0); }
		void Wait(int time);

		void BindKey(Windows::Forms::Keys key, Action^ function);
		void ProcessKeyBindings();
	};

	private ref class ScriptContext {
	private:
		void HandleException(Exception^ e);
	internal:
		static ScriptContext^ current;

		bool _endNext;

		Thread^ _thread;
		EventWaitHandle^ _execute;
		EventWaitHandle^ _continue;
		BaseScript^ _myScript;
		DWORD _wakeUpAt;

		String^ _identifier;

		ScriptContext(BaseScript^ script);

		void WakeUp();
		void Yield();
		void Run();
		void Clean();
	};
}