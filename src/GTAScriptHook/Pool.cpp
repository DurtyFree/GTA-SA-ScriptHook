#include "stdafx.h"
#include "Pool.h"
#include "Log.h"
#include "GTAUtils.h"

namespace GTA {
	Pool::Pool(IntPtr start, DWORD elSize) {
		_pool = (CPool**)start.ToPointer();
		_elSize = elSize;

		_pointerList = gcnew List<IntPtr>();
		_handleList = gcnew List<int>();
	}

	int Pool::PtrToHandle(IntPtr pointer) {
		DWORD number = pointer.ToInt32();

		DWORD amount = number - ((DWORD)(*_pool)->objects);
		amount = amount / _elSize;

		signed char unique = (*_pool)->flags[amount];
		return (amount << 8) + unique;
	}

	IntPtr Pool::GetAtIndex(int index) {
		if ((*_pool)->flags[index] >= 0) {
			DWORD_PTR ptr = (*_pool)->objects;
			ptr += (index * _elSize);
			return IntPtr((int)ptr);
		}

		return IntPtr::Zero;
	}

	IntPtr Pool::HandleToPtr(int handle) {
		int index = (handle >> 8);
		int uniqu = (handle & 0xFF);

		if ((*_pool)->flags[index] == uniqu) {
			DWORD_PTR ptr = (*_pool)->objects;
			ptr += (index * _elSize);
			return IntPtr((int)ptr);
		}

		return IntPtr::Zero;
	}

	List<int>^ Pool::GetAllHandles() {
		List<IntPtr>^ pointers = GetAllPointers();
		//List<int>^ handles = gcnew List<int>();
		_handleList->Clear();

		for each (IntPtr pointer in pointers) {
			_handleList->Add(PtrToHandle(pointer));
		}

		return _handleList;
	}

	List<IntPtr>^ Pool::GetAllPointers() {
		//List<IntPtr>^ pointers = gcnew List<IntPtr>();
		_pointerList->Clear();

		for (int i = (*_pool)->size; i > 0; i--) {
			if ((*_pool)->flags[i] >= 0) {
				//DWORD ptr = *(DWORD*)((*_pool)->objects);
				DWORD_PTR ptr = (*_pool)->objects;
				ptr += (i * _elSize);
				_pointerList->Add(IntPtr((int)ptr));
			}
		}

		return _pointerList;
	}

	void Pool::InitializeDefault() {
#ifdef GTA_SA
		_pedPool = gcnew Pool(IntPtr(0xB74490), 1988);
		_vehiclePool = gcnew Pool(IntPtr(0xB74494), 2584);
		_objectPool = gcnew Pool(IntPtr(0xB7449C), 412);
		_txdPool = gcnew Pool(IntPtr(0xC8800C), 12);
#endif
#ifdef GTA_III
		// -- 1.0!
		_pedPool = gcnew Pool(IntPtr(0x8F2C60), 1520);
		_vehiclePool = gcnew Pool(IntPtr(0x9430DC), 1448);
		_objectPool = gcnew Pool(IntPtr(0x880E28), 412);
		_txdPool = gcnew Pool(IntPtr(0x8F5FB8), 28);
#endif
	}
}