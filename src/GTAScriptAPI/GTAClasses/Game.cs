﻿using System;
using System.Collections.Generic;

namespace GTA
{
    public class TextDictionary
    {
        private readonly Dictionary<string, string> _internalDict;

        public TextDictionary()
        {
            _internalDict = new Dictionary<string, string>();
        }

        public string this[string key]
        {
            get
            {
                // compatibility requires key to be ToUpper-ed
                key = key.ToUpper();

                return _internalDict[key];
            }
            set
            {
                key = key.ToUpper();

                _internalDict[key] = value;
                TextHook.RemoveCache(key);
            }
        }

        public bool ContainsKey(string key)
        {
            key = key.ToUpper();
            return _internalDict.ContainsKey(key);
        }
    }

    public class Game
    {
        private static int _curId = 0;

        public static string InstallFolder
        {
            get;
            private set;
        }

        public static TextDictionary CustomGxTs
        {
            get;
            set;
        }

#if GTA_SA
        public static Pad GamePad { get; set; }
        public static Pad GamePad2 { get; set; }
#endif

        static Game()
        {
            //CustomGXTs = new Dictionary<string, string>();
            CustomGxTs = new TextDictionary();

            TextHook.RegisterCallback(key =>
            {
                if (CustomGxTs.ContainsKey(key))
                {
                    return CustomGxTs[key];
                }

                return null;
            });

#if GTA_SA
            GamePad = new Pad(new IntPtr(0xB73458));
            GamePad2 = new Pad(new IntPtr(0xB7358C));
#endif

            InstallFolder = System.Windows.Forms.Application.StartupPath;
        }

        public static Time Time
        {
            get
            {
                VarPointer h = new VarPointer(0);
                VarPointer m = new VarPointer(0);

                Internal.Function.Call(0x00bf, h, m);

                int hh = (int)h;
                int mm = (int)m;

                return new Time() { Hours = hh, Minutes = mm };
            }
            set => Internal.Function.Call(0x00c0, value.Hours, value.Minutes);
        }

        public static void PlaySound(int soundId)
        {
            PlaySound(soundId, new Vector3(0, 0, 0));
        }

        public static void PlaySound(int soundId, Vector3 at)
        {
            Internal.Function.Call(0x097A, at, soundId);
        }

#if GTA_SA
        public static void PlayFrontendSound(FrontendSound soundId)
        {
            PlayFrontendSound((int)soundId);
        }

        public static void PlayFrontendSound(int soundId)
        {
            NativeFunctions.PlayFrontendAudio(soundId);
        }
#endif

        #region stats
        public static int GetStatInt(int id)
        {
            return Internal.Function.Call<int>(0x0652, id);
        }

        public static float GetStatFloat(int id)
        {
            return Internal.Function.Call<float>(0x0653, id);
        }

        public static void SetStatInt(int id, int value)
        {
            Internal.Function.Call(0x0629, id, value);
        }

        public static void SetStatFloat(int id, float value)
        {
            Internal.Function.Call(0x062a, id, value);
        }
        #endregion

        #region fading
        public static void Fade(bool fadeIn)
        {
            Fade(fadeIn, true);
        }

        public static void Fade(bool fadeIn, bool wait)
        {
            if (fadeIn)
            {
                FadeIn();
            }
            else
            {
                FadeOut();
            }

            if (wait)
            {
                while (Fading)
                {
                    GTAUtils.Wait(0);
                }
            }
        }

        public static void FadeIn()
        {
#if !GTA_IV
            Internal.Function.Call(0x016a, 500, true);
#else
            Internal.Function.Call("DO_SCREEN_FADE_IN", 500);
#endif
        }

        public static void FadeOut()
        {
#if !GTA_IV
            Internal.Function.Call(0x016a, 500, false);
#else
            Internal.Function.Call("DO_SCREEN_FADE_OUT", 500);
#endif
        }

        public static bool Fading => Internal.Function.Call(0x016b);

        #endregion

        #region HUD
        public static void ShowHud(bool enabled)
        {
            Internal.Function.Call(0x0826, enabled);
        }

        public static void ShowRadar(bool enabled)
        {
            Internal.Function.Call(0x0581, enabled);
        }

        public static void ShowZoneName(bool enabled)
        {
            Internal.Function.Call(0x09ba, enabled);
        }

        public static unsafe void RawHudEnabled(bool enabled)
        {
#if GTA_SA
            *(byte*)0xBA6769 = (enabled) ? (byte)1 : (byte)0;
#endif
        }
        #endregion

        #region text
        public static void DisplayTextBox(string text)
        {
#if !GTA_IV
            Internal.Function.Call(0x03E5, RegisterKey(text));
#else
            Internal.Function.Call("PRINT_HELP_WITH_STRING", "STRING", text);
#endif
        }

        public static void DisplayText(string text, int time)
        {
#if !GTA_IV
            Internal.Function.Call(0x00BC, RegisterKey(text), time, 1);
#else
            Internal.Function.Call("PRINT_STRING_WITH_LITERAL_STRING_NOW", "STRING", text, time, 1);
#endif
        }

        public static void DisplayMission(string text)
        {
#if !GTA_IV
            DisplayStyledText(text, 1000, TextStyle.MissionName);
#else

#endif
        }

        public static void DisplayStyledText(string text, int time, TextStyle style)
        {
#if !GTA_IV
            DisplayStyledText(text, time, (int)style);
#endif
        }

        public static void DisplayStyledText(string text, int time, int type)
        {
#if !GTA_IV
            Internal.Function.Call(0x00ba, RegisterKey(text), time, type);
#endif
        }

        private static string RegisterKey(string value)
        {
            string key = "NET" + _curId.ToString("X4"); // unique identifier based on key
            CustomGxTs[key] = value;

            _curId++;

            // prevent overflow/full memory
            if (_curId >= 0xFFF)
            {
                _curId = 0;
            }

            return key;
        }
        #endregion
    }
}
