using System.Collections.Generic;

namespace GTA
{
    public class World
    {
        static World()
        {
            carList = new List<Vehicle>();
            pedList = new List<Ped>();
        }

        public static Ped CreatePed(PedID model, Vector3 position, int pedtype) => CreatePed((int)model, position, pedtype);

        public static Vehicle CreateVehicle(CarID model, Vector3 position) => CreateVehicle((int)model, position);

        public static Ped CreatePed(Model model, Vector3 position, int pedtype)
        {
            if (model.ID >= 290 && model.ID <= 299)
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

        static readonly List<Vehicle> carList;

        public static List<Vehicle> GetAllVehicles()
        {
            var handles = Pool.Vehicle.GetAllHandles();
            //var vehicles = new List<Vehicle>();
            carList.Clear();

            foreach (var handle in handles)
            {
                carList.Add(ObjectCache.GetVehicle(handle));
            }

            return carList;

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

        static readonly List<Ped> pedList;

        public static List<Ped> GetAllPeds()
        {
            var handles = Pool.Ped.GetAllHandles();
            //var peds = new List<Ped>();
            pedList.Clear();

            foreach (var handle in handles)
            {
                pedList.Add(ObjectCache.GetPed(handle));
            }

            return pedList;

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
            get
            {
                return Internal.Function.Call<int>(0x077E);
            }
            set
            {
                Internal.Function.Call(0x057E, (value != 0)); // gray out radar if not exterior world
                Internal.Function.Call(0x04BB, value);
            }
        }
    }
}
