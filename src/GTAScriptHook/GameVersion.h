#pragma once

namespace GTA {
	public ref class GameVersion {
	private:
		GameVersion() { }

		static int _version;
		static char _region;
	public:
		static void Detect();

		static property int VersionNumber {
			int get() {
				return _version;
			}
		}

		static property char Region {
			char get() {
				return _region;
			}
		}

		static property String^ VersionName {
			String^ get() {
#ifdef GTA_SA
				switch (VersionNumber) {
					case 100:
						return "1.0";
					case 101:
						return "1.01";
					case 200:
						return "2.00";
				}

				return "Unknown";
#else
#ifdef GTA_III
				return "GTA III";
#endif
#ifdef GTA_IV
				return "GTA IV";
#endif
#endif
			}
		}
	};
}