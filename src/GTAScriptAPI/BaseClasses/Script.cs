﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GTA.Internal;

namespace GTA
{
    public class Script : BaseScript
    {
        public Player Player { get; set; }

        public override void OnStart() {
#if !GTA_SCO
            this.Player = (Player)new Player(GlobalVariable.Get(2).Value);
#if GTA_SA
            this.Player.Character = (Ped)new Ped(GlobalVariable.Get(3).Value);
#endif
#if GTA_III
            Player.Character = (Ped)new Ped(GlobalVariable.Get(11).Value);
#endif
#else
            Player = new Player();
            Player.Character = new Ped();
#endif
        }
    }

    public class TickScript : Script
    {
        public int Interval { get; set; }
        public event EventHandler Tick;

        public TickScript()
        {
            this.Interval = 100;
        }

        public override void Run()
        {
            while (true)
            {
                this.ProcessKeyBindings();
                this.OnTick();

                this.Wait(this.Interval);
            }
        }

        public virtual void OnTick()
        {
            if (Tick != null)
            {
                Tick(this, EventArgs.Empty);
            }
        }
    }
}
