using System.Collections.Generic;

namespace GTA
{
    public class World
    {
        static World()
        {
            CarList = new List<Vehicle>();
            PedList = new List<Ped>();
        }

        public static Ped CreatePed(PedId model, Vector3 position, int pedtype) => CreatePed((int)model, position, pedtype);

        public static Vehicle CreateVehicle(CarId model, Vector3 position) => CreateVehicle((int)model, position);

        public static Ped CreatePed(Model model, Vector3 position, int pedtype)
        {
            if (model.Id >= 290 && model.Id <= 299)
            {
                return Internal.Function.Call<Ped>(0x009a, pedtype, model, position);
            }

            model.Load();
            var ped = Internal.Function.Call<Ped>(0x009a, pedtype, model, position);
            model.Release();

            return ped;
        }

        public static Vehicle CreateVehicle(Model model, Vector3 position)
        {
            model.Load();
            var car = Internal.Function.Call<Vehicle>(0x00a5, model, position);
            model.Release();

            return car;
        }

        public static Sphere CreateSphere(Vector3 position, float radius)
        {
            var sphere = Internal.Function.Call<Sphere>(0x03BC, position, radius);
            return sphere;
        }

        public static Vector3 GetGroundPosition(Vector3 position)
        {
            float z = Internal.Function.Call<float>(0x02CE, position);

            return new Vector3(position.X, position.Y, z);
        }

        static readonly List<Vehicle> CarList;

        public static List<Vehicle> GetAllVehicles()
        {
            var handles = Pool.Vehicle.GetAllHandles();
            //var vehicles = new List<Vehicle>();
            CarList.Clear();

            foreach (var handle in handles)
            {
                CarList.Add(ObjectCache.GetVehicle(handle));
            }

            return CarList;

#if LEGACYPOOL
            var retval = new List<Vehicle>();
            int ni = 0;

            for (int i = 0; i < 30000; i++, ni++)
            {
                var veh = new Vehicle(i);

                if (veh.IsDefined)
                {
                    retval.Add(veh);
                }

                if (ni > 3000)
                {
                    GTAUtils.Wait(0);
                    ni = 0;
                }
            }

            return retval;
#endif
        }

        static readonly List<Ped> PedList;

        public static List<Ped> GetAllPeds()
        {
            var handles = Pool.Ped.GetAllHandles();
            //var peds = new List<Ped>();
            PedList.Clear();

            foreach (var handle in handles)
            {
                PedList.Add(ObjectCache.GetPed(handle));
            }

            return PedList;

#if LEGACYPOOL
            var retval = new List<Ped>();
            int ni = 0;

            for (int i = 0; i < 30000; i++, ni++)
            {
                var ped = new Ped(i);

                if (ped.IsDefined)
                {
                    retval.Add(ped);
                }

                if (ni > 3000)
                {
                    GTAUtils.Wait(0);
                    ni = 0;
                }
            }

            return retval;
#endif
        }

        public static void SetInteriorAccess(string name, bool access)
        {
            Internal.Function.Call(0x07FB, name, access);
        }

        public static int Interior
        {
            get => Internal.Function.Call<int>(0x077E);
            set
            {
                Internal.Function.Call(0x057E, (value != 0)); // gray out radar if not exterior world
                Internal.Function.Call(0x04BB, value);
            }
        }
    }
}
