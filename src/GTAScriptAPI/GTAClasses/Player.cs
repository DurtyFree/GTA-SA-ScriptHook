using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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
        public void ForceWeapon(WeaponID type)
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

        public bool Defined
        {
            get
            {
                return Internal.Function.Call(0x0256, this);
            }
        }

        public Group Group
        {
            get
            {
                return Group.FromPlayer(this);
            }
        }

        public bool Driveby
        {
            set
            {
                if (value)
                {
                    Character.Tasks.DriveBy();
                    GTA.Internal.Function.Call(0x0501, this, true);
                }
                else
                {
                    GTA.Internal.Function.Call(0x0501, this, false);
                    Character.Tasks.ClearAll();
                }
            }
        }

        public int Money
        {
            get
            {
                return Internal.Function.Call<int>(0x010b, this);
            }
        }

        public bool CanControlCharacter
        {
            get
            {
                return Internal.Function.Call(0x03EE, this);
            }
            set
            {
                Internal.Function.Call(0x01B4, this, value);
            }
        }

        public bool IgnoredByEveryone
        {
            set
            {
                Internal.Function.Call(0x03BF, this, value);
            }
        }

        public int WantedLevel
        {
            get
            {
                return Internal.Function.Call<int>(0x01c0, this);
            }
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
            get
            {
                return Internal.Function.Call<int>(0x050F);
            }
            set
            {
                if (value <= 6)
                {
                    Internal.Function.Call(0x01f0, value);
                }
            }
        }

        public PedID Model
        {
            set
            {
                if (value == PedID.@null || (value >= PedID.special01 && value <= PedID.special10))
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
