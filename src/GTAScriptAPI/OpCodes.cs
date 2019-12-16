using GTA.Internal;

namespace GTA
{
    public enum OpCodes : uint
    {
        CAR_GOTO_COORDINATES = 0x00a7, // vHandle, xF, yF ,zF
        CAR_WANDER_RANDOMLY = 0x00a8, // vHandle
        CAR_SET_IDLE = 0x00a9, // vHandle
        SET_CAR_VISIBLE = 0x0338, // vHandle, bool
        SWITCH_CAR_GENERATOR = 0x0338, // carGenHandle, i
        GET_MAXIMUM_NUMBER_OF_PASSENGERS = 0x01EA, // vHandle => i
        SET_CAR_HEAVY = 0x01EC, // vHandle, b
        EXPLODE_CAR = 0x020B,  // vHandle
        GET_CAR_DOOR_LOCK_STATUS = 0x09B3, // vHandle => i
        LOCK_CAR_DOORS = 0x020A, // vHandle, i
        GET_CAR_HEALTH = 0x0227, // vHandle => F
        SET_CAR_HEALTH = 0x0224, // vHandle, i
    }

    public static class OpCode
    {
        public static bool Call(OpCodes opCode, params Parameter[] parameters) => Function.Call((uint)opCode, parameters);

        public static TReturn Call<TReturn>(OpCodes opCode, params Parameter[] parameters) => Function.Call<TReturn>((uint)opCode, parameters);
    }
}
