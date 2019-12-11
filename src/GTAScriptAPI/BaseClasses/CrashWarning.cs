using System;

namespace GTA
{
    public class CrashWarning : ScriptPostInitializer
    {
        public override void OnGameStart()
        {
            ScriptProcessor.Instance.ScriptCrashed += new Action<BaseScript, Exception>(Instance_ScriptCrashed);
        }

        void Instance_ScriptCrashed(BaseScript script, Exception exception)
        {
            Game.DisplayTextBox("Script " + script.GetType().Name + " crashed. Check the log for details.");
        }
    }
}
