namespace GTA
{
    // TODO: find out if GTA reads alpha value
    public struct BlipColor
    {
        public byte R { get; }

        public byte G { get; }

        public byte B { get; }

        public byte A { get; }

        public static BlipColor Default => new BlipColor(0);

        public static BlipColor Int0 => new BlipColor(0);

        public static BlipColor Pickup => new BlipColor(1);

        public static BlipColor Int1 => new BlipColor(1);

        public static BlipColor LightBlue => new BlipColor(2);

        public static BlipColor Int2 => new BlipColor(2);

        public static BlipColor White => new BlipColor(3);

        public static BlipColor Int3 => new BlipColor(3);

        public static BlipColor Destination => new BlipColor(4);

        public static BlipColor Int4 => new BlipColor(4);

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
            R = r;
            G = g;
            B = b;
            A = a;
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

                return ((R * cR) + (G * cG) + (B * cB) + (A * cA));
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
        private BlipColor _currentColor;

        public Blip()
        {
            _currentColor = BlipColor.Default;
            Icon = BlipIcon.MiscDestination;
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
            blip.Icon = icon;

            blip.Position = position;

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
            get => _currentColor;
            set
            {
                _currentColor = value;
                Internal.Function.Call(0x0165, this, (int)value.Value);
            }
        }

        public Vector3 Position { get; private set; }

        public int Size
        {
            set => Internal.Function.Call(0x0168, this, value);
        }

        public bool Friendly
        {
            set => Internal.Function.Call(0x07E0, this, value);
        }

        public BlipIcon Icon { get; private set; }

        public BlipDisplay Display
        {
            set => Internal.Function.Call(0x018B, this, (int)value);
        }
    }
}
