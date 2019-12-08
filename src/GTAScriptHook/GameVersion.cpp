#include "stdafx.h"
#include "gameversion.h"
#include "Log.h"

namespace GTA {
	void GameVersion::Detect() {
#ifdef GTA_SA
		// first detect the game main version
		// code taken from VehicleAudioHook, and is indeed audio-related

		const char* data = "\x2D\x90\x01\x00\x00";
		int version = 100;

		// is this 1.0?
		void* testAddress = (void*)0x4F77BB;

		if (memcmp(testAddress, data, 5)) {
			// try 1.1
			version = 101;
			testAddress = (void*)0x4F7C1B;

			if (memcmp(testAddress, data, 5)) {
				// version 2 seems to take a while - it may decrypt the code first?
				// after 15 seconds the code is decrypted, and for the purposes of the audio hook,
				// version 2 is equal to version 1.01, but with different copy protection
				Log::Debug("Unknown game version, waiting 15 seconds to see if it is v2 (not).");
				//Sleep(15000);

				version = 200;

				if (memcmp(testAddress, data, 5)) {
					version = 100;
					Log::Warn("Unknown GTA version found!");
				}
			}
		}

		_version = version;
		_region = 'U'; // for now, we hardcode US

		if (_version == 100) {
			testAddress = (void*)0x7474D3;
			data = "\x89\x35\xC0\xD4\xC8\x00";

			if (memcmp(testAddress, data, 5) == 0) {
				_region = 'E';
			}
		}
#else
#ifdef GTA_IV
		_version = (int)Game::GetVersion();
		_region = 'I';
#endif
#endif
	}
}