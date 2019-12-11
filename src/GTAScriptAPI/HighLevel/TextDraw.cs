using System;
using System.Collections.Generic;

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
        public GtaColor Color { get; set; }
        public bool Centered { get; set; }
        public TextDrawAlign Align { get; set; }
        public float LineWidth { get; set; }

        public TextDrawFont()
        {
            LineWidth = 640f;
            BorderEnabled = true;
            Font = 1;
            Size = 100;
            Centered = false;
            Color = new GtaColor(255, 255, 255, 255);
        }

        public void ApplyToGame()
        {
            // 26-10-2009: enable 'normal' width
            Native.CallOpcode(0x0348, true);

            if (Centered)
            {
                Align = TextDrawAlign.Center;
            }

            Native.CallOpcode(0x0342, false);
            Native.CallOpcode(0x03e4, false);

            // disable shadow, we don't want one!
            Native.CallOpcode(0x060d, false, 0, 0, 0, 0);

            // but we do want a border :)
            // 26-10-2009: fixed bug with Color.A

            if (Color.A == 0)
            {
                Native.CallOpcode(0x081c, BorderEnabled, 0, 0, 0, 255);
            }
            else
            {
                Native.CallOpcode(0x081c, BorderEnabled, 0, 0, 0, Color.A);
            }

            if (Align == TextDrawAlign.Center)
            {
                Native.CallOpcode(0x0342, true);
            }
            else if (Align == TextDrawAlign.Right)
            {
                Native.CallOpcode(0x03e4, true);
            }

            /*if (Align != TextDrawAlign.Left)
            {*/
            //Native.CallOpcode(0x0343, 640.0f);
            Native.CallOpcode(0x0343, LineWidth);
            /*}
            else
            {
                Native.CallOpcode(0x0343, 0.0f);
            }*/

            if (Size > 0)
            {
                // let's take 100 == 1.0 height

                float height = (int)(Size / 100);

                // could have fixed the bug, but it causes incompatiblity
                if (Size < 30f)
                {
                    height = Size;
                }

                float width = (height * 0.224f);
                Native.CallOpcode(0x033f, width, height);

                //Initialize.Log(string.Format("Font size: {0} {1}", width, height));
            }

            if (Font != -1)
            {
                Native.CallOpcode(0x0349, Font);
            }

            if (Color.A != 0)
            {
                Native.CallOpcode(0x0340, Color.R, Color.G, Color.B, Color.A);
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
            Interval = 0;
            Tick += new EventHandler(TextDraw_OnTick);

            var tdEnabled = new TextDrawEnabledConsoleCommand();
            Console.Register(tdEnabled);
        }

        public static void Draw(TextDrawText text)
        {
            TempTexts.Add(text);
        }

        void TextDraw_OnTick(object sender, EventArgs e)
        {
            Clear();

            if (HijackTick != null)
            {
                HijackTick();
            }

            if (!Enabled)
            {
                return;
            }

            _curDrawId = 1;
            foreach (var text in Texts)
            {
                text.Font.ApplyToGame();
                DrawCurrent(text.Text, text.Position.PX, text.Position.PY);
            }

            foreach (var text in TempTexts)
            {
                text.Font.ApplyToGame();
                DrawCurrent(text.Text, text.Position.PX, text.Position.PY);
            }

            TempTexts.Clear();

            //Native.CallOpcode(0x033e, 10f, 10f, "_TMEMO");
        }

        static int _curDrawId = 1;

        public static void DrawCurrent(string text, float x, float y)
        {
            string name = "TDRW" + _curDrawId.ToString();

            //GTA.Game.SetCustomMultiText(i, Text.Text);
            Game.CustomGxTs[name] = text;
            Native.CallOpcode(0x033e, x, y, name);

            _curDrawId++;

            if (_curDrawId >= 200)
            {
                _curDrawId = 1;
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
            ValidateValue = value => (value == "1" || value == "0");
        }

        public override string Value
        {
            get => (TextDraw.Enabled) ? "1" : "0";
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
