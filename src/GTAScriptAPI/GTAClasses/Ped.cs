namespace GTA
{
    public class Ped : HandleObject
    {
        #region HandleObject fuckups
        public Ped() { }
        public Ped(int handle) : base(handle) { }

        public static explicit operator Ped(int source) => new Ped(source);
        #endregion

        private PedTasks _tasks;
        private WeaponsCollection _weapons;

        public WeaponsCollection Weapons
        {
            get
            {
                if (_weapons == null)
                {
                    _weapons = new WeaponsCollection(this);
                }

                return _weapons;
            }
        }

        public PedTasks Tasks
        {
            get
            {
                if (_tasks == null)
                {
                    _tasks = new PedTasks(this);
                }

                return _tasks;
            }
        }

        public Vector3 Position
        {
            get
            {
                VarPointer x = new VarPointer();
                VarPointer y = new VarPointer();
                VarPointer z = new VarPointer();

                Internal.Function.Call(0x00a0, this, x, y, z);

                return new Vector3((float)x, (float)y, (float)z);
            }
            set => Internal.Function.Call(0x00a1, this, value);
        }

        public int Health
        {
            get => Internal.Function.Call<int>(0x0226, this);
            set => Internal.Function.Call(0x0223, this, value);
        }

        public int Armor
        {
            get => Internal.Function.Call<int>(0x04DD, this);
            set => Internal.Function.Call(0x035F, this, value);
        }

        public float Heading
        {
            get => Internal.Function.Call<float>(0x0172, this);
            set => Internal.Function.Call(0x0173, this, value);
        }

        public void MakeProofTo(bool bullets, bool fire, bool explosions, bool collisions, bool meleeAttacks)
        {
            Internal.Function.Call(0x02ab, this, bullets, fire, explosions, collisions, meleeAttacks);
        }

        public void Delete()
        {
            Internal.Function.Call(0x009b, this);
        }

        public void NoLongerNeeded()
        {
            Internal.Function.Call(0x01c2, this);
        }

        public void AddToGroup(Group group)
        {
            group.AddPed(this, false);
        }

        public void RemoveFromGroup()
        {
            Internal.Function.Call(0x06c9, this);
        }

        public bool InSphere(Vector3 position, Vector3 radius)
        {
#if !GTA_IV
            return Internal.Function.Call(0x00fe, this, position, radius, false);
#else
            return (Position.DistanceTo(position) < radius.pX);
#endif
        }

        public bool IsDriving => Internal.Function.Call(0x0449, this);

        public bool IsAlive => !Internal.Function.Call(0x0118, this);

        public bool IsArrested
        {
            get
            {
#if !GTA_IV
                return Internal.Function.Call(0x0741, this);
#else
                return Internal.Function.Call("IS_PLAYER_BEING_ARRESTED");
#endif
            }
        }

        public bool IsDefined => Internal.Function.Call(0x056d, this);

        public PedId Model => (PedId)Internal.Function.Call<int>(0x0665, this);

        public Vehicle CurrentVehicle => Internal.Function.Call<Vehicle>(0x03c0, this);

        public int Interior
        {
            get => Internal.Function.Call<int>(0x09E8, this);
            set => Internal.Function.Call(0x0860, this, value);
        }

        public void Lock(bool enabled)
        {
            Internal.Function.Call(0x04d7, this, enabled);
        }

        public void SetWeaponAccuracy(int value)
        {
            Internal.Function.Call(0x02E2, this, value);
        }

        public bool DamagedBy(Ped ped)
        {
#if !GTA_IV
            return Internal.Function.Call(0x051A, this, ped);
#else
            return Internal.Function.Call("HAS_CHAR_BEEN_DAMAGED_BY_CHAR", this, ped, false);
#endif
        }

        public bool DamagedBy(Vehicle car)
        {
            return Internal.Function.Call(0x051B, this, car);
        }

        public bool DamagedBy(WeaponId weapon)
        {
            return Internal.Function.Call(0x031D, this, (int)weapon);
        }
    }
}
