#pragma once

namespace GTA {
	void __stdcall GetGXTString(const char* string);

	public ref class TextHook {
	private:
		static int _textMemory;

		static List<Func<String^, String^>^>^ _accessFunctions;
		static List<Func<String^, String^>^>^ _filterFunctions;
		static Dictionary<String^, IntPtr>^ _keyCache;
	internal:
		static void Install();
		static void Initialize();
#if GTA_SA
		static const char* GetString(const char* string);
#else
		static const wchar_t* GetString(const char* string);
#endif
	public:
		static String^ Get(String^ label);

		static void RemoveCache(String^ label);

		static void RegisterCallback(Func<String^, String^>^ function) {
			if (_accessFunctions == nullptr) {
				_accessFunctions = gcnew List<Func<String^, String^>^>();
			}

			_accessFunctions->Add(function);
		}

		static void RegisterFilter(Func<String^, String^>^ function) {
			if (_filterFunctions == nullptr) {
				_filterFunctions = gcnew List<Func<String^, String^>^>();
			}

			_filterFunctions->Add(function);
		}
	};
}