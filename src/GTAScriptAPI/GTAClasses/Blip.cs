using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    // TODO: find out if GTA reads alpha value
    public struct BlipColor
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
        }

        public static BlipColor Default
        {
            get
            {
                return new BlipColor(0);
            }
        }

        public static BlipColor Int_0
        {
            get
            {
                return new BlipColor(0);
            }
        }

        public static BlipColor Pickup
        {
            get
            {
                return new BlipColor(1);
            }
        }

        public static BlipColor Int_1
        {
            get
            {
                return new BlipColor(1);
            }
        }

        public static BlipColor LightBlue
        {
            get
            {
                return new BlipColor(2);
            }
        }

        public static BlipColor Int_2
        {
            get
            {
                return new BlipColor(2);
            }
        }

        public static BlipColor White
        {
            get
            {
                return new BlipColor(3);
            }
        }

        public static BlipColor Int_3
        {
            get
            {
                return new BlipColor(3);
            }
        }

        public static BlipColor Destination
        {
            get
            {
                return new BlipColor(4);
            }
        }

        public static BlipColor Int_4
        {
            get
            {
                return new BlipColor(4);
            }
        }

        public BlipColor(byte a)
            : this(0, 0, 0, a)
        {

        }

        public BlipColor(byte r, byte g, byte b)
            : this(r, g, b, 0)
        {

        }

        public BlipColor(byte r, byte g, byte b, byte a)
        {
            this._r = r;
            this._g = g;
            this._b = b;
            this._a = a;
        }

        public uint Value
        {
            get
            {
                // this could also be done using bitshifting, but this is more readable and worked in SanAndreasScriptHook.
                // this does not exist in VC however!
                uint cR = 16777216;
                uint cG = 65536;
                uint cB = 256;
                uint cA = 1;

                return ((this.R * cR) + (this.G * cG) + (this.B * cB) + (this.A * cA));
            }
        }
    }

    public enum BlipDisplay
    {
        Neither = 0,
        MarkerOnly = 1,
        BlipOnly = 2,
        Both = 3
    }

    public class Blip : HandleObject
    {
        private BlipIcon currentIcon;
        private BlipColor currentColor;
        private Vector3 lastPosition;

        public Blip()
        {
            this.currentColor = BlipColor.Default;
            this.currentIcon = BlipIcon.Misc_Destination;
        }

        public static Blip AddBlip(Vector3 position, BlipIcon icon)
        {
            return AddBlip(position, icon, false);
        }

        public static Blip AddBlip(Vector3 position, BlipIcon icon, bool checkpoint)
        {
            Blip blip;

            if (checkpoint)
            {
                blip = Internal.Function.Call<Blip>(0x018a, position);
            }
            else
            {
                blip = Internal.Function.Call<Blip>(0x02a8, position, (int)icon);
            }

            blip.Size = 3; // sensible defaults, yaknow
            blip.currentIcon = icon;

            blip.lastPosition = position;

            return blip;
        }

        public static Blip AddBlip(Ped character)
        {
            return Internal.Function.Call<Blip>(0x0187, character);
        }

        public static Blip AddBlip(Vehicle car)
        {
            return Internal.Function.Call<Blip>(0x0186, car);
        }

        public static Blip AddBlip(Pickup pickup)
        {
            return Internal.Function.Call<Blip>(0x03dc, pickup);
        }

        public void Delete()
        {
            Internal.Function.Call(0x0164, this);
        }

        public void MakeInvisibleOnRadar()
        {
            Internal.Function.Call(0x018b, this, 1); // BLIPDISPLAY_MARKERONLY
        }

        public void MakeInvisibleOnScreen()
        {
            Internal.Function.Call(0x018b, this, 2); // MARKER_DISPLAY_BLIPONLY
        }

        public BlipColor Color
        {
            get
            {
                return this.currentColor;
            }
            set
            {
                this.currentColor = value;
                Internal.Function.Call(0x0165, this, (int)value.Value);
            }
        }

        public Vector3 Position
        {
            get
            {
                return this.lastPosition;
            }
        }

        public int Size
        {
            set
            {
                Internal.Function.Call(0x0168, this, value);
            }
        }

        public bool Friendly
        {
            set
            {
                Internal.Function.Call(0x07E0, this, value);
            }
        }

        public BlipIcon Icon
        {
            get
            {
                return this.currentIcon;
            }
        }

        public BlipDisplay Display
        {
            set
            {
                Internal.Function.Call(0x018B, this, (int)value);
            }
        }
    }
}
