using System.Collections.Generic;

namespace GTA
{
    public class WeaponType
    {
        private readonly Ped _owner;

        internal WeaponType(Ped owner, WeaponId type)
        {
            Type = type;
            _owner = owner;
        }

        public WeaponId Type { get; }

        public int Ammo
        {
            get
            {
                if (!Internal.Function.Call(0x0491, _owner, (int)Type))
                {
                    return -1;
                }

                return Internal.Function.Call<int>(0x041a, _owner, (int)Type);
            }
            set
            {
                int type = (int)Type;

                if (Internal.Function.Call(0x0491, _owner, type))
                {
                    if (value == 0)
                    {
                        Internal.Function.Call(0x0555, _owner, type);
                    }
                    else
                    {
                        Internal.Function.Call(0x017b, _owner, type, value);
                    }
                }
                else
                {
                    if (value != 0)
                    {
                        Load();

                        Internal.Function.Call(0x01b2, _owner, type, value);
                    }
                }
            }
        }

        public void Load()
        {
            Model model = new Model(Model);
            model.Load();
        }

        public WeaponId Id => Type;

        public int Model
        {
            get
            {
                int modelId = Internal.Function.Call<int>(0x0781, (int)Type);

                return modelId;
            }
        }

        public int Slot
        {
            get
            {
                int slotId = Internal.Function.Call<int>(0x0782, (int)Type);

                return slotId;
            }
        }

        public void Select()
        {
            int type = (int)Type;

            if (!Internal.Function.Call(0x0491, _owner, type))
            {
                // TODO: perhaps use weapon in this weapon group?
                return;
            }

            Internal.Function.Call(0x01b9, _owner, type);
        }
    }

    public class WeaponsCollection
    {
        private readonly Ped _character;
        private Dictionary<WeaponId, WeaponType> _weaponCache;

        internal WeaponsCollection(Ped character)
        {
            _character = character;
        }

        public WeaponType FromId(WeaponId id)
        {
            WeaponType retval = null;

            if (_weaponCache == null)
            {
                _weaponCache = new Dictionary<WeaponId, WeaponType>();
            }
            else if (_weaponCache.TryGetValue(id, out retval))
            {
                return retval;
            }

            retval = new WeaponType(_character, id);
            _weaponCache.Add(id, retval);

            return retval;
        }

        public static implicit operator WeaponId(WeaponsCollection source)
        {
            return source.CurrentId;
        }

        public static implicit operator WeaponType(WeaponsCollection source)
        {
            return source.Current;
        }

        public void RemoveAll()
        {
            Internal.Function.Call(0x048f, _character);
        }

        public void Select(WeaponId weapon)
        {
            FromId(weapon).Select();
        }

        public WeaponType Current => FromId(Internal.Function.Call<WeaponId>(0x0470, _character));

        public WeaponId CurrentId => Internal.Function.Call<WeaponId>(0x0470, _character);

        public WeaponType FromSlot(int slot)
        {
            VarPointer type = new VarPointer();
            VarPointer dummy = new VarPointer();

            Internal.Function.Call(0x04B8, _character, slot, type, dummy, dummy);

            return this[(WeaponId)type.Value];
        }

        public WeaponType this[WeaponId id] => FromId(id);

        // generated from a helper tool
        public WeaponType GiftDildo1 => FromId(WeaponId.GiftDildo1);

        public WeaponType GiftDildo2 => FromId(WeaponId.GiftDildo2);

        public WeaponType GiftVibe1 => FromId(WeaponId.GiftVibe1);

        public WeaponType GiftVibe2 => FromId(WeaponId.GiftVibe2);

        public WeaponType GiftFlowers => FromId(WeaponId.GiftFlowers);

        public WeaponType GiftCane => FromId(WeaponId.GiftCane);

        public WeaponType MeleeUnarmed => FromId(WeaponId.MeleeUnarmed);

        public WeaponType MeleeBrassKnuckles => FromId(WeaponId.MeleeBrassKnuckles);

        public WeaponType MeleeGolfClub => FromId(WeaponId.MeleeGolfClub);

        public WeaponType MeleeNightstick => FromId(WeaponId.MeleeNightstick);

        public WeaponType MeleeKnife => FromId(WeaponId.MeleeKnife);

        public WeaponType MeleeBat => FromId(WeaponId.MeleeBat);

        public WeaponType MeleeShovel => FromId(WeaponId.MeleeShovel);

        public WeaponType MeleePoolCue => FromId(WeaponId.MeleePoolCue);

        public WeaponType MeleeKatana => FromId(WeaponId.MeleeKatana);

        public WeaponType MeleeChainsaw => FromId(WeaponId.MeleeChainsaw);

        public WeaponType ThrownGrenades => FromId(WeaponId.ThrownGrenades);

        public WeaponType ThrownTeargas => FromId(WeaponId.ThrownTeargas);

        public WeaponType ThrownMolotovs => FromId(WeaponId.ThrownMolotovs);

        public WeaponType ThrownSatchel => FromId(WeaponId.ThrownSatchel);

        public WeaponType SatchelDetonator => FromId(WeaponId.SatchelDetonator);

        public WeaponType PistolColt45 => FromId(WeaponId.PistolColt45);

        public WeaponType PistolSilenced => FromId(WeaponId.PistolSilenced);

        public WeaponType PistolDeagle => FromId(WeaponId.PistolDeagle);

        public WeaponType ShotgunShotgun => FromId(WeaponId.ShotgunShotgun);

        public WeaponType ShotgunSawnoff => FromId(WeaponId.ShotgunSawnoff);

        public WeaponType ShotgunSpas12 => FromId(WeaponId.ShotgunSpas12);

        public WeaponType SmgUzi => FromId(WeaponId.SmgUzi);

        public WeaponType SmgMp5 => FromId(WeaponId.SmgMp5);

        public WeaponType SmgTec9 => FromId(WeaponId.SmgTec9);

        public WeaponType AssaultAk47 => FromId(WeaponId.AssaultAk47);

        public WeaponType AssaultM4 => FromId(WeaponId.AssaultM4);

        public WeaponType RifleCountry => FromId(WeaponId.RifleCountry);

        public WeaponType RifleSniper => FromId(WeaponId.RifleSniper);

        public WeaponType HeavyRpg => FromId(WeaponId.HeavyRpg);

        public WeaponType HeavyHsrpg => FromId(WeaponId.HeavyHsrpg);

        public WeaponType HeavyFlamethrower => FromId(WeaponId.HeavyFlamethrower);

        public WeaponType HeavyMinigun => FromId(WeaponId.HeavyMinigun);

        public WeaponType MiscSpraycan => FromId(WeaponId.MiscSpraycan);

        public WeaponType MiscFireExt => FromId(WeaponId.MiscFireExt);

        public WeaponType MiscCamera => FromId(WeaponId.MiscCamera);

        public WeaponType ApparelNvGoggles => FromId(WeaponId.ApparelNvGoggles);

        public WeaponType ApparelThermGoggles => FromId(WeaponId.ApparelThermGoggles);

        public WeaponType ApparelParachute => FromId(WeaponId.ApparelParachute);
    }
}
