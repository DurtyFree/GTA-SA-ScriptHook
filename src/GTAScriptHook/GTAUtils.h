#pragma once

#include "GameVersion.h"

namespace GTA {
	public ref class GTAUtils {
	private:
		GTAUtils() { }
	internal:
		static void RebaseNearOpcode(BYTE* command, BYTE* originalLocation, BYTE* newLocation);
	public:
		static float ConvertIntAsFloat(int integer) {
			float retval;
			memcpy(&retval, &integer, sizeof(float));

			return retval;
		}

		static int ConvertFloatAsInt(float floatval) {
			int retval;
			memcpy(&retval, &floatval, sizeof(int));

			return retval;
		}

		static int GetGameTimer() {
#ifdef GTA_SA
			DWORD* timer = (DWORD*)0xB7CB84;

			if (GameVersion::VersionNumber == 101 || GameVersion::VersionNumber == 200) {
				timer = (DWORD*)0xB7F204;
			}
#endif
#ifdef GTA_III
			DWORD* timer = (DWORD*)0x885B48;
#endif
#if GTA_IV
			DWORD timerV = GetTickCount();
			DWORD* timer = &timerV;
#endif

			return *timer;
		}

		static void Wait(int time);

#ifdef GTA_SA
		static void SetPlayerWeaponSlot(int slotID);
		static void LoadGameNatively();
#endif
	};
}