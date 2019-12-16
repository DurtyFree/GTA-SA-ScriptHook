using GTA.GTAClasses.DataTypes;

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

        public bool SetInvisible(bool state) => this.OpCodeCallOnHandle(OpCodes.SET_CAR_VISIBLE, state);

        public bool SetHeavy(bool state) => this.OpCodeCallOnHandle(OpCodes.SET_CAR_HEAVY, state);

        public bool Explode() => this.OpCodeCallOnHandle(OpCodes.EXPLODE_CAR);

        public void DriveToCoords(float x, float y, float z) => this.OpCodeCallOnHandle(OpCodes.CAR_GOTO_COORDINATES, x, y, z);

        public int GetMaxNumbersOfPassengers() => this.OpCodeCallOnHandle<int>(OpCodes.GET_MAXIMUM_NUMBER_OF_PASSENGERS);

        public void MakeImmunefTo(bool bullets, bool fire, bool explosions, bool collisions, bool meleeAttacks)
            => OpCode.Call(OpCodes.SET_CAR_PROOFS, this, bullets, fire, explosions, collisions, meleeAttacks);

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
            set => Internal.Function.Call(0x00ab, this, value);
        }

        public void SetImmuneToNonPlayer(bool value) => this.OpCodeCallOnHandle(OpCodes.SET_CAR_ONLY_DAMAGED_BY_PLAYER, value);

        public bool DamagedBy(Ped ped)
        {
            return Internal.Function.Call(0x051C, this, ped);
        }

        public bool DamagedBy(Vehicle car)
        {
            return Internal.Function.Call(0x051D, this, car);
        }

        public bool DamagedBy(WeaponId weapon)
        {
            return Internal.Function.Call(0x031E, this, (int)weapon);
        }

        public int Health
        {
            get => this.OpCodeCallOnHandle<int>(OpCodes.GET_CAR_HEALTH);
            set => this.OpCodeCallOnHandle(OpCodes.SET_CAR_HEALTH, value);
        }

        public LockDoorTyp LockStatus
        {
            get => (LockDoorTyp)this.OpCodeCallOnHandle<int>(OpCodes.GET_CAR_DOOR_LOCK_STATUS);
            set => this.OpCodeCallOnHandle(OpCodes.LOCK_CAR_DOORS, (int)value);
        }

        public float Speed
        {
            get => Internal.Function.Call<float>(0x02e3, this);
            set => Internal.Function.Call(0x04ba, this, value);
        }

        public float AiSpeed
        {
            set => Internal.Function.Call(0x00ad, this, value);
        }

        public float Heading
        {
            get => Internal.Function.Call<float>(0x0174, this);
            set => Internal.Function.Call(0x0175, this, value);
        }

        public CarId Model => (CarId)Internal.Function.Call<int>(0x0441, this);

        public bool IsAlive => !Internal.Function.Call(0x0119, this);

        public bool IsDefined => Internal.Function.Call(0x056e, this);

        public bool IsInWater => this.OpCodeCallOnHandle<bool>(OpCodes.IS_CAR_IN_WATER);
    }
}
