#include "Stdafx.h"
#include "VarPointer.h"
#include "GTAUtils.h"

namespace GTA {
	VarPointer::operator float(VarPointer^ source) {
		return GTAUtils::ConvertIntAsFloat(source->Value);
	}

	VarPointer::operator int(VarPointer^ source) {
		return source->Value;
	}

	void VarPointer::Initialize(int value) {
		varStorage[_curID] = value;
		_varID = _curID;
		_curID++;

		if (_curID >= 512) {
			_curID = 0;
		}
	}

	void* VarPointer::CreatePointer() {
		pin_ptr<int> ptr = &varStorage[_varID];
		return (void*)ptr;
	}
}