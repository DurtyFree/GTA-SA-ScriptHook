using System;
using System.Collections.Generic;
using GTA.GTAClasses.DataTypes;

namespace GTA
{
    public class Cheats : Script
    {
        static Cheats()
        {
            _lastKeys = new byte[256];
            _registeredCheats = new List<Cheat>();
        }

        public Cheats()
        {
            _my = this;
        }

        class Cheat
        {
            public string Name;
            public Action Callback;
        }

        static Cheats _my;

        static readonly List<Cheat> _registeredCheats;

        static readonly byte[] _lastKeys;
        static string _textBuffer = "";

        public override void Run()
        {
            while (true)
            {
                Wait(0);

                BuildBuffer();
                CheckRegistry();
            }
        }

        public static void SpawnVehicle(CarId carId)
        {
            var position = _my.Player.Character.Position.Around(5);

            Log.Debug("position read: " + position.ToString());

            var car = World.CreateVehicle(carId, position);

            Log.Debug("position car: " + car.Position.ToString());
            car.LockStatus = LockDoorTyp.Unlocked;
            car.NoLongerNeeded();
        }

        public static void SpawnPed(PedId pedId)
        {
            var position = _my.Player.Character.Position.Around(5);

            var ped = World.CreatePed(pedId, position, 24);
            ped.Tasks.Wander();
            ped.NoLongerNeeded();
        }

        public static void RegisterCheat(string name, Action callback)
        {
            _registeredCheats.Add(new Cheat() { Name = name.ToUpper(), Callback = callback });
        }

        void CheckRegistry()
        {
            foreach (var cheat in _registeredCheats)
            {
                if (_textBuffer.EndsWith(cheat.Name))
                {
                    try
                    {
                        cheat.Callback();
                        Game.DisplayTextBox("Cheat activated");
                    }
                    catch (Exception e)
                    {
                        Game.DisplayTextBox("Cheat failed");
                        Log.Error(e);
                    }

                    _textBuffer = "";
                }
            }
        }

        void BuildBuffer()
        {
            var keys = ScriptProcessor.Instance.KeyBuffer;
            for (int i = 0x30; i <= 0x5A; i++)
            {
                if (keys[i] != 0 && _lastKeys[i] == 0)
                {
                    _textBuffer += (char)i;
                }
            }

            Array.Copy(keys, _lastKeys, 256);

            if (_textBuffer.Length > 25)
            {
                _textBuffer = _textBuffer.Substring(1, 25);
            }
        }
    }
}
