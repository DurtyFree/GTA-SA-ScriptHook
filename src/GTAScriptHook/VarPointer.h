#pragma once

#include "Log.h"

namespace GTA {
	public ref class VarPointer {
	private:
		static cli::array<int>^ varStorage;
		static int _curID;

		int _varID;

		void Initialize(int value);
	internal:
		void* CreatePointer();
	public:
		static VarPointer() {
			varStorage = gcnew cli::array<int>(512);
			_curID = 0;
		}

		VarPointer() {
			Initialize(0);
		}

		VarPointer(int value) {
			Initialize(value);
		}

		property int Value {
			int get() {
				return varStorage[_varID];
			}
			void set(int value) {
				varStorage[_varID] = value;
			}
		}

		property int ID {
			int get() {
				return _varID;
			}
		}

		static explicit operator int (VarPointer^ source);
		static explicit operator float (VarPointer^ source);
	};
}