using System.Collections.Generic;

namespace GTA
{
    public static class ObjectCache
    {
        private static readonly Dictionary<int, Ped> _pedCache = new Dictionary<int, Ped>();
        private static readonly Dictionary<int, Vehicle> _vehicleCache = new Dictionary<int, Vehicle>();

        public static void AddPed(Ped p)
        {
            if (!_pedCache.ContainsKey(p.Handle))
            {
                _pedCache.Add(p.Handle, p);
            }
        }

        public static void AddVehicle(Vehicle p)
        {
            if (!_vehicleCache.ContainsKey(p.Handle))
            {
                _vehicleCache.Add(p.Handle, p);
            }
        }

        public static Ped GetPed(int handle)
        {
            Ped r = null;

            if (handle == 0 || handle == -1)
            {
                return r;
            }

            if (!_pedCache.TryGetValue(handle, out r))
            {
                r = new Ped(handle);
                AddPed(r);
            }

            return r;
        }

        public static Vehicle GetVehicle(int handle)
        {
            Vehicle r = null;

            if (handle == 0 || handle == -1)
            {
                return r;
            }

            if (!_vehicleCache.TryGetValue(handle, out r))
            {
                r = new Vehicle(handle);
                AddVehicle(r);
            }

            return r;
        }
    }
}
