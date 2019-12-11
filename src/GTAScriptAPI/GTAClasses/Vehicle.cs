namespace GTA
{
    public enum VehicleSeat
    {
        Driver = -1,
        RightFront = 0,
        LeftRear = 1,
        RightRear = 2
    }

    public class Vehicle : HandleObject
    {
        #region HandleObject fuckups
        public Vehicle() { }
        public Vehicle(int handle) : base(handle) { }

        public static explicit operator Vehicle(int source) => new Vehicle(source);
        #endregion

        public void NoLongerNeeded()
        {
            Internal.Function.Call(0x01c3, this);
        }

        public void Delete()
        {
            Internal.Function.Call(0x00a6, this);
        }

        public void MakeProofTo(bool Bullets, bool Fire, bool Explosions, bool Collisions, bool MeleeAttacks)
        {
            Internal.Function.Call(0x02ac, this, Bullets, Fire, Explosions, Collisions, MeleeAttacks);
        }

        public Vector3 Position
        {
            get
            {
                VarPointer x = new VarPointer();
                VarPointer y = new VarPointer();
                VarPointer z = new VarPointer();

                Internal.Function.Call(0x00aa, this, x, y, z);

                return new Vector3((float)x, (float)y, (float)z);
            }
            set
            {
                Internal.Function.Call(0x00ab, this, value);
            }
        }

        public void SetImmuneToNonPlayer(bool value)
        {
            Internal.Function.Call(0x02AA, this, value);
        }

        public bool DamagedBy(Ped ped)
        {
            return Internal.Function.Call(0x051C, this, ped);
        }

        public bool DamagedBy(Vehicle car)
        {
            return Internal.Function.Call(0x051D, this, car);
        }

        public bool DamagedBy(WeaponID weapon)
        {
            return Internal.Function.Call(0x031E, this, (int)weapon);
        }

        public int Health
        {
            get
            {
                return Internal.Function.Call<int>(0x0227, this);
            }
            set
            {
                Internal.Function.Call(0x0224, this, value);
            }
        }

        public VehicleLock LockStatus
        {
            get
            {
                return (VehicleLock)Internal.Function.Call<int>(0x09B3, this);
            }
            set
            {
                Internal.Function.Call(0x020A, this, (int)value);
            }
        }

        public float Speed
        {
            get
            {
                return Internal.Function.Call<float>(0x02e3, this);
            }
            set
            {
                Internal.Function.Call(0x04ba, this, value);
            }
        }

        public float AISpeed
        {
            set
            {
                Internal.Function.Call(0x00ad, this, value);
            }
        }

        public float Heading
        {
            get
            {
                return Internal.Function.Call<float>(0x0174, this);
            }
            set
            {
                Internal.Function.Call(0x0175, this, value);
            }
        }

        public CarID Model
        {
            get
            {
                return (CarID)Internal.Function.Call<int>(0x0441, this);
            }
        }

        public bool IsAlive
        {
            get
            {
                return !Internal.Function.Call(0x0119, this);
            }
        }

        public bool IsDefined
        {
            get
            {
                return Internal.Function.Call(0x056e, this);
            }
        }
    }
}
