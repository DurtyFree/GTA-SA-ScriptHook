using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class Native
    {
        public static int CallOpcode(ushort opcode, params Internal.Parameter[] parameters)
        {
            return (Internal.Function.Call(opcode, parameters)) ? 1 : 0;
        }
    }

    public class Initialize
    {
        public static void Log(string message)
        {
            GTA.Log.Debug("SASHook legacy - " + message);
        }
    }
}
