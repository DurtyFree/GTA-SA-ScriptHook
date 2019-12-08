using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public enum TextDrawAlign
    {
        Left,
        Center,
        Right
    }

    public class TextDrawFont
    {
        public bool BorderEnabled { get; set; }
        public int Font { get; set; }
        public float Size { get; set; }
        public GTAColor Color { get; set; }
        public bool Centered { get; set; }
        public TextDrawAlign Align { get; set; }
        public float LineWidth { get; set; }

        public TextDrawFont()
        {
            this.LineWidth = 640f;
            this.BorderEnabled = true;
            this.Font = 1;
            this.Size = 100;
            this.Centered = false;
            this.Color = new GTAColor(255, 255, 255, 255);
        }

        public void ApplyToGame()
        {
            // 26-10-2009: enable 'normal' width
            Native.CallOpcode(0x0348, true);

            if (this.Centered)
            {
                this.Align = TextDrawAlign.Center;
            }

            Native.CallOpcode(0x0342, false);
            Native.CallOpcode(0x03e4, false);

            // disable shadow, we don't want one!
            Native.CallOpcode(0x060d, false, 0, 0, 0, 0);

            // but we do want a border :)
            // 26-10-2009: fixed bug with Color.A

            if (this.Color.A == 0)
            {
                Native.CallOpcode(0x081c, this.BorderEnabled, 0, 0, 0, 255);
            }
            else
            {
                Native.CallOpcode(0x081c, this.BorderEnabled, 0, 0, 0, this.Color.A);
            }

            if (this.Align == TextDrawAlign.Center)
            {
                Native.CallOpcode(0x0342, true);
            }
            else if (this.Align == TextDrawAlign.Right)
            {
                Native.CallOpcode(0x03e4, true);
            }

            /*if (Align != TextDrawAlign.Left)
            {*/
            //Native.CallOpcode(0x0343, 640.0f);
            Native.CallOpcode(0x0343, this.LineWidth);
            /*}
            else
            {
                Native.CallOpcode(0x0343, 0.0f);
            }*/

            if (this.Size > 0)
            {
                // let's take 100 == 1.0 height

                float height = (int)(this.Size / 100);

                // could have fixed the bug, but it causes incompatiblity
                if (this.Size < 30f)
                {
                    height = this.Size;
                }

                float width = (height * 0.224f);
                Native.CallOpcode(0x033f, width, height);

                //Initialize.Log(string.Format("Font size: {0} {1}", width, height));
            }

            if (this.Font != -1)
            {
                Native.CallOpcode(0x0349, this.Font);
            }

            if (this.Color.A != 0)
            {
                Native.CallOpcode(0x0340, this.Color.R, this.Color.G, this.Color.B, this.Color.A);
            }
        }
    }

    public class TextDrawText
    {
        public string Text { get; set; }
        public Vector3 Position { get; set; }
        public TextDrawFont Font { get; set; }
    }

    public class TextDraw : TickScript
    {
        public static List<TextDrawText> Texts = new List<TextDrawText>();
        public static List<TextDrawText> TempTexts = new List<TextDrawText>();
        public static bool Enabled { get; set; }
        public static event Action HijackTick;

        public TextDraw()
        {
            Enabled = true;
            this.Interval = 0;
            Tick += new EventHandler(this.TextDraw_OnTick);

            var tdEnabled = new TextDrawEnabledConsoleCommand();
            Console.Register(tdEnabled);
        }

        public static void Draw(TextDrawText text)
        {
            TempTexts.Add(text);
        }

        void TextDraw_OnTick(object sender, EventArgs e)
        {
            this.Clear();

            if (HijackTick != null)
            {
                HijackTick();
            }

            if (!Enabled)
            {
                return;
            }

            curDrawID = 1;
            foreach (var Text in Texts)
            {
                Text.Font.ApplyToGame();
                DrawCurrent(Text.Text, Text.Position.pX, Text.Position.pY);
            }

            foreach (var Text in TempTexts)
            {
                Text.Font.ApplyToGame();
                DrawCurrent(Text.Text, Text.Position.pX, Text.Position.pY);
            }

            TempTexts.Clear();

            //Native.CallOpcode(0x033e, 10f, 10f, "_TMEMO");
        }

        static int curDrawID = 1;

        public static void DrawCurrent(string text, float x, float y)
        {
            string name = "TDRW" + curDrawID.ToString();

            //GTA.Game.SetCustomMultiText(i, Text.Text);
            GTA.Game.CustomGXTs[name] = text;
            Native.CallOpcode(0x033e, x, y, name);

            curDrawID++;

            if (curDrawID >= 200)
            {
                curDrawID = 1;
            }
        }

        public void Clear()
        {
            Native.CallOpcode(0x03f0, 0);

            //if (Enabled)
            //{
            Native.CallOpcode(0x03f0, 1);
            //}
        }
    }

    internal class TextDrawEnabledConsoleCommand : ConsoleCommand
    {
        public TextDrawEnabledConsoleCommand()
            : base("v_textdraw", "")
        {
            this.ValidateValue = value => (value == "1" || value == "0");
        }

        public override string Value
        {
            get
            {
                return (TextDraw.Enabled) ? "1" : "0";
            }
            set
            {
                if (value == "")
                {
                    return;
                }

                if (value == "1")
                {
                    TextDraw.Enabled = true;
                }
                else
                {
                    TextDraw.Enabled = false;
                }
            }
        }
    }

}
