using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace GTA
{
    public struct Model
    {
        #region item name code
        internal static bool IdeLoaded = false;
        internal static Dictionary<string, int> Models = new Dictionary<string, int>();

        internal static void LoadIde()
        {
            if (IdeLoaded)
            {
                return;
            }

            IdeLoaded = true; // though we may not succeed, this is for the better - no need trying again if we fail

            var gtadat = "";
#if GTA_SA
            var reader = File.OpenText(Game.InstallFolder + @"\data\gta.dat");
#endif
#if GTA_III
            var reader = File.OpenText(Game.InstallFolder + @"\data\gta3.dat");
#endif
            gtadat += reader.ReadToEnd();
            reader.Close();

            // also load default.dat
            reader = File.OpenText(Game.InstallFolder + @"\data\default.dat");
            gtadat += reader.ReadToEnd();
            reader.Close();

            // read any definition files
            var matches = Regex.Matches(gtadat, "^IDE (.*?)$", RegexOptions.Multiline);

            // pre-compile the line regex
            var objsLine = new Regex("^([0-9]+?),?\\s+(.*?),?\\s+(.*?),\\s+(.*?),\\s+(.*?)$", RegexOptions.Multiline);

            foreach (Match match in matches)
            {
                string filename = match.Groups[1].Value.Trim();

                // no exception checking, because if the file did not exist
                // the game wouldn't even be able to load
                StreamReader ide = File.OpenText(Game.InstallFolder + @"\" + filename);
                string data = ide.ReadToEnd();
                ide.Close();

                // and match again
                var imatches = objsLine.Matches(data);

                foreach (Match line in imatches)
                {
                    int value = -1;

                    if (int.TryParse(line.Groups[1].Value.Trim(), out value))
                    {
                        Models[line.Groups[2].Value.Trim().ToLower()] = value;
                    }
                    else
                    {
                        Log.Info("Could not read model line: " + line.Groups[0].Value);
                    }
                }
            }
        }

        public static bool IsKnown(string name)
        {
#if !GTA_IV
            LoadIde();

            if (!Models.ContainsKey(name.ToLower()))
            {
                int model = -1;

                if (int.TryParse(name, out model))
                {
                    return true;
                }
            }
            else
            {
                return true;
            }

            return false;
#else
            return true; // no way to know, right?
#endif
        }
        #endregion

        public static uint Hash(string str)
        {
            uint value = 0, temp;
            var index = 0;
            var quoted = false;

            if (str[index] == '"')
            {
                quoted = true;
                index++;
            }

            str = str.ToLower();

            for (; index < str.Length; index++)
            {
                var v = str[index];

                if (quoted && (v == '"'))
                {
                    break;
                }

                if (v == '\\')
                {
                    v = '/';
                }

                temp = v;
                temp += value;
                value = temp << 10;
                temp += value;
                value = temp >> 6;
                value ^= temp;
            }

            temp = value << 3;
            temp = value + temp;
            var temp2 = temp >> 11;
            temp = temp2 ^ temp;
            temp2 = temp << 15;

            value = temp2 + temp;

            if (value < 2)
            {
                value += 2;
            }

            return value;
        }

        public Model(string name)
        {
#if !GTA_IV
            LoadIde();

            if (!Models.ContainsKey(name.ToLower()))
            {
                int model = -1;

                if (int.TryParse(name, out model))
                {
                    Id = model;
                }
                else
                {
                    throw new ArgumentException("This model does not exist.", "name");
                }
            }
            else
            {
                Id = Models[name.ToLower()];
            }
#else
            _id = (int)Hash(name);
#endif
        }

        public Model(int id)
        {
            Id = id;
        }

        public void Load()
        {
            Internal.Function.Call(0x0247, Id);
            Internal.Function.Call(0x038B);

            while (!Loaded)
            {
                GTAUtils.Wait(0);
            }
        }

        public void Release()
        {
            Internal.Function.Call(0x0249, Id);
        }

        public static implicit operator Model(int source)
        {
            return new Model(source);
        }

        public static implicit operator Model(string source)
        {
            return new Model(source);
        }

        public static implicit operator Internal.Parameter(Model source)
        {
            return new Internal.Parameter(source.Id);
        }

        public static bool operator ==(Model left, Model right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(Model left, Model right)
        {
            return !left.Equals(right);
        }

        public override int GetHashCode()
        {
            return Id;
        }

        public override bool Equals(object obj)
        {
            return (GetHashCode() == obj.GetHashCode());
        }

        public override string ToString()
        {
            return "#" + Id.ToString();
        }

        public bool Loaded
        {
            get
            {
                try
                {
                    if (Internal.Function.Call(0x0248, Id))
                    {
                        return true;
                    }
                }
                catch (AccessViolationException) { }

                return false;
            }
        }

        public bool Exists
        {
            get
            {
                try
                {
                    Internal.Function.Call(0x0248, Id);
                    return true;
                }
                catch (AccessViolationException)
                {
                    return false;
                }
            }
        }

        public int Id { get; }

        public static void Load(Model model)
        {
            model.Load();
        }

        public static void Release(Model model)
        {
            model.Release();
        }


    }
}
