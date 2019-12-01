using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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

    public class GTAColor
    {
        private byte _r;
        private byte _g;
        private byte _b;
        private byte _a;

        public byte R
        {
            get
            {
                return _r;
            }
        }

        public byte G
        {
            get
            {
                return _g;
            }
        }

        public byte B
        {
            get
            {
                return _b;
            }
        }

        public byte A
        {
            get
            {
                return _a;
            }
            set
            {
                _a = value;
            }
        }

        public GTAColor(byte r, byte g, byte b)
            : this(r, g, b, 255)
        {

        }

        public GTAColor(byte r, byte g, byte b, byte a)
        {
            _r = r;
            _g = g;
            _b = b;
            _a = a;
        }
    }
}
