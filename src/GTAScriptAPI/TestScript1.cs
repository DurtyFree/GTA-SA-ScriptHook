using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GTA.Internal;

#if st
namespace GTA
{
    public class TestScript1 : TickScript
    {
        public TestScript1()
        {
            Tick += new EventHandler(TestScript1_Tick);
        }

        void TestScript1_Tick(object sender, EventArgs e)
        {
            Pickup.CreatePickup(new Vector3(1.23f, 1.23f, 1.23f), WeaponID.Assault_AK47, 500);

            if (myPed == null)
            {
                myPed = World.CreatePed(PedID.WFYSEX, Player.Character.Position.Around(10), 23);
                myBlip = Blip.AddBlip(myPed);
                myBlip.Color = BlipColor.Pickup;

                Player.Character.Weapons[WeaponID.Assault_M4].Load();
                Player.Character.Weapons[WeaponID.Assault_M4].Ammo = 200;
                Player.Character.Weapons[WeaponID.Assault_M4].Select();
            }

            if (!myPed.IsAlive)
            {
                myBlip.Delete();
                myPed = null;
            }
        }

        Ped myPed = null;
        Blip myBlip = null;
    }
}

namespace GTA
{
    public class TestScript1 : Script
    {
        public override void Run()
        {
            Ped myPed = null;
            Blip myBlip = null;

            while (true)
            {
                Wait(0);

                if (myPed == null)
                {
                    myPed = World.CreatePed(PedID.WFYSEX, Player.Character.Position.Around(10), 23);
                    myBlip = Blip.AddBlip(myPed);
                    myBlip.Color = BlipColor.Pickup;

                    Player.Character.Weapons[WeaponID.Assault_M4].Load();
                    Player.Character.Weapons[WeaponID.Assault_M4].Ammo = 200;
                    Player.Character.Weapons[WeaponID.Assault_M4].Select();
                }

                if (!myPed.IsAlive)
                {
                    myBlip.Delete();
                    myPed = null;
                }
            }
        }
    }
}
#endif