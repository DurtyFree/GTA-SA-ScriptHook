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
            this.Hours = hours;
            this.Minutes = minutes;
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
                return this._r;
            }
        }

        public byte G
        {
            get
            {
                return this._g;
            }
        }

        public byte B
        {
            get
            {
                return this._b;
            }
        }

        public byte A
        {
            get
            {
                return this._a;
            }
            set
            {
                this._a = value;
            }
        }

        public GTAColor(byte r, byte g, byte b)
            : this(r, g, b, 255)
        {

        }

        public GTAColor(byte r, byte g, byte b, byte a)
        {
            this._r = r;
            this._g = g;
            this._b = b;
            this._a = a;
        }
    }
}
