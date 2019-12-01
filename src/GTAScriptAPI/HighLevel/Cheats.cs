using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class Cheats : Script
    {
        static Cheats()
        {
            lastKeys = new byte[256];
            registeredCheats = new List<Cheat>();
        }

        public Cheats()
        {
            my = this;
        }

        class Cheat
        {
            public string name;
            public Action callback;
        }

        static Cheats my;

        static List<Cheat> registeredCheats;

        static byte[] lastKeys;
        static string textBuffer = "";

        public override void Run()
        {
            while (true)
            {
                Wait(0);

                BuildBuffer();
                CheckRegistry();
            }
        }

        public static void SpawnVehicle(CarID carID)
        {
            var position = my.Player.Character.Position.Around(5);

            Log.Debug("position read: " + position.ToString());

            var car = World.CreateVehicle(carID, position);

            Log.Debug("position car: " + car.Position.ToString());
            car.LockStatus = VehicleLock.Unlocked;
            car.NoLongerNeeded();
        }

        public static void SpawnPed(PedID pedID)
        {
            var position = my.Player.Character.Position.Around(5);

            var ped = World.CreatePed(pedID, position, 24);
            ped.Tasks.Wander();
            ped.NoLongerNeeded();
        }

        public static void RegisterCheat(string name, Action callback)
        {
            registeredCheats.Add(new Cheat() { name = name.ToUpper(), callback = callback });
        }

        void CheckRegistry()
        {
            foreach (var cheat in registeredCheats)
            {
                if (textBuffer.EndsWith(cheat.name))
                {
                    try
                    {
                        cheat.callback();
                        Game.DisplayTextBox("Cheat activated");
                    }
                    catch (Exception e)
                    {
                        Game.DisplayTextBox("Cheat failed");
                        Log.Error(e);
                    }

                    textBuffer = "";
                }
            }
        }

        void BuildBuffer()
        {
            var keys = ScriptProcessor.Instance.KeyBuffer;
            for (int i = 0x30; i <= 0x5A; i++)
            {
                if (keys[i] != 0 && lastKeys[i] == 0)
                {
                    textBuffer += (char)i;
                }
            }

            Array.Copy(keys, lastKeys, 256);

            if (textBuffer.Length > 25)
            {
                textBuffer = textBuffer.Substring(1, 25);
            }
        }
    }
}
