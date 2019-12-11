using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;

namespace GenerateBuildID
{
    class Program
    {
        static void Main(string[] args)
        {
            var path = string.Join(" ", args);

            if (File.Exists(path))
            {
                var file = File.OpenText(path);
                var data = file.ReadToEnd();
                file.Close();

                string dateID = DateTime.Now.ToString("yyyy.MM.dd.HHmm");

                // generate new strings
                string genVersion = "// ##GENVERSION\r\n";
                genVersion += "[assembly:AssemblyVersionAttribute(\"" + dateID + "\")];\r\n";
                genVersion += "// #/GENVERSION";

                //string buildDate = = "// ##GENBDATE\r\n";

                data = Regex.Replace(data, "// ##GENVERSION\r\n(.*?)\r\n// #/GENVERSION", genVersion);

                var writer = new StreamWriter(path, false);
                writer.Write(data);
                writer.Flush();
                writer.Close();
            }
        }
    }
}
