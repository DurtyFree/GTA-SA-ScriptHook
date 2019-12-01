#include "Stdafx.h"
#include "GTAUtils.h"
#include "Script.h"
#include "InternalCalls.h"

#ifdef GTA_SA
#pragma unmanaged
void PlayerConfigureWeaponSlot(DWORD dwThis, BYTE weaponSlot) {
    DWORD dwFunc = 0x60D000;
    _asm
    {
        mov     ecx, dwThis
        push    weaponSlot
        call    dwFunc
    }
}

void GameLoadNow() {
	DWORD menu = 0xBA6748;
	DWORD gameLoader = 0x573330;
	DWORD mpackNumber = 0xB72910;

	_asm {
		pushad
		mov ecx, menu
		call gameLoader
		mov bl, 1
		mov [ecx + 32h], bl
		mov [ecx + 60h], bl
		mov [ecx + 0xE9], bl
		mov [mpackNumber], 0
		mov [ecx + 1B3Ch], 0
		mov bl, 0
		mov [ecx + 32h], bl
		mov [ecx + 33h], bl
		popad
	}
}
#pragma managed
#endif

namespace GTA {
	void GTAUtils::Wait(int time) {
		ScriptContext^ context = ScriptContext::current;

		//Internal::Function::Call(0x0001, 0);

		context->_wakeUpAt = GTAUtils::GetGameTimer() + time;
		//context->_continue->Set();
		//context->_execute->WaitOne();
		context->Yield();
	}

#ifdef GTA_SA
	void GTAUtils::SetPlayerWeaponSlot(int slotID) {
		BYTE bslotID = (BYTE)slotID; // to help alignment

		// 0xB7CD98 (first CPlayerInfo) + 4 (CPlayerPedData) + 28 (m_nChosenWeapon)
		*(BYTE *)0xB7CDB8 = bslotID;

		PlayerConfigureWeaponSlot(*(DWORD *)0xB7CD98, slotID);
	}

	void GTAUtils::LoadGameNatively() {
		GameLoadNow();
	}
#endif

	void GTAUtils::RebaseNearOpcode(BYTE* command, BYTE* originalLocation, BYTE* newLocation) {
		if (command[0] == 0xE9 || command[0] == 0xE8) { // jump near and call near
			int originalPointer;
			memcpy(&originalPointer, &command[1], sizeof(int)); // easiest to understand :p

			originalPointer += (DWORD)originalLocation;
			originalPointer -= (DWORD)newLocation;

			memcpy(&command[1], &originalPointer, sizeof(int));
		}
	}
} 