#pragma once

namespace GTA {
	namespace Internal {
		public ref class OpcodeMap {
		private:
			static Dictionary<int, String^>^ _opcodes;
		public:
			static OpcodeMap();
			//static String^ GetID(int id);
			//static int GetName(String^ name);
		};
	}
}