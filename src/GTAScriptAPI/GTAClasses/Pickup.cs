using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public enum PickupType
    {
        PickupNever = 1,
        PickupOnce = 3,
        PickupRespawn = 15
    }

    public class PickupHandler : Script
    {
        static List<Pickup> _registeredPickups = new List<Pickup>();
        static List<Pickup> _unregisteredPickups = new List<Pickup>();

        internal static void Register(Pickup pickup)
        {
            _registeredPickups.Add(pickup);
        }

        internal static void Unregister(Pickup pickup)
        {
            _unregisteredPickups.Add(pickup);
        }

        public override void Run()
        {
            while (true)
            {
                this.Wait(0);

                try
                {
                    foreach (var pickup in _registeredPickups)
                    {
                        if (pickup.PickedUp)
                        {
                            pickup.InvokeOnPickedUp();
                        }
                    }

                    if (_unregisteredPickups.Count > 0)
                    {
                        foreach (var pickup in _unregisteredPickups)
                        {
                            _registeredPickups.Remove(pickup);
                        }

                        _unregisteredPickups.Clear();
                    }
                }
                catch (InvalidOperationException) { }
            }
        }
    }

    public class Pickup : HandleObject
    {
        private Vector3 _origPos;

        public static Pickup CreatePickup(Vector3 position, Model model, PickupType type)
        {
            model.Load();

            var retval = Internal.Function.Call<Pickup>(0x0213, model, (int)type, position);
            PickupHandler.Register(retval);

            model.Release();

            retval._origPos = position;
            return retval;
        }

#if !GTA_IV
        public static Pickup CreateCashPickup(Vector3 position, int maxCash, bool permanent)
        {
            var retval = Internal.Function.Call<Pickup>(0x02E1, position, maxCash, permanent);
            PickupHandler.Register(retval);

            retval._origPos = position;
            return retval;
        }
#endif

        public static Pickup CreatePickup(Vector3 position, WeaponID weaponType, int ammo)
        {
            var weapon = new WeaponType(null, weaponType);
            var model = weapon.Model;
            var group = weapon.Slot;

            if (group == 11 || group == 1 || group == 2)
            {
                return Pickup.CreatePickup(position, model, PickupType.PickupRespawn);
            }

            var retval = Internal.Function.Call<Pickup>(0x032B, model, group, ammo, position);
            PickupHandler.Register(retval);

            retval._origPos = position;
            return retval;
        }

        public void Delete()
        {
            Internal.Function.Call(0x0215, this);
            PickupHandler.Unregister(this);
        }

        public event EventHandler OnPickedUp;

        internal void InvokeOnPickedUp()
        {
            if (OnPickedUp != null)
            {
                OnPickedUp(this, EventArgs.Empty);
            }
        }

        public bool PickedUp
        {
            get
            {
                return Internal.Function.Call(0x0214, this);
            }
        }

#if GTA_SA
        public int Money
        {
            set
            {
                Internal.Function.Call(0x094a, this, value);
            }
        }
#endif

        public Vector3 Position
        {
            get
            {
                return this._origPos;
            }
        }
    }
}
