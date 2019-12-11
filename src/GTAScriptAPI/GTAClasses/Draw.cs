namespace GTA
{
    public class Draw
    {
        public static void Corona(Vector3 position, GtaColor color)
        {
            Corona(position, color, 1.0f);
        }

        public static void Corona(Vector3 position, GtaColor color, float radius)
        {
            Corona(position, color, radius, 0);
        }

        public static void Corona(Vector3 position, GtaColor color, float radius, int type)
        {
            Corona(position, color, radius, type, false);
        }

        public static void Corona(Vector3 position, GtaColor color, float radius, int type, bool lensFlare)
        {
            Internal.Function.Call(0x024f, position, radius, type, lensFlare, color.R, color.G, color.B);
        }

        public static void Blank(GtaColor color)
        {
            Box(Memory.ReadSingle(0x85951c) / 2, 224f, Memory.ReadSingle(0x85951c) + 10f, 458f, color);
        }

        public static void Box(float x, float y, float w, float h, GtaColor color)
        {
            Internal.Function.Call(0x038e, x, y, w, h, color.R, color.G, color.B, color.A);
        }
    }
}
