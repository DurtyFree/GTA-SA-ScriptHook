#pragma once

using namespace System::IO;
using namespace System::Globalization;

namespace GTA {
	public enum struct LogLevel {
		None = 0,
		Error = 1,
		Warning = 2,
		Info = 4,
		Debug = 8
	};

	public ref class Log {
	private:
		Log() { }

		static StreamWriter^ _logWriter;
		static LogLevel _logLevel;
		static String^ _filename;

		static void Write(String^ message, LogLevel level);
	public:
		static void Initialize(String^ filename, LogLevel logLevel, bool free);

		static bool MayWriteType(LogLevel type);

		static void Debug(String^ message);
		static void Info(String^ message);
		static void Warn(String^ message);
		static void Error(String^ message);
		static void Error(Exception^ exception) { Error(exception->ToString()); }

		static event Action<LogLevel, String^>^ EventWritten;

		static property LogLevel CurrentLogLevel {
			void set(LogLevel logLevel) {
				_logLevel = logLevel;
			}
		}
	};
}