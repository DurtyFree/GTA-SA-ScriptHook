using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.IO;
using System.Text;

namespace GTA
{
    public enum ConsoleCommandType
    {
        Variable,
        Command
    }

    public class ConsoleCommand
    {
        private string _value;

        public ConsoleCommand(string name, Action<string[]> handler)
        {
            this.Name = name;
            this.Type = ConsoleCommandType.Command;
            this.Handler = handler;
            this.HelpText = "";

            this.ShowInAutoComplete = true;
        }

        public ConsoleCommand(string name, string defaultValue)
        {
            this.Name = name;
            this.Type = ConsoleCommandType.Variable;
            this.ValidateValue = value => true;
            this.ShowInAutoComplete = true;
            this.HelpText = "";

            if (defaultValue != null)
            {
                this.Value = defaultValue;
            }
        }

        public ConsoleCommand(string name, string defaultValue, Func<string, bool> validator)
        {
            this.Name = name;
            this.Type = ConsoleCommandType.Variable;
            this.ValidateValue = validator;
            this.ShowInAutoComplete = true;
            this.HelpText = "";

            if (defaultValue != null)
            {
                this.Value = defaultValue;
            }
        }

        public string Name { get; set; }
        public ConsoleCommandType Type { get; set; }
        public Action<string[]> Handler { get; set; }
        public Func<string, bool> ValidateValue { get; set; }
        public bool ShowInAutoComplete { get; set; }
        public string HelpText { get; set; }

        public virtual string Value
        {
            get
            {
                return this._value;
            }
            set
            {
                this._value = value;

                if (ValueChanged != null)
                {
                    ValueChanged(this, EventArgs.Empty);
                }
            }
        }

        public event EventHandler ValueChanged;
    }

    public class Console : Script
    {
        public static bool Active { get; set; }
        public static bool LargeConsole { get; set; }
        public static bool Invalidated { get; set; }

        private static Dictionary<string, ConsoleCommand> Commands = new Dictionary<string, ConsoleCommand>();

        private int _screenX;
        private int _screenY;

        private static int _screenSize;
        private static int _screenTop = 0;

        private string _inputBuffer;
        private string _typedInputBuffer;
        private List<string> _commandHistory;
        private static List<string> _screenBuffer;

        private IntPtr rwTexture;
        private Font font;

        private bool _setAA = true;

        [System.Runtime.InteropServices.DllImport("user32.dll", SetLastError = true)]
        public static extern int ToAscii(
            uint uVirtKey, // virtual-key code
            uint uScanCode, // scan code
            byte[] lpKeyState, // key-state array
            StringBuilder lpChar, // buffer for translated key
            uint flags // active-menu flag
        );

        static Console()
        {
            _screenBuffer = new List<string>();
        }

        public Console()
        {
            Log.EventWritten += new Action<LogLevel, string>(this.Log_EventWritten);
            ScriptProcessor.Instance.RawTick += new Action<uint>(this.Instance_RawTick);

            ConsoleCommand dbgAppDomain = new ConsoleCommand("dbg_appdomain", args =>
            {
                Print(AppDomain.CurrentDomain.FriendlyName);
            });

            dbgAppDomain.HelpText = "[DEBUG] shows the current AppDomain";
            Register(dbgAppDomain);

            ConsoleCommand setAA = new ConsoleCommand("v_console_smooth", "1", (value) =>
            {
                if (value != "0" && value != "1")
                {
                    return false;
                }

                return true;
            });

            setAA.ValueChanged += new EventHandler(this.setAA_ValueChanged);
            setAA.HelpText = "A flag changing some value nobody knows what it does";

            Register(setAA);

            ConsoleCommand cmdList = new ConsoleCommand("help", args =>
            {
                string filter = "";

                if (args.Length > 0)
                {
                    filter = args[0];
                }

                Print("All registered commands:");

                var commands = from command in Commands
                               orderby command.Key ascending
                               where command.Key.StartsWith(filter)
                               select command.Value;

                foreach (var command in commands)
                {
                    if (filter == "" && !command.ShowInAutoComplete)
                    {
                        continue;
                    }

                    var msg = command.Name;

                    if (command.HelpText != "")
                    {
                        msg += " - " + command.HelpText;
                    }

                    Print(msg);
                }
            });

            cmdList.HelpText = "This list :)";
            Register(cmdList);
        }

        void setAA_ValueChanged(object sender, EventArgs e)
        {
            this._setAA = (((ConsoleCommand)sender).Value == "1");
        }

        public static void Register(ConsoleCommand command)
        {
            if (!Commands.ContainsKey(command.Name))
            {
                Commands.Add(command.Name, command);
            }
        }

        void Instance_RawTick(uint tDelta)
        {
            if (Active)
            {
                this.EnsureFrameBuffer();
                this.DrawConsole();
                this.LogBuffer("draw");
            }
        }

        void Log_EventWritten(LogLevel level, string lmessage)
        {
            var message = "";

            switch (level)
            {
                case LogLevel.Error:
                    message += "@#ff0000";
                    break;
                case LogLevel.Warning:
                    message += "@#ffff00";
                    break;
            }

            message += lmessage;

            Print(message);
        }

        public override void Run()
        {
            this.Wait(1000);

            this._commandHistory = new List<string>();
            this.lastKeys = new byte[256];
            LargeConsole = true;

            this.CreateFrameBuffer();

            this.font = new Font("Courier New", 10, FontStyle.Regular);

            while (true)
            {
                this.Wait(0);

#if GTA_SA
                this._screenX = Memory.ReadInt32(0xC17044);
                this._screenY = Memory.ReadInt32(0xC17048);
#endif
#if GTA_III
                //_screenX = (int)(1f / Memory.ReadSingle(0x5F7148));
                //_screenY = (int)(1f / Memory.ReadSingle(0x5F7158));
                _screenX = Memory.ReadInt32(0x8F436C);
                _screenY = Memory.ReadInt32(0x8F4370);

                Game.DisplayText(_screenY.ToString(), 20);
#endif

                this.ProcessKeys();
                Array.Copy(this.keys, this.lastKeys, 256);

                if (Active)
                {
#if GTA_SA
                    Game.GamePad.Clear();
                    Game.GamePad2.Clear();
#endif
                    this.LogBuffer("begin");
                    this.EnsureFrameBuffer();
                    this.LogBuffer("ensure1");
                    this.RenderConsole();
                    this.LogBuffer("render");
                    this.EnsureFrameBuffer(); // again!
                    this.LogBuffer("ensure2");
                }
            }
        }

        private void LogBuffer(string at)
        {
            /*
            int baseOffset = 0xA94B68;
            baseOffset += (91 * 4);
            baseOffset -= 4;

            var pointer = Memory.ReadInt32(baseOffset);

            Log.Debug(at + " - buffer: 0x" + pointer.ToString("X8"));
            */
        }

        private void EnsureFrameBuffer()
        {
#if GTA_SA
            int baseOffset = 0xA94B68;
            baseOffset += (91 * 4);
#endif
#if GTA_III
            int baseOffset = 0x72B090;
            baseOffset += (1 * 4);
#endif
            baseOffset -= 4;

            var pointer = Memory.ReadInt32(baseOffset);

            if (pointer < 0xa00000)
            {
                this.CreateFrameBuffer();
            }
        }

        private void CreateFrameBuffer()
        {
            Log.Debug("Creating frame buffer");
#if !GTA_IV
            this.rwTexture = RenderWare.CreateTexture32(2048, 2048);

            // write texture to script position 91
#if GTA_SA
            int baseOffset = 0xA94B68;
            baseOffset += (91 * 4);
#endif
#if GTA_III
            int baseOffset = 0x72B090;
            baseOffset += (1 * 4);
#endif
            baseOffset -= 4;

            Memory.Write(baseOffset, this.rwTexture.ToInt32());

            Invalidated = true;
#endif
        }

        byte[] keys;
        byte[] lastKeys;

        private bool KeyPressed(int keycode)
        {
            var retval = (this.keys[keycode] != 0 && this.lastKeys[keycode] == 0);

            return retval;
        }

        private bool IsShiftPressed()
        {
            return (this.keys[(int)System.Windows.Forms.Keys.Shift] != 0);
        }

        private void ProcessKeys()
        {
            this.keys = ScriptProcessor.Instance.KeyBuffer;

            this.ProcessKeyBindings();

            if (this.KeyPressed((int)System.Windows.Forms.Keys.Oem3))
            {
                Active = !Active;
                this.Player.CanControlCharacter = !Active;
                BaseScript.DisableKeyBindings = Active;
#if GTA_SA
                Game.RawHUDEnabled(!Active);
                Game.ShowRadar(!Active);
#endif
                Invalidated = true;

                return;
            }

            if (Active)
            {
                if (this.KeyPressed((int)System.Windows.Forms.Keys.Back))
                {
                    if (this._inputBuffer.Length > 0)
                    {
                        this._inputBuffer = this._inputBuffer.Substring(0, this._inputBuffer.Length - 1);
                        this._typedInputBuffer = this._inputBuffer;

                        this.UpdateSuggestions();
                        Invalidated = true;
                    }
                }

                if (this.KeyPressed((int)System.Windows.Forms.Keys.Return))
                {
                    this.SendCommand();

                    this.UpdateSuggestions();
                    return;
                }

                if (this.KeyPressed((int)System.Windows.Forms.Keys.Up))
                {
                    if (this._suggestions.Count > 0)
                    {
                        this._currentSuggestion--;

                        if (this._currentSuggestion < 0)
                        {
                            this._currentSuggestion = this._suggestions.Count - 1;
                        }

                        this._inputBuffer = this._suggestions[this._currentSuggestion].Name + " ";

                        Invalidated = true;
                    }

                    return;
                }

                if (this.KeyPressed((int)System.Windows.Forms.Keys.Down))
                {
                    if (this._suggestions.Count > 0)
                    {
                        this._currentSuggestion++;

                        if (this._currentSuggestion > (this._suggestions.Count - 1))
                        {
                            this._currentSuggestion = 0;
                        }

                        this._inputBuffer = this._suggestions[this._currentSuggestion].Name + " ";

                        Invalidated = true;
                    }

                    return;
                }

                if (this.KeyPressed((int)System.Windows.Forms.Keys.PageUp))
                {
                    _screenTop -= 25;

                    if (_screenTop < 0)
                    {
                        _screenTop = 0;
                    }

                    Invalidated = true;

                    return;
                }

                if (this.KeyPressed((int)System.Windows.Forms.Keys.PageDown))
                {
                    _screenTop += 25;

                    if (_screenTop > (_screenBuffer.Count - _screenSize))
                    {
                        _screenTop = (_screenBuffer.Count - _screenSize);
                    }

                    Invalidated = true;

                    return;
                }

                for (int i = 0x20; i <= 0xFF; i++)
                {
                    if (this.KeyPressed(i))
                    {
                        StringBuilder sb = new StringBuilder(2);
                        int retval = ToAscii((uint)i, 0, this.keys, sb, 0);

                        if (retval == 1)
                        {
                            this._inputBuffer += sb.ToString()[0];
                            this._typedInputBuffer = this._inputBuffer;

                            this.UpdateSuggestions();
                            Invalidated = true;
                        }
                        else if (retval == 2)
                        {
                            this._inputBuffer += sb.ToString();
                            this._typedInputBuffer = this._inputBuffer;

                            this.UpdateSuggestions();
                            Invalidated = true;
                        }
                    }
                }
            }
        }

        private void SendCommand()
        {
            Print("@#FFFF00> " + this._inputBuffer);

            Process(this._inputBuffer);

            this._inputBuffer = "";
            this._typedInputBuffer = "";
            this.UpdateSuggestions();

            Invalidated = true;
        }

        public static void Process(string command)
        {
            try
            {
                if (!command.EndsWith(" "))
                {
                    command += ' ';
                }

                var data = command.Split(new char[] { ' ' }, 2);
                var commandName = data[0].ToLower();

                if (!Commands.ContainsKey(commandName))
                {
                    Print("@#ff0000unknown command " + commandName);
                    return;
                }

                var cmd = Commands[commandName];

                switch (cmd.Type)
                {
                    case ConsoleCommandType.Command:
                        string[] arguments = new string[0];

                        if (data.Length > 1)
                        {
                            arguments = ParseArgs(data[1].Trim());
                        }

                        if (arguments.Length == 1 && arguments[0].Trim() == "")
                        {
                            arguments = new string[0];
                        }

                        Defer.DeferScript(delegate()
                        {
                            cmd.Handler(arguments);
                        });
                        break;
                    case ConsoleCommandType.Variable:
                        if (data[1].Trim() == "")
                        {
                            Print(cmd.Name + ": " + cmd.Value);
                        }
                        else
                        {
                            var varguments = ParseArgs(data[1].Trim());
                            var newValue = varguments[0];

                            if (cmd.ValidateValue != null)
                            {
                                if (!cmd.ValidateValue(newValue))
                                {
                                    Console.Print("@#ff0000invalid argument passed");
                                    break;
                                }
                            }

                            Defer.DeferScript(delegate()
                            {
                                cmd.Value = newValue;
                            });
                        }
                        break;
                }
            }
            catch (Exception e)
            {
                Print("@#FF0000" + e.ToString());
            }
        }

        private static string[] ParseArgs(string data)
        {
            List<string> output = new List<string>();
            bool inQuote = false;
            bool inEscape = false;
            char lastQuote = '"';
            int idx = 0;
            string current = "";

            data = data.Trim();

            for (idx = 0; idx < data.Length; idx++)
            {
                char curChar = data[idx];

                if (curChar == ' ' && !inQuote)
                {
                    output.Add(current);
                    current = "";
                    continue;
                }

                if (curChar == '\'' || curChar == '"')
                {
                    if (!inEscape)
                    {
                        if (!inQuote || (curChar == lastQuote))
                        {
                            inQuote = !inQuote;
                            lastQuote = curChar;
                            continue;
                        }
                    }
                }

                if (curChar == '\\' && !inEscape)
                {
                    inEscape = true;
                    continue;
                }

                current += curChar;
                inEscape = false;
            }

            output.Add(current);
            return output.ToArray();
        }

        public static void Print(string text)
        {
            var prefix = "";

            if (text.StartsWith("@#"))
            {
                prefix = text.Substring(0, 8);
                text = text.Substring(8);
            }

            var lines = text.Split('\n');

            foreach (var line in lines)
            {
                _screenBuffer.Add(prefix + line);
            }

            ResetTop();

            // todo: make this a convar
            if (_screenBuffer.Count > 500)
            {
                _screenBuffer = _screenBuffer.Skip(_screenBuffer.Count - 300).ToList();
            }

            Invalidated = true;
        }

        private static void ResetTop()
        {
            _screenTop = (_screenBuffer.Count - _screenSize);

            Invalidated = true;
        }

        private void DrawConsole()
        {
#if !GTA_IV
            float x = 1024f;
            float y = 1024f;

            float w = 2048f;
            float h = 2048f;

#if GTA_SA
            x = (x / this._screenX) * (Memory.ReadSingle(0x85951c));
            y = (y / this._screenY) * 448f;

            w = (w / this._screenX) * (Memory.ReadSingle(0x85951c));
            h = (h / this._screenY) * 448f;
#endif
#if GTA_III
            // GTA3 uses non-translated screen-space coordinates for textures, going from the top left
            x = 0f;
            y = 0f;

            // since 2048 will roll over to be negative in GTA3's 16-bit floating point system
            w = 2047.9375f;
            h = 2047.9375f;
#endif

            // GTA3 doesn't do anything with it, but if false, the HUD is drawn last
            // which is useful, since the HUD disabling commands don't exist on III. :)
#if !GTA_III
            if (this._setAA)
            {
                Internal.Function.Call(0x03E3, true);
            }
#endif

#if GTA_SA
            Internal.Function.Call(0x038D, 91, x, y, w, h, 255, 255, 255, 255);
#endif
#if GTA_III
            Internal.Function.Call(0x038D, 1, x, y, w, h, 255, 255, 255, 255);
#endif
#endif
        }

        private float p(float value)
        {
            return ((short)(value * 16f)) / 16f;
        }

        private int _inputBoxBottom = 0;
        private int _inputBoxRight = 0;

        private void RenderConsole()
        {
#if !GTA_IV
            if (!Invalidated)
            {
                return;
            }

            var graphics = TXD.LockBitmap(this.rwTexture);
            graphics.Clear(Color.Transparent);
            graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;

            this.RenderInputBox(graphics);

            if (LargeConsole)
            {
                this.RenderOutputBox(graphics);
            }

            this.RenderAutoComplete(graphics);

            TXD.UnlockBitmap(this.rwTexture);

            Invalidated = false;
#endif
        }

        private void RenderInputBox(Graphics g)
        {
            var text = "GTAScript:" + ScriptProcessor.HookVersion + "> " + this._inputBuffer;
            var tSize = g.MeasureString(text, this.font).ToSize();

            int x = 15;
            int y = 15;

            int w = this._screenX - 30;
            int h = tSize.Height + 3 + 3;

            g.FillRectangle(new SolidBrush(Color.FromArgb(0x44, 0x44, 0x44)), x, y, w + 2, h + 2);
            g.DrawRectangle(new Pen(Color.FromArgb(0x22, 0x22, 0x22), 2f), x, y, w + 2, h + 2);

            g.DrawString(text, this.font, new SolidBrush(Color.Yellow), x + 7, y + 3);

            this._inputBoxRight = x + 7 + tSize.Width;
            this._inputBoxBottom = y + h + 2;
        }

        private List<ConsoleCommand> _suggestions = new List<ConsoleCommand>();
        private string _suggestionSource = "";
        private int _currentSuggestion = 0;

        private void UpdateSuggestions()
        {
            if (this._typedInputBuffer.Contains(' ') || this._typedInputBuffer == "")
            {
                this._suggestions.Clear();
                this._currentSuggestion = 0;
                return;
            }

            if (this._typedInputBuffer != this._suggestionSource)
            {
                var suggestions = from command in Commands
                                  where command.Key.ToLower().StartsWith(this._typedInputBuffer.ToLower()) && command.Key.ToLower() != this._typedInputBuffer.ToLower() && command.Value.ShowInAutoComplete
                                  select command.Value;

                this._suggestions = suggestions.ToList();
                this._currentSuggestion = -1;
            }
        }

        private string RenderAutoCompleteLine(ConsoleCommand line)
        {
            var name = line.Name;

            if (line.Type == ConsoleCommandType.Variable)
            {
                name += " " + line.Value;
            }

            return name;
        }

        private void RenderAutoComplete(Graphics g)
        {
            if (this._suggestions.Count > 0)
            {
                var longestSuggestion = (from command in this._suggestions
                                         orderby this.RenderAutoCompleteLine(command).Length descending
                                         select this.RenderAutoCompleteLine(command)).First();

                var size = g.MeasureString(longestSuggestion, this.font).ToSize();

                var x = this._inputBoxRight;
                var y = this._inputBoxBottom - 2;

                var lines = Math.Min(this._suggestions.Count, 20);
                var h = (lines * size.Height) + 4 + 6;
                var w = size.Width + 4 + 6;

                g.FillRectangle(new SolidBrush(Color.FromArgb(0x44, 0x44, 0x44)), x, y, w, h);
                g.DrawRectangle(new Pen(Color.FromArgb(0x22, 0x22, 0x22), 2f), x, y, w, h);

                foreach (var line in this._suggestions)
                {
                    g.DrawString(this.RenderAutoCompleteLine(line), this.font, new SolidBrush(Color.White), x + 5, y + 5);

                    y += size.Height;
                }
            }
        }

        private void RenderOutputBox(Graphics g)
        {
            int x = 15;
            int y = this._inputBoxBottom + 5;

            int w = this._screenX - 30;
            int h = this._screenY - y - 15 - 2;

            var size = g.MeasureString("a", this.font).ToSize();

            g.FillRectangle(new SolidBrush(Color.FromArgb(0xcc, 0x44, 0x44, 0x44)), x, y, w + 2, h + 2);
            g.DrawRectangle(new Pen(Color.FromArgb(0xcc, 0x22, 0x22, 0x22), 2f), x, y, w + 2, h + 2);

            bool reset = false;

            if (_screenSize == 0)
            {
                reset = true;
            }

            _screenSize = (h - 4) / size.Height;

            if (reset)
            {
                ResetTop();
            }

            var list = _screenBuffer.Skip(_screenTop);
            int i = 0;

            y += 5;

            foreach (var line in list)
            {
                var text = line;
                var color = Color.White;

                if (text.StartsWith("@#"))
                {
                    var colorN = text.Substring(1, 7);
                    color = ColorTranslator.FromHtml(colorN);

                    text = text.Substring(8);
                }

                g.DrawString(text, this.font, new SolidBrush(color), x + 5, y);

                y += size.Height;
                i++;

                if (i >= _screenSize)
                {
                    break;
                }
            }
        }
    }
}
