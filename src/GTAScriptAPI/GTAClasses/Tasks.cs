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
            this._ped = ped;
        }

        public void AimAt(Ped ped, int duration)
        {
            Internal.Function.Call(0x0635, this._ped, ped, duration);
        }

        public void AimAt(Vector3 position, int duration)
        {
            Internal.Function.Call(0x0667, this._ped, position, duration);
        }

        public void Crouch(bool crouched)
        {
            Internal.Function.Call(0x04eb, this._ped, crouched);
        }

        public void Die()
        {
            Internal.Function.Call(0x0762, this._ped);
        }

        public void DriveBy(Ped target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, this._ped, target, -1, 0f, 0f, 0f, radius, 4, 1, firingRate);
        }

        public void DriveBy(Vehicle target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, this._ped, -1, target, 0f, 0f, 0f, radius, 4, 1, firingRate);
        }

        public void DriveBy(Vector3 target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, this._ped, -1, -1, target, radius, 4, 1, firingRate);
        }

        internal void DriveBy()
        {
            Internal.Function.Call(0x0713, this._ped, -1, -1, 0f, 0f, 0f, 0f, -9000, 0, 100);
        }

        public void EnterVehicle(Vehicle vehicle, VehicleSeat seat)
        {
            if (seat >= VehicleSeat.Driver)
            {
                if (seat == VehicleSeat.Driver)
                {
                    Internal.Function.Call(0x05cb, this._ped, vehicle, -1);
                }
                else
                {
                    Internal.Function.Call(0x05ca, this._ped, vehicle, -1, (int)seat);
                }
            }
        }

        public void FightAgainst(Ped ped)
        {
            Internal.Function.Call(0x05e2, this._ped, ped);
        }

        public void FightAgainst(Ped ped, int duration)
        {
            Internal.Function.Call(0x07a5, this._ped, ped, duration);
        }

        public void FleeFromPed(Ped ped)
        {
            this.FleeFromPed(ped, false);
        }

        public void FleeFromPed(Ped ped, bool prefersPavements)
        {
            this.FleeFromPed(ped, prefersPavements, -1);
        }

        public void FleeFromPed(Ped ped, bool prefersPavements, int duration)
        {
            if (prefersPavements)
            {
                Internal.Function.Call(0x05dd, this._ped, ped, 100.0f, duration);
            }
            else
            {
                Internal.Function.Call(0x05db, this._ped, ped, 100.0f, duration);
            }
        }

        public void GoTo(Vector3 position)
        {
            this.GoTo(position, false);
        }

        public void GoTo(Vector3 target, bool ignorePaths)
        {
            if (!ignorePaths)
            {
                Internal.Function.Call(0x0a2e, this._ped, target, 2, -1, 1.0f);
            }
            else
            {
                Internal.Function.Call(0x05d3, this._ped, target, 2, -1);
            }
        }

        public void Guard(int duration)
        {
            Internal.Function.Call(0x05c9, this._ped, duration);
        }

        public void HandsUp(int duration)
        {
            if (duration < 0)
            {
                duration = 3600000;
            }

            Internal.Function.Call(0x05c4, this._ped, duration);
        }

        public void LeaveVehicle()
        {
            Internal.Function.Call(0x0633, this._ped);
        }

        public void LeaveVehicle(Vehicle vehicle)
        {
            Internal.Function.Call(0x05cd, this._ped, vehicle);
        }

        public void LeaveVehicleImmediately(Vehicle vehicle)
        {
            Internal.Function.Call(0x0622, this._ped, vehicle);
        }

        public void LookAt(Ped target, int duration)
        {
            Internal.Function.Call(0x05bf, this._ped, target, duration);
        }

        public void LookAt(Vector3 target, int duration)
        {
            Internal.Function.Call(0x06a9, this._ped, target, duration);
        }

        public void LookAt(Vehicle target, int duration)
        {
            Internal.Function.Call(0x05c0, this._ped, target, duration);
        }

        public void PlayAnimation(string file, string animation, bool loop)
        {
            this.PlayAnimation(file, animation, loop, -2);
        }

        public void PlayAnimation(string file, string animation, bool loop, int duration)
        {
            LoadAnimation(file);
            Internal.Function.Call(0x0812, this._ped, animation, file, 1f, loop, true, true, true, duration);
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
            this.RunTo(target, false);
        }

        public void RunTo(Vector3 target, bool ignorePaths)
        {
            if (!ignorePaths)
            {
                Internal.Function.Call(0x0a2e, this._ped, target, 4, -1, 1.0f);
            }
            else
            {
                Internal.Function.Call(0x05d3, this._ped, target, 4, -1);
            }
        }

        public void StandStill(bool enable)
        {
            Internal.Function.Call(0x0638, this._ped, enable);
        }

        public void Tire(int duration)
        {
            Internal.Function.Call(0x05bd, this._ped, duration);
        }

        public void TurnTo(Ped target)
        {
            Internal.Function.Call(0x0a1d, this._ped, target);
        }

        public void TurnTo(Vector3 target)
        {
            Internal.Function.Call(0x06ba, this._ped, target);
        }

        public void Wander()
        {
            Internal.Function.Call(0x05de, this._ped);
        }

        public void WarpIntoVehicle(Vehicle vehicle, VehicleSeat seat)
        {
            if (seat >= VehicleSeat.Driver)
            {
                if (seat == VehicleSeat.Driver)
                {
                    Internal.Function.Call(0x072a, this._ped, vehicle);
                }
                else
                {
                    Internal.Function.Call(0x072b, this._ped, vehicle, (int)seat);
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
            Internal.Function.Call(0x061b, this._handle);
        }

        public TaskSequence()
        {
            this._handle = Internal.Function.Call<int>(0x0615);

            if (!this._hasNullPed)
            {
                this._hasNullPed = true;
                this._nullPed = new Ped(-1);
            }
        }

        public void Perform(Ped ped)
        {
            if (!this._closed)
            {
                this._closed = true;
                Internal.Function.Call(0x0616, this._handle);
            }

            ped.Tasks.ClearAll();

            Internal.Function.Call(0x0618, ped, this._handle);
        }

        public Tasks Tasks
        {
            get
            {
                return this._nullPed.Tasks;
            }
        }

        public int Handle
        {
            get
            {
                return this._handle;
            }
        }
    }

    public class PedTasks : Tasks
    {
        internal PedTasks(Ped ped) : base(ped) { }

        public void ClearAll()
        {
            Internal.Function.Call(0x0687, this._ped);
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
