using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public enum GTAKey
    {
#if !GTA_IV
        L1 = 4,
        L2 = 5,
        R1 = 6,
        R2 = 7,
        DPadUp = 8,
        DPadDown = 9,
        DPadLeft = 10,
        DPadRight = 11,
        Select = 13,
        Square = 14,
        Triangle = 15,
        Cross = 16,
        Circle = 17,
        L3 = 18,
        R3 = 19
#endif
    }

    public class Controls
    {
        public static bool KeyPressed(GTAKey key)
        {
            return Internal.Function.Call(0x00E1, 0, (int)key);
        }

        public static bool KeyPressed(System.Windows.Forms.Keys key)
        {
            return (ScriptProcessor.Instance.KeyBuffer[(int)key] != 0);
        }

        public static Vector3 GetLeftStick()
        {
            VarPointer x = new VarPointer();
            VarPointer y = new VarPointer();

            Internal.Function.Call(0x0494, 0, x, y, new VarPointer(), new VarPointer());

            return new Vector3((int)x, (int)y);
        }

        public static Vector3 GetRightStick()
        {
            VarPointer x = new VarPointer();
            VarPointer y = new VarPointer();

            Internal.Function.Call(0x0494, 0, new VarPointer(), new VarPointer(), x, y);

            return new Vector3((int)x, (int)y);
        }
    }
}
