using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace GTA
{
    public class Memory
    {
        [DllImport("kernel32.dll")]
        static extern bool ReadProcessMemory
        (
            IntPtr hProcess,
            IntPtr lpBaseAddress,
            byte[] lpBuffer,
            UInt32 nSize,
            ref UInt32 lpNumberOfBytesRead
        );

        [DllImport("kernel32.dll")]
        static extern IntPtr GetCurrentProcess();

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out int lpNumberOfBytesWritten);


        public static byte[] Read(IntPtr address, uint size)
        {
            uint bytes = 0;
            byte[] buffer = new byte[size];

            ReadProcessMemory(GetCurrentProcess(), address, buffer, size, ref bytes);

            return buffer;
        }

        public static short ReadInt16(int address)
        {
            return BitConverter.ToInt16(Read(new IntPtr(address), 2), 0);
        }

        public static int ReadInt32(int address)
        {
            return BitConverter.ToInt32(Read(new IntPtr(address), 4), 0);
        }

        public static byte ReadByte(int address)
        {
            return Read(new IntPtr(address), 1)[0];
        }

        public static float ReadSingle(int address)
        {
            return BitConverter.ToSingle(Read(new IntPtr(address), 4), 0);
        }

        public static string ReadFixedString(int address, int length)
        {
            var bytes = Read(new IntPtr(address), (uint)length);
            char[] buffer = new char[length];
            int i;

            for (i = 0; i < length; i++)
            {
                buffer[i] = (char)bytes[i];

                if (bytes[i] == 0)
                {
                    break;
                }
            }

            return new string(buffer, 0, i);
        }

        public static void Write(int address, byte[] data, uint size)
        {
            int bytes;

            WriteProcessMemory(GetCurrentProcess(), new IntPtr(address), data, size, out bytes);
        }

        public static void Write(int address, int value)
        {
            Write(address, BitConverter.GetBytes(value), 4);
        }

        public static void Write(int address, float value)
        {
            Write(address, BitConverter.GetBytes(value), 4);
        }

        public static void Write(int address, short value)
        {
            Write(address, BitConverter.GetBytes(value), 2);
        }

        public static void Write(int address, byte value)
        {
            Write(address, BitConverter.GetBytes(value), 1);
        }
    }
}