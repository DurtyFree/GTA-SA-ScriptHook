using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public enum CameraLookMode
    {
        Normal = 2,
        Transverse = 1
    }

    public class Camera
    {
        public static int TransverseDelay
        {
            set
            {
#if !GTA_IV
                Internal.Function.Call(0x0460, 0.0f, value);
#endif
            }
        }

#if GTA_SA
        public static float FOV
        {
            get
            {
                return NativeFunctions.GetCameraFOV();
            }
            set
            {
                NativeFunctions.SetCameraFOV(value);
            }
        }
#endif

        public static void SetPosition(Vector3 position, Vector3 rotation)
        {
            Internal.Function.Call(0x015f, position, rotation);
        }

        public static void LookAt(Vector3 position, CameraLookMode mode)
        {
            Internal.Function.Call(0x0160, position, (int)mode);
        }

        public static void LookAt(Vehicle vehicle, CameraLookMode mode)
        {
            Internal.Function.Call(0x0158, vehicle, 15, (int)mode);
        }

        public static void Restore()
        {
            Restore(false);
        }

        public static void Restore(bool instantly)
        {
            if (instantly)
            {
                Internal.Function.Call(0x02eb);
            }
            else
            {
                Internal.Function.Call(0x015a);
            }
        }

        public static bool IsSphereVisible(Vector3 position, float radius)
        {
            return Internal.Function.Call(0x00c2, position, radius);
        }
    }
}
