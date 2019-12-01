using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class Tasks
    {
        protected Ped _ped;

        internal Tasks(Ped ped)
        {
            _ped = ped;
        }

        public void AimAt(Ped ped, int duration)
        {
            Internal.Function.Call(0x0635, _ped, ped, duration);
        }

        public void AimAt(Vector3 position, int duration)
        {
            Internal.Function.Call(0x0667, _ped, position, duration);
        }

        public void Crouch(bool crouched)
        {
            Internal.Function.Call(0x04eb, _ped, crouched);
        }

        public void Die()
        {
            Internal.Function.Call(0x0762, _ped);
        }

        public void DriveBy(Ped target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, _ped, target, -1, 0f, 0f, 0f, radius, 4, 1, firingRate);
        }

        public void DriveBy(Vehicle target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, _ped, -1, target, 0f, 0f, 0f, radius, 4, 1, firingRate);
        }

        public void DriveBy(Vector3 target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, _ped, -1, -1, target, radius, 4, 1, firingRate);
        }

        internal void DriveBy()
        {
            Internal.Function.Call(0x0713, _ped, -1, -1, 0f, 0f, 0f, 0f, -9000, 0, 100);
        }

        public void EnterVehicle(Vehicle vehicle, VehicleSeat seat)
        {
            if (seat >= VehicleSeat.Driver)
            {
                if (seat == VehicleSeat.Driver)
                {
                    Internal.Function.Call(0x05cb, _ped, vehicle, -1);
                }
                else
                {
                    Internal.Function.Call(0x05ca, _ped, vehicle, -1, (int)seat);
                }
            }
        }

        public void FightAgainst(Ped ped)
        {
            Internal.Function.Call(0x05e2, _ped, ped);
        }

        public void FightAgainst(Ped ped, int duration)
        {
            Internal.Function.Call(0x07a5, _ped, ped, duration);
        }

        public void FleeFromPed(Ped ped)
        {
            FleeFromPed(ped, false);
        }

        public void FleeFromPed(Ped ped, bool prefersPavements)
        {
            FleeFromPed(ped, prefersPavements, -1);
        }

        public void FleeFromPed(Ped ped, bool prefersPavements, int duration)
        {
            if (prefersPavements)
            {
                Internal.Function.Call(0x05dd, _ped, ped, 100.0f, duration);
            }
            else
            {
                Internal.Function.Call(0x05db, _ped, ped, 100.0f, duration);
            }
        }

        public void GoTo(Vector3 position)
        {
            GoTo(position, false);
        }

        public void GoTo(Vector3 target, bool ignorePaths)
        {
            if (!ignorePaths)
            {
                Internal.Function.Call(0x0a2e, _ped, target, 2, -1, 1.0f);
            }
            else
            {
                Internal.Function.Call(0x05d3, _ped, target, 2, -1);
            }
        }

        public void Guard(int duration)
        {
            Internal.Function.Call(0x05c9, _ped, duration);
        }

        public void HandsUp(int duration)
        {
            if (duration < 0)
            {
                duration = 3600000;
            }

            Internal.Function.Call(0x05c4, _ped, duration);
        }

        public void LeaveVehicle()
        {
            Internal.Function.Call(0x0633, _ped);
        }

        public void LeaveVehicle(Vehicle vehicle)
        {
            Internal.Function.Call(0x05cd, _ped, vehicle);
        }

        public void LeaveVehicleImmediately(Vehicle vehicle)
        {
            Internal.Function.Call(0x0622, _ped, vehicle);
        }

        public void LookAt(Ped target, int duration)
        {
            Internal.Function.Call(0x05bf, _ped, target, duration);
        }

        public void LookAt(Vector3 target, int duration)
        {
            Internal.Function.Call(0x06a9, _ped, target, duration);
        }

        public void LookAt(Vehicle target, int duration)
        {
            Internal.Function.Call(0x05c0, _ped, target, duration);
        }

        public void PlayAnimation(string file, string animation, bool loop)
        {
            PlayAnimation(file, animation, loop, -2);
        }

        public void PlayAnimation(string file, string animation, bool loop, int duration)
        {
            LoadAnimation(file);
            Internal.Function.Call(0x0812, _ped, animation, file, 1f, loop, true, true, true, duration);
            FreeAnimation(file);
        }

        public static void LoadAnimation(string file)
        {
            file = file.ToLower().Replace(".ifp", "");

            if (file != "ped")
            {
                Internal.Function.Call(0x04ED, file);

                while (!Internal.Function.Call(0x04EE, file))
                {
                    GTAUtils.Wait(0);
                }
            }
        }

        public static void FreeAnimation(string file)
        {
            file = file.ToLower().Replace(".ifp", "");

            if (file != "ped")
            {
                Internal.Function.Call(0x04EF, file);
            }
        }

        public void RunTo(Vector3 target)
        {
            RunTo(target, false);
        }

        public void RunTo(Vector3 target, bool ignorePaths)
        {
            if (!ignorePaths)
            {
                Internal.Function.Call(0x0a2e, _ped, target, 4, -1, 1.0f);
            }
            else
            {
                Internal.Function.Call(0x05d3, _ped, target, 4, -1);
            }
        }

        public void StandStill(bool enable)
        {
            Internal.Function.Call(0x0638, _ped, enable);
        }

        public void Tire(int duration)
        {
            Internal.Function.Call(0x05bd, _ped, duration);
        }

        public void TurnTo(Ped target)
        {
            Internal.Function.Call(0x0a1d, _ped, target);
        }

        public void TurnTo(Vector3 target)
        {
            Internal.Function.Call(0x06ba, _ped, target);
        }

        public void Wander()
        {
            Internal.Function.Call(0x05de, _ped);
        }

        public void WarpIntoVehicle(Vehicle vehicle, VehicleSeat seat)
        {
            if (seat >= VehicleSeat.Driver)
            {
                if (seat == VehicleSeat.Driver)
                {
                    Internal.Function.Call(0x072a, _ped, vehicle);
                }
                else
                {
                    Internal.Function.Call(0x072b, _ped, vehicle, (int)seat);
                }
            }
        }
    }

    public class TaskSequence
    {
        private bool _closed;
        private bool _hasNullPed;
        private Ped _nullPed;
        private int _handle;

        ~TaskSequence()
        {
            Internal.Function.Call(0x061b, _handle);
        }

        public TaskSequence()
        {
            _handle = Internal.Function.Call<int>(0x0615);

            if (!_hasNullPed)
            {
                _hasNullPed = true;
                _nullPed = new Ped(-1);
            }
        }

        public void Perform(Ped ped)
        {
            if (!_closed)
            {
                _closed = true;
                Internal.Function.Call(0x0616, _handle);
            }

            ped.Tasks.ClearAll();

            Internal.Function.Call(0x0618, ped, _handle);
        }

        public Tasks Tasks
        {
            get
            {
                return _nullPed.Tasks;
            }
        }

        public int Handle
        {
            get
            {
                return _handle;
            }
        }
    }

    public class PedTasks : Tasks
    {
        internal PedTasks(Ped ped) : base(ped) { }

        public void ClearAll()
        {
            Internal.Function.Call(0x0687, _ped);
        }

        public void PerformSequence(TaskSequence sequence)
        {
            if (sequence != null)
            {
                sequence.Perform(this._ped);
            }
        }
    }
}
