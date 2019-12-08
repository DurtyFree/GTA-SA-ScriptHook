using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    class DeferredScript : TickScript
    {
        Action _action;
        public string Source { get; set; }

        public DeferredScript()
        {
            Tick += new EventHandler(this.DeferredScript_OnTick);
            this.Interval = 100;
        }

        public void Assign(Action action)
        {
            this._action = action;
        }

        void DeferredScript_OnTick(object sender, EventArgs e)
        {
            if (this._action == null)
            {
                return;
            }

            try
            {
                this._action();
            }
            catch (Exception ex)
            {
                GTA.Game.DisplayTextBox("A deferred script caused an exception.");

                Initialize.Log("Exception caused in deferred script: " + ex.ToString());
            }

            this._action = null;
        }

        public bool Busy
        {
            get
            {
                return (this._action == null) ? false : true;
            }
        }
    }

    public class Defer : TickScript
    {
        static List<Action> Actions { get; set; }
        static List<DeferredScript> Workers = new List<DeferredScript>();

        public Defer()
        {
            Actions = new List<Action>();
            Tick += new EventHandler(this.Defer_OnTick);

            for (int i = 0; i < 5; i++)
            {
                var ds = new DeferredScript();
                Workers.Add(ds);

                ScriptLoader.LoadScript(ds);
            }
        }

        public static void DeferScript(Action action)
        {
            //Actions.Add(action);
            bool assigned = false;

            foreach (var worker in Workers)
            {
                if (worker.Busy)
                {
                    continue;
                }

                //worker.Source = new System.Diagnostics.StackTrace().GetFrame(0);
                var trace = new System.Diagnostics.StackTrace();
                foreach (var frame in trace.GetFrames())
                {
                    var method = frame.GetMethod();
                    if (method.Name.Equals("DeferScript"))
                    {
                        continue;
                    }

                    worker.Source = string.Format("{0}::{1}",
                        method.ReflectedType != null ? method.ReflectedType.Name : string.Empty,
                        method.Name);

                    break;
                }
                worker.Assign(action);

                assigned = true;
                break;
            }

            if (!assigned)
            {
                var ds = new DeferredScript();
                Workers.Add(ds);

                ScriptLoader.LoadScript(ds);

                ds.Assign(action);
            }
        }

        public static List<string> WorkerData = new List<string>();

        void Defer_OnTick(object sender, EventArgs e)
        {
            WorkerData.Clear();

            int i = 0;

            foreach (var worker in Workers)
            {
                string d = "Worker " + i.ToString();

                if (worker.Busy)
                {
                    d += " - assigned: " + worker.Source;
                }
                else
                {
                    d += " - free";
                }

                i++;

                WorkerData.Add(d);
            }

            try
            {
                foreach (var action in Actions)
                {
                    try
                    {
                        action();
                    }
                    catch (Exception ex)
                    {
                        GTA.Game.DisplayTextBox("A deferred script caused an exception.");

                        Initialize.Log("Exception caused in deferred script: " + ex.ToString());
                    }
                }

                Actions.Clear();
            }
            catch (InvalidOperationException) { }
        }
    }
}
