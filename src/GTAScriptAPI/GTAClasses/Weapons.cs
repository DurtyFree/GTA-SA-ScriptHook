using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class WeaponType
    {
        private Ped owner;
        private WeaponID type;

        internal WeaponType(Ped owner, WeaponID type)
        {
            this.type = type;
            this.owner = owner;
        }

        public WeaponID Type
        {
            get
            {
                return type;
            }
        }

        public int Ammo
        {
            get
            {
                if (!Internal.Function.Call(0x0491, owner, (int)type))
                {
                    return -1;
                }

                return Internal.Function.Call<int>(0x041a, owner, (int)type);
            }
            set
            {
                int type = (int)this.type;

                if (Internal.Function.Call(0x0491, owner, type))
                {
                    if (value == 0)
                    {
                        Internal.Function.Call(0x0555, owner, type);
                    }
                    else
                    {
                        Internal.Function.Call(0x017b, owner, type, value);
                    }
                }
                else
                {
                    if (value != 0)
                    {
                        Load();

                        Internal.Function.Call(0x01b2, owner, type, value);
                    }
                }
            }
        }

        public void Load()
        {
            Model model = new Model(Model);
            model.Load();
        }

        public WeaponID ID
        {
            get
            {
                return type;
            }
        }

        public int Model
        {
            get
            {
                int modelID = Internal.Function.Call<int>(0x0781, (int)type);

                return modelID;
            }
        }

        public int Slot
        {
            get
            {
                int slotID = Internal.Function.Call<int>(0x0782, (int)type);

                return slotID;
            }
        }

        public void Select()
        {
            int type = (int)this.type;

            if (!Internal.Function.Call(0x0491, owner, type))
            {
                // TODO: perhaps use weapon in this weapon group?
                return;
            }

            Internal.Function.Call(0x01b9, owner, type);
        }
    }

    public class WeaponsCollection
    {
        private Ped character;
        private Dictionary<WeaponID, WeaponType> weaponCache;

        internal WeaponsCollection(Ped character)
        {
            this.character = character;
        }

        public WeaponType FromID(WeaponID id)
        {
            WeaponType retval = null;

            if (weaponCache == null)
            {
                weaponCache = new Dictionary<WeaponID, WeaponType>();
            }
            else if (weaponCache.TryGetValue(id, out retval))
            {
                return retval;
            }

            retval = new WeaponType(character, id);
            weaponCache.Add(id, retval);

            return retval;
        }

        public static implicit operator WeaponID(WeaponsCollection source)
        {
            return source.CurrentID;
        }

        public static implicit operator WeaponType(WeaponsCollection source)
        {
            return source.Current;
        }

        public void RemoveAll()
        {
            Internal.Function.Call(0x048f, character);
        }

        public void Select(WeaponID weapon)
        {
            FromID(weapon).Select();
        }

        public WeaponType Current
        {
            get
            {
                return FromID(GTA.Internal.Function.Call<WeaponID>(0x0470, character));
            }
        }

        public WeaponID CurrentID
        {
            get
            {
                return GTA.Internal.Function.Call<WeaponID>(0x0470, character);
            }
        }

        public WeaponType FromSlot(int slot)
        {
            VarPointer type = new VarPointer();
            VarPointer dummy = new VarPointer();

            Internal.Function.Call(0x04B8, character, slot, type, dummy, dummy);

            return this[(WeaponID)type.Value];
        }

        public WeaponType this[WeaponID id]
        {
            get
            {
                return FromID(id);
            }
        }

        // generated from a helper tool
        public WeaponType Gift_Dildo1
        {
            get
            {
                return FromID(WeaponID.Gift_Dildo1);
            }
        }

        public WeaponType Gift_Dildo2
        {
            get
            {
                return FromID(WeaponID.Gift_Dildo2);
            }
        }

        public WeaponType Gift_Vibe1
        {
            get
            {
                return FromID(WeaponID.Gift_Vibe1);
            }
        }

        public WeaponType Gift_Vibe2
        {
            get
            {
                return FromID(WeaponID.Gift_Vibe2);
            }
        }

        public WeaponType Gift_Flowers
        {
            get
            {
                return FromID(WeaponID.Gift_Flowers);
            }
        }

        public WeaponType Gift_Cane
        {
            get
            {
                return FromID(WeaponID.Gift_Cane);
            }
        }

        public WeaponType Melee_Unarmed
        {
            get
            {
                return FromID(WeaponID.Melee_Unarmed);
            }
        }

        public WeaponType Melee_BrassKnuckles
        {
            get
            {
                return FromID(WeaponID.Melee_BrassKnuckles);
            }
        }

        public WeaponType Melee_GolfClub
        {
            get
            {
                return FromID(WeaponID.Melee_GolfClub);
            }
        }

        public WeaponType Melee_Nightstick
        {
            get
            {
                return FromID(WeaponID.Melee_Nightstick);
            }
        }

        public WeaponType Melee_Knife
        {
            get
            {
                return FromID(WeaponID.Melee_Knife);
            }
        }

        public WeaponType Melee_Bat
        {
            get
            {
                return FromID(WeaponID.Melee_Bat);
            }
        }

        public WeaponType Melee_Shovel
        {
            get
            {
                return FromID(WeaponID.Melee_Shovel);
            }
        }

        public WeaponType Melee_PoolCue
        {
            get
            {
                return FromID(WeaponID.Melee_PoolCue);
            }
        }

        public WeaponType Melee_Katana
        {
            get
            {
                return FromID(WeaponID.Melee_Katana);
            }
        }

        public WeaponType Melee_Chainsaw
        {
            get
            {
                return FromID(WeaponID.Melee_Chainsaw);
            }
        }

        public WeaponType Thrown_Grenades
        {
            get
            {
                return FromID(WeaponID.Thrown_Grenades);
            }
        }

        public WeaponType Thrown_Teargas
        {
            get
            {
                return FromID(WeaponID.Thrown_Teargas);
            }
        }

        public WeaponType Thrown_Molotovs
        {
            get
            {
                return FromID(WeaponID.Thrown_Molotovs);
            }
        }

        public WeaponType Thrown_Satchel
        {
            get
            {
                return FromID(WeaponID.Thrown_Satchel);
            }
        }

        public WeaponType Satchel_Detonator
        {
            get
            {
                return FromID(WeaponID.Satchel_Detonator);
            }
        }

        public WeaponType Pistol_Colt45
        {
            get
            {
                return FromID(WeaponID.Pistol_Colt45);
            }
        }

        public WeaponType Pistol_Silenced
        {
            get
            {
                return FromID(WeaponID.Pistol_Silenced);
            }
        }

        public WeaponType Pistol_Deagle
        {
            get
            {
                return FromID(WeaponID.Pistol_Deagle);
            }
        }

        public WeaponType Shotgun_Shotgun
        {
            get
            {
                return FromID(WeaponID.Shotgun_Shotgun);
            }
        }

        public WeaponType Shotgun_Sawnoff
        {
            get
            {
                return FromID(WeaponID.Shotgun_Sawnoff);
            }
        }

        public WeaponType Shotgun_SPAS12
        {
            get
            {
                return FromID(WeaponID.Shotgun_SPAS12);
            }
        }

        public WeaponType SMG_Uzi
        {
            get
            {
                return FromID(WeaponID.SMG_Uzi);
            }
        }

        public WeaponType SMG_MP5
        {
            get
            {
                return FromID(WeaponID.SMG_MP5);
            }
        }

        public WeaponType SMG_Tec9
        {
            get
            {
                return FromID(WeaponID.SMG_Tec9);
            }
        }

        public WeaponType Assault_AK47
        {
            get
            {
                return FromID(WeaponID.Assault_AK47);
            }
        }

        public WeaponType Assault_M4
        {
            get
            {
                return FromID(WeaponID.Assault_M4);
            }
        }

        public WeaponType Rifle_Country
        {
            get
            {
                return FromID(WeaponID.Rifle_Country);
            }
        }

        public WeaponType Rifle_Sniper
        {
            get
            {
                return FromID(WeaponID.Rifle_Sniper);
            }
        }

        public WeaponType Heavy_RPG
        {
            get
            {
                return FromID(WeaponID.Heavy_RPG);
            }
        }

        public WeaponType Heavy_HSRPG
        {
            get
            {
                return FromID(WeaponID.Heavy_HSRPG);
            }
        }

        public WeaponType Heavy_Flamethrower
        {
            get
            {
                return FromID(WeaponID.Heavy_Flamethrower);
            }
        }

        public WeaponType Heavy_Minigun
        {
            get
            {
                return FromID(WeaponID.Heavy_Minigun);
            }
        }

        public WeaponType Misc_Spraycan
        {
            get
            {
                return FromID(WeaponID.Misc_Spraycan);
            }
        }

        public WeaponType Misc_FireExt
        {
            get
            {
                return FromID(WeaponID.Misc_FireExt);
            }
        }

        public WeaponType Misc_Camera
        {
            get
            {
                return FromID(WeaponID.Misc_Camera);
            }
        }

        public WeaponType Apparel_NVGoggles
        {
            get
            {
                return FromID(WeaponID.Apparel_NVGoggles);
            }
        }

        public WeaponType Apparel_ThermGoggles
        {
            get
            {
                return FromID(WeaponID.Apparel_ThermGoggles);
            }
        }

        public WeaponType Apparel_Parachute
        {
            get
            {
                return FromID(WeaponID.Apparel_Parachute);
            }
        }
    }
}
