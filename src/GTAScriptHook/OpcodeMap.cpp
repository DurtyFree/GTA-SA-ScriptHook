#include "stdafx.h"
#include "OpcodeMap.h"

namespace GTA {
	namespace Internal {
		static OpcodeMap::OpcodeMap() {
			_opcodes = gcnew Dictionary<int, String^>();
			_opcodes->Add(0x02c0, "GET_CLOSEST_CAR_NODE"); // for lack of a char op
			_opcodes->Add(0x02c1, "GET_CLOSEST_CAR_NODE");

			_opcodes->Add(0x03d3, "GET_CLOSEST_CAR_NODE_WITH_HEADING");

			_opcodes->Add(0x0164, "REMOVE_BLIP");
			_opcodes->Add(0x018b, "CHANGE_BLIP_DISPLAY");
			_opcodes->Add(0x0165, "CHANGE_BLIP_COLOUR");
			_opcodes->Add(0x0168, "CHANGE_BLIP_SCALE");
			_opcodes->Add(0x07e0, "SET_BLIP_AS_FRIENDLY");

			//_opcodes->Add(0x015f, "SET_CAM_POS");

			_opcodes->Add(0x00e1, "IS_CONTROL_PRESSED");
			_opcodes->Add(0x00c0, "SET_TIME_OF_DAY");
			_opcodes->Add(0x00bf, "GET_TIME_OF_DAY");

			_opcodes->Add(0x0629, "SET_INT_STAT");
			_opcodes->Add(0x062a, "SET_FLOAT_STAT");

			_opcodes->Add(0x0652, "GET_INT_STAT");
			_opcodes->Add(0x0653, "GET_FLOAT_STAT");

			_opcodes->Add(0x016b, "IS_SCREEN_FADING");

			_opcodes->Add(0x0826, "DISPLAY_HUD");
			_opcodes->Add(0x0581, "DISPLAY_RADAR");
			_opcodes->Add(0x09ba, "DISPLAY_AREA_NAME");

			// todo: make this GXT?
			//_opcodes->Add(0x03e5, "PRINT_HELP");

			_opcodes->Add(0x0630, "SET_GROUP_LEADER");
			_opcodes->Add(0x0631, "SET_GROUP_MEMBER");
			_opcodes->Add(0x0632, "REMOVE_GROUP");
			_opcodes->Add(0x06EE, "IS_GROUP_MEMBER");
			_opcodes->Add(0x06EF, "IS_GROUP_LEADER");
			_opcodes->Add(0x06F0, "SET_GROUP_SEPARATION_RANGE");
			_opcodes->Add(0x07F6, "GET_GROUP_SIZE");
			_opcodes->Add(0x092B, "GET_GROUP_MEMBER");

			_opcodes->Add(0x0247, "REQUEST_MODEL");
			_opcodes->Add(0x0248, "HAS_MODEL_LOADED");
			_opcodes->Add(0x0249, "MARK_MODEL_AS_NO_LONGER_NEEDED");

			_opcodes->Add(0x02AB, "SET_CHAR_PROOFS");
			_opcodes->Add(0x009B, "DELETE_CHAR");
			_opcodes->Add(0x01C2, "MARK_CHAR_AS_NO_LONGER_NEEDED");
			_opcodes->Add(0x06C9, "REMOVE_CHAR_FROM_GROUP");
			_opcodes->Add(0x0449, "IS_CHAR_IN_ANY_CAR");
			_opcodes->Add(0x0118, "IS_CHAR_DEAD");
			_opcodes->Add(0x056d, "DOES_CHAR_EXIST");
			_opcodes->Add(0x0665, "GET_CHAR_MODEL");
			_opcodes->Add(0x03c0, "GET_CAR_CHAR_IS_USING");
			_opcodes->Add(0x09e8, "GET_INTERIOR_FROM_CHAR");
			_opcodes->Add(0x0860, "SET_ROOM_FOR_CHAR_BY_KEY");
			_opcodes->Add(0x04d7, "FREEZE_CHAR_POSITION");
			_opcodes->Add(0x02E2, "SET_CHAR_ACCURACY");
			_opcodes->Add(0x051a, "HAS_CHAR_BEEN_DAMAGED_BY_CHAR");
			_opcodes->Add(0x051b, "HAS_CHAR_BEEN_DAMAGED_BY_CAR");
			_opcodes->Add(0x031d, "HAS_CHAR_BEEN_DAMAGED_BY_WEAPON");
			_opcodes->Add(0x00a0, "GET_CHAR_COORDINATES");
			_opcodes->Add(0x00a1, "SET_CHAR_COORDINATES");
			_opcodes->Add(0x0223, "SET_CHAR_HEALTH");
			_opcodes->Add(0x0226, "GET_CHAR_HEALTH");
			_opcodes->Add(0x04DD, "GET_CHAR_ARMOUR");
			_opcodes->Add(0x035F, "ADD_ARMOUR_TO_CHAR");
			_opcodes->Add(0x0173, "SET_CHAR_HEADING");
			_opcodes->Add(0x0172, "GET_CHAR_HEADING");

			_opcodes->Add(0x0215, "REMOVE_PICKUP");
			_opcodes->Add(0x0214, "HAS_PICKUP_BEEN_COLLECTED");
			_opcodes->Add(0x032B, "CREATE_PICKUP_WITH_AMMO");
			_opcodes->Add(0x0213, "CREATE_PICKUP");

			_opcodes->Add(0x03BF, "SET_EVERYONE_IGNORE_PLAYER");

		}
	}
}