using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class BaseConsole : Script
    {
        public override void Run()
        {
            var version = new ConsoleCommand("version", delegate (string[] args)
            {
                Console.Print("GTAScriptHook v" + ScriptProcessor.HookVersion);

                // TODO: allow scripts to register versions
            });

            version.HelpText = "Shows the version of the script hook and other scripts";
            Console.Register(version);

            var spawnV = new ConsoleCommand("spawn_vehicle", delegate(string[] args)
            {
                var modelName = args[0];

                if (Model.IsKnown(modelName))
                {
                    var model = new Model(modelName);
                    Cheats.SpawnVehicle((CarID)model.ID);
                }
                else
                {
                    Console.Print("@#ff0000No such model exists in the loaded IDE files.");
                }
            });

            spawnV.HelpText = "Spawns the selected vehicle model";
            Console.Register(spawnV);

            var spawnP = new ConsoleCommand("spawn_ped", delegate(string[] args)
            {
                var modelName = args[0];

                if (Model.IsKnown(modelName))
                {
                    var model = new Model(modelName);
                    Cheats.SpawnPed((PedID)model.ID);
                }
                else
                {
                    if (modelName.StartsWith("#"))
                    {
                        modelName = modelName.Replace("#", "");

                        if (modelName.Length > 7)
                        {
                            Console.Print("@#ff0000A special model ID can be 7 characters at maximum.");
                        }
                        else
                        {
                            Internal.Function.Call(0x023c, 7, modelName);
                            GTAUtils.Wait(250);

                            if (!Internal.Function.Call(0x023d, 7))
                            {
                                Console.Print("@#ff0000No such special model exists.");
                            }

                            Cheats.SpawnPed(PedID.special07);

                            Internal.Function.Call(0x023e, 7);
                        }
                    }
                    else
                    {
                        Console.Print("@#ff0000No such model exists in the loaded IDE files.");
                    }
                }
            });

            spawnP.HelpText = "Spawns a selected pedestrian model";
            Console.Register(spawnP);

#if GTA_SA
            var pModel = new ConsoleCommand("player_model", "null");

            pModel.ValueChanged += new EventHandler(delegate(object sender, EventArgs e)
            {
                var modelName = ((ConsoleCommand)sender).Value;

                if (Model.IsKnown(modelName))
                {
                    var model = new Model(modelName);
                    this.Player.Model = (PedID)model.ID;
                }
                else
                {
                    if (modelName.StartsWith("#"))
                    {
                        modelName = modelName.Replace("#", "");

                        if (modelName.Length > 7)
                        {
                            Console.Print("@#ff0000A special model ID can be 7 characters at maximum.");
                        }
                        else
                        {
                            Internal.Function.Call(0x023c, 7, modelName);
                            GTAUtils.Wait(250);

                            if (!Internal.Function.Call(0x023d, 7))
                            {
                                Console.Print("@#ff0000No such special model exists.");
                            }

                            this.Player.Model = PedID.special07;

                            Internal.Function.Call(0x023e, 7);
                        }
                    }
                    else
                    {
                        Console.Print("@#ff0000No such model exists in the loaded IDE files.");
                    }
                }
            });

            pModel.HelpText = "Sets the player's model (09C7)";

            Console.Register(pModel);

            var listScripts = new ConsoleCommand("script_list_threads", args =>
            {
                int count = 0;
                var pointer = Memory.ReadInt32(0xA8B42C);

                while (pointer != 0)
                {
                    var name = Memory.ReadFixedString(pointer + 8, 8);
                    int instruction = Memory.ReadInt32(pointer + 20);
                    bool isMission = (Memory.ReadByte(pointer + 198) != 0);
                    bool isStreamed = (Memory.ReadByte(pointer + 199) != 0);
                    int wakeUpIn = (Memory.ReadInt32(pointer + 204) - GTAUtils.GetGameTimer());

                    if (!isMission && !isStreamed)
                    {
                        instruction -= 0xA49960;
                    }

                    var data = string.Format("{0} (at 0x{1}) (wake up in {2} ms)", name, instruction.ToString("X"), wakeUpIn);

                    if (isMission)
                    {
                        data += " (mission)";
                    }

                    if (isStreamed)
                    {
                        data += " (streamed)";
                    }

                    Console.Print(data);

                    pointer = Memory.ReadInt32(pointer);
                    count++;
                }

                Console.Print("Total: " + count + " running scripts");
            });

            listScripts.HelpText = "Shows all currently running SCM threads";

            Console.Register(listScripts);

            Dictionary<int, string> statNames = new Dictionary<int,string>();

            statNames[21] = "fat";
            statNames[22] = "stamina";
            statNames[23] = "muscle";
            statNames[68] = "respect";

            statNames[137] = "times_cheated";
            statNames[160] = "driving_skill";
            statNames[181] = "cities_unlocked";
            statNames[223] = "flying_skill";
            statNames[225] = "lung_capacity";
            statNames[229] = "bike_skill";
            statNames[230] = "bicycle_skill";

            for (int si = 0; si < 81; si++)
            {
                StatConsoleCommand command = new StatConsoleCommand(si, true, (statNames.ContainsKey(si)) ? statNames[si] : si.ToString());
                if (!statNames.ContainsKey(si))
                {
                    command.ShowInAutoComplete = false;
                }

                Console.Register(command);
            }

            for (int si = 120; si < 337; si++)
            {
                StatConsoleCommand command = new StatConsoleCommand(si, false, (statNames.ContainsKey(si)) ? statNames[si] : si.ToString());
                if (!statNames.ContainsKey(si))
                {
                    command.ShowInAutoComplete = false;
                }

                Console.Register(command);
            }
#endif

            WantedConsoleCommand wCommand = new WantedConsoleCommand(this.Player, false);
            wCommand.HelpText = "The player's current wanted level";
            Console.Register(wCommand);

            WantedConsoleCommand wCommand2 = new WantedConsoleCommand(this.Player, true);
            wCommand2.HelpText = "The player's maximum wanted level";
            Console.Register(wCommand2);

            var fadeScreen = new ConsoleCommand("fade_in_out", args =>
            {
                Game.Fade(false);
                Game.Fade(true);
            });
            fadeScreen.HelpText = "Fades the screen in and out";

            Console.Register(fadeScreen);

            var missionText = new ConsoleCommand("show_mission_text", args =>
            {
                Game.DisplayMission(args[0]);
            });
            missionText.HelpText = "Displays the argument as mission text";

            Console.Register(missionText);
        }
    }

    internal class WantedConsoleCommand : ConsoleCommand
    {
        private Player _player;
        private bool _isMax;

        public WantedConsoleCommand(Player player, bool isMax)
            : base("v_wantedlevel", "")
        {
            this._player = player;
            this._isMax = isMax;

            if (this._isMax)
            {
                this.Name = "v_maxwantedlevel";
            }
        }

        public override string Value
        {
            get
            {
                if (!this._isMax)
                {
                    return this._player.WantedLevel.ToString();
                }
                else
                {
                    return this._player.MaximumWantedLevel.ToString();
                }
            }
            set
            {
                if (value == "")
                {
                    return;
                }

                if (!this._isMax)
                {
                    this._player.WantedLevel = int.Parse(value);
                }
                else
                {
                    this._player.MaximumWantedLevel = int.Parse(value);
                }
            }
        }
    }

    internal class StatConsoleCommand : ConsoleCommand
    {
        private int _statID;
        private bool _isFloat;

        public StatConsoleCommand(int statID, bool isFloat)
            : base("stat_" + statID, "")
        {
            this._statID = statID;
            this._isFloat = isFloat;
        }

        public StatConsoleCommand(int statID, bool isFloat, string friendlyName)
            : base("stat_" + friendlyName, "")
        {
            this._statID = statID;
            this._isFloat = isFloat;
        }

        public override string Value
        {
            get
            {
                if (this._isFloat)
                {
                    return Game.GetStatFloat(this._statID).ToString();
                }
                else
                {
                    return Game.GetStatInt(this._statID).ToString();
                }
            }
            set
            {
                if (value == "")
                {
                    return;
                }

                base.Value = value;

                if (this._isFloat)
                {
                    Game.SetStatFloat(this._statID, float.Parse(value));
                }
                else
                {
                    Game.SetStatInt(this._statID, int.Parse(value));
                }
            }
        }
    }
}
