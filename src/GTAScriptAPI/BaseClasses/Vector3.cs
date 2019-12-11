using System;

namespace GTA
{
    public enum PathType
    {
        Car,
        Ped
    }

    public struct Vector3
    {
        static readonly Random _random;

        static Vector3()
        {
            _random = new Random();
        }

        public float PX, PY, PZ;

        public float X { get => PX;
            set => PX = value;
        }
        public float Y { get => PY;
            set => PY = value;
        }
        public float Z { get => PZ;
            set => PZ = value;
        }

        public Vector3(float x, float y) : this(x, y, 0f) { }

        public Vector3(float x, float y, float z)
        {
            PX = x;
            PY = y;
            PZ = z;
        }

        public Vector3(SVector old)
        {
            PX = old.pX;
            PY = old.pY;
            PZ = old.pZ;
        }

        public float DistanceTo2D(Vector3 other)
        {
            Vector3 temp = other;
            temp.PZ = 0;

            Vector3 temp2 = this;
            temp2.PZ = 0;

            return temp2.DistanceTo(temp);
        }

        public float DistanceTo(Vector3 other)
        {
            Vector3 diff = other - this;

            return diff.Length();
        }

        public float Length()
        {
            return (float)Math.Sqrt((X * X) + (Y * Y) + (Z * Z));
        }

        public Vector3 Around(float distance)
        {
            Vector3 difference = RandomXy() * distance;

            return (this + difference);
        }

        public static Vector3 RandomXy()
        {
            Vector3 retval = new Vector3((float)(_random.NextDouble() - 0.5), (float)(_random.NextDouble() - 0.5));
            retval.Normalize();

            return retval;
        }

        public void Normalize()
        {
            var length = Length();

            if (length > 0)
            {
                var factor = 1.0f / length;
                X *= factor;
                Y *= factor;
                Z *= factor;
            }
        }

        public static Vector3 operator -(Vector3 left, Vector3 right)
        {
            return new Vector3(left.X - right.X, left.Y - right.Y, left.Z - right.Z);
        }

        public static Vector3 operator +(Vector3 left, Vector3 right)
        {
            return new Vector3(left.X + right.X, left.Y + right.Y, left.Z + right.Z);
        }

        public static Vector3 operator *(Vector3 vector, float factor)
        {
            return new Vector3(vector.X * factor, vector.Y * factor, vector.Z * factor);
        }

        public static implicit operator Internal.Parameter(Vector3 source)
        {
            // 3 floats + 3 bytes for types
#if !GTA_III
            byte[] array = new byte[5 * 3];

            // set data types
            array[0] = 0x06;
            array[5] = 0x06;
            array[10] = 0x06;

            int value = GTAUtils.ConvertFloatAsInt(source.X);

			array[1] = (byte)value;
			array[2] = (byte)(value >> 8);
			array[3] = (byte)(value >> 16);
			array[4] = (byte)(value >> 24);

            value = GTAUtils.ConvertFloatAsInt(source.Y);

            array[6] = (byte)value;
            array[7] = (byte)(value >> 8);
            array[8] = (byte)(value >> 16);
            array[9] = (byte)(value >> 24);

            value = GTAUtils.ConvertFloatAsInt(source.Z);

            array[11] = (byte)value;
            array[12] = (byte)(value >> 8);
            array[13] = (byte)(value >> 16);
            array[14] = (byte)(value >> 24);
#else
            // floats are only 2 bytes in III, youknow?
            byte[] array = new byte[3 * 3];

            array[0] = 0x06;
            array[3] = 0x06;
            array[6] = 0x06;

            short value = (short)(source.X * 16f);

            array[1] = (byte)value;
            array[2] = (byte)(value >> 8);

            value = (short)(source.Y * 16f);

            array[4] = (byte)value;
            array[5] = (byte)(value >> 8);

            value = (short)(source.Z * 16f);

            array[7] = (byte)value;
            array[8] = (byte)(value >> 8);
#endif

            var p = new Internal.Parameter(array);
            p._preVal = source.ToSVector();
            return p;
        }

        public SVector ToSVector()
        {
            return new SVector(X, Y, Z);
        }

#if GTA_SA
        public Vector3 ToScreenCoords()
        {
            var retval = NativeFunctions.GetScreenCoords(ToSVector());
            return new Vector3(retval);
        }
#endif

        public Vector3 GetClosestPathCoordinates(PathType type)
        {
            uint opcode = 0;

            switch (type)
            {
                case PathType.Car:
                    opcode = 0x02c1;
                    break;
                case PathType.Ped:
                    opcode = 0x02c0;
                    break;
            }

            VarPointer pX = new VarPointer();
            VarPointer pY = new VarPointer();
            VarPointer pZ = new VarPointer();

            Internal.Function.Call(opcode, this, pX, pY, pZ);

            return new Vector3((float)pX, (float)pY, (float)pZ);
        }

        public Vector3 GetClosestCarPathWithHeading(ref float heading)
        {
            VarPointer pX = new VarPointer();
            VarPointer pY = new VarPointer();
            VarPointer pZ = new VarPointer();
            VarPointer pA = new VarPointer();

            Internal.Function.Call(0x03d3, this, pX, pY, pZ, pA);

            heading = (float)pA;

            return new Vector3((float)pX, (float)pY, (float)pZ);
        }

        public override string ToString()
        {
            return string.Format("({0},{1},{2})", X, Y, Z);
        }
    }
}
