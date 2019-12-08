using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class Draw
    {
        public static void Corona(Vector3 position, GTAColor color)
        {
            Corona(position, color, 1.0f);
        }

        public static void Corona(Vector3 position, GTAColor color, float radius)
        {
            Corona(position, color, radius, 0);
        }

        public static void Corona(Vector3 position, GTAColor color, float radius, int type)
        {
            Corona(position, color, radius, type, false);
        }

        public static void Corona(Vector3 position, GTAColor color, float radius, int type, bool lensFlare)
        {
            Internal.Function.Call(0x024f, position, radius, type, lensFlare, color.R, color.G, color.B);
        }

        public static void Blank(GTAColor color)
        {
            Box(Memory.ReadSingle(0x85951c) / 2, 224f, Memory.ReadSingle(0x85951c) + 10f, 458f, color);
        }

        public static void Box(float x, float y, float w, float h, GTAColor color)
        {
            Internal.Function.Call(0x038e, x, y, w, h, color.R, color.G, color.B, color.A);
        }
    }
}
