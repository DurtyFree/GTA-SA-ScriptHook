namespace GTA
{
    public class Player : HandleObject
    {
        #region HandleObject fuckups
        public Player() { }
        public Player(int handle) : base(handle) { }

        public static explicit operator Player(int source)
        {
            return new Player(source);
        }
        #endregion

        public Ped Character { get; set; }

#if GTA_SA
        public void ForceWeapon(WeaponId type)
        {
            var weapon = new WeaponType(null, type);
            GTAUtils.SetPlayerWeaponSlot(weapon.Slot);
        }
#endif

        public void AddMoney(int amount)
        {
            Internal.Function.Call(0x0109, this, amount);
        }

        public void SetWantedLevelNoDrop(int level)
        {
            if (level <= 6 && level > 0)
            {
                Internal.Function.Call(0x010e, this, level);
            }
        }

        public bool Defined => Internal.Function.Call(0x0256, this);

        public Group Group => Group.FromPlayer(this);

        public bool Driveby
        {
            set
            {
                if (value)
                {
                    this.Character.Tasks.DriveBy();
                    Internal.Function.Call(0x0501, this, true);
                }
                else
                {
                    Internal.Function.Call(0x0501, this, false);
                    this.Character.Tasks.ClearAll();
                }
            }
        }

        public int Money => Internal.Function.Call<int>(0x010b, this);

        public bool IsInVehicle => this.Character?.CurrentVehicle != null;

        public bool CanControlCharacter
        {
            get => Internal.Function.Call(0x03EE, this);
            set => Internal.Function.Call(0x01B4, this, value);
        }

        public bool IgnoredByEveryone
        {
            set => Internal.Function.Call(0x03BF, this, value);
        }

        public int WantedLevel
        {
            get => Internal.Function.Call<int>(0x01c0, this);
            set
            {
                if (value <= 6)
                {
                    Internal.Function.Call(0x010d, this, value);
                }
            }
        }

        public int MaximumWantedLevel
        {
            get => Internal.Function.Call<int>(0x050F);
            set
            {
                if (value <= 6)
                {
                    Internal.Function.Call(0x01f0, value);
                }
            }
        }

        public PedId Model
        {
            set
            {
                if (value == PedId.Null || (value >= PedId.Special01 && value <= PedId.Special10))
                {
                    Internal.Function.Call(0x09C7, this, (int)value);
                }

                GTA.Model.Load((int)value);
                Internal.Function.Call(0x09C7, this, (int)value);
                GTA.Model.Release((int)value);
            }
        }
    }
}
