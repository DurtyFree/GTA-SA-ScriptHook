namespace GTA
{
    public struct Time
    {
        public Time(int hours, int minutes) : this()
        {
            Hours = hours;
            Minutes = minutes;
        }

        public int Hours { get; set; }
        public int Minutes { get; set; }
    }

    public class GtaColor
    {
        public byte R { get; }

        public byte G { get; }

        public byte B { get; }

        public byte A { get; set; }

        public GtaColor(byte r, byte g, byte b, byte a = 255)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
    }
}
