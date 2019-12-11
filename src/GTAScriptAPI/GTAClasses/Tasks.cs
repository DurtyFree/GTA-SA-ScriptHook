namespace GTA
{
    public class Tasks
    {
        protected Ped Ped;

        internal Tasks(Ped ped)
        {
            Ped = ped;
        }

        public void AimAt(Ped ped, int duration)
        {
            Internal.Function.Call(0x0635, Ped, ped, duration);
        }

        public void AimAt(Vector3 position, int duration)
        {
            Internal.Function.Call(0x0667, Ped, position, duration);
        }

        public void Crouch(bool crouched)
        {
            Internal.Function.Call(0x04eb, Ped, crouched);
        }

        public void Die()
        {
            Internal.Function.Call(0x0762, Ped);
        }

        public void DriveBy(Ped target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, Ped, target, -1, 0f, 0f, 0f, radius, 4, 1, firingRate);
        }

        public void DriveBy(Vehicle target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, Ped, -1, target, 0f, 0f, 0f, radius, 4, 1, firingRate);
        }

        public void DriveBy(Vector3 target, float radius, int firingRate)
        {
            Internal.Function.Call(0x0713, Ped, -1, -1, target, radius, 4, 1, firingRate);
        }

        internal void DriveBy()
        {
            Internal.Function.Call(0x0713, Ped, -1, -1, 0f, 0f, 0f, 0f, -9000, 0, 100);
        }

        public void EnterVehicle(Vehicle vehicle, VehicleSeat seat)
        {
            if (seat >= VehicleSeat.Driver)
            {
                if (seat == VehicleSeat.Driver)
                {
                    Internal.Function.Call(0x05cb, Ped, vehicle, -1);
                }
                else
                {
                    Internal.Function.Call(0x05ca, Ped, vehicle, -1, (int)seat);
                }
            }
        }

        public void FightAgainst(Ped ped)
        {
            Internal.Function.Call(0x05e2, Ped, ped);
        }

        public void FightAgainst(Ped ped, int duration)
        {
            Internal.Function.Call(0x07a5, Ped, ped, duration);
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
                Internal.Function.Call(0x05dd, Ped, ped, 100.0f, duration);
            }
            else
            {
                Internal.Function.Call(0x05db, Ped, ped, 100.0f, duration);
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
                Internal.Function.Call(0x0a2e, Ped, target, 2, -1, 1.0f);
            }
            else
            {
                Internal.Function.Call(0x05d3, Ped, target, 2, -1);
            }
        }

        public void Guard(int duration)
        {
            Internal.Function.Call(0x05c9, Ped, duration);
        }

        public void HandsUp(int duration)
        {
            if (duration < 0)
            {
                duration = 3600000;
            }

            Internal.Function.Call(0x05c4, Ped, duration);
        }

        public void LeaveVehicle()
        {
            Internal.Function.Call(0x0633, Ped);
        }

        public void LeaveVehicle(Vehicle vehicle)
        {
            Internal.Function.Call(0x05cd, Ped, vehicle);
        }

        public void LeaveVehicleImmediately(Vehicle vehicle)
        {
            Internal.Function.Call(0x0622, Ped, vehicle);
        }

        public void LookAt(Ped target, int duration)
        {
            Internal.Function.Call(0x05bf, Ped, target, duration);
        }

        public void LookAt(Vector3 target, int duration)
        {
            Internal.Function.Call(0x06a9, Ped, target, duration);
        }

        public void LookAt(Vehicle target, int duration)
        {
            Internal.Function.Call(0x05c0, Ped, target, duration);
        }

        public void PlayAnimation(string file, string animation, bool loop)
        {
            PlayAnimation(file, animation, loop, -2);
        }

        public void PlayAnimation(string file, string animation, bool loop, int duration)
        {
            LoadAnimation(file);
            Internal.Function.Call(0x0812, Ped, animation, file, 1f, loop, true, true, true, duration);
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
                Internal.Function.Call(0x0a2e, Ped, target, 4, -1, 1.0f);
            }
            else
            {
                Internal.Function.Call(0x05d3, Ped, target, 4, -1);
            }
        }

        public void StandStill(bool enable)
        {
            Internal.Function.Call(0x0638, Ped, enable);
        }

        public void Tire(int duration)
        {
            Internal.Function.Call(0x05bd, Ped, duration);
        }

        public void TurnTo(Ped target)
        {
            Internal.Function.Call(0x0a1d, Ped, target);
        }

        public void TurnTo(Vector3 target)
        {
            Internal.Function.Call(0x06ba, Ped, target);
        }

        public void Wander()
        {
            Internal.Function.Call(0x05de, Ped);
        }

        public void WarpIntoVehicle(Vehicle vehicle, VehicleSeat seat)
        {
            if (seat >= VehicleSeat.Driver)
            {
                if (seat == VehicleSeat.Driver)
                {
                    Internal.Function.Call(0x072a, Ped, vehicle);
                }
                else
                {
                    Internal.Function.Call(0x072b, Ped, vehicle, (int)seat);
                }
            }
        }
    }

    public class TaskSequence
    {
        private bool _closed;
        private readonly bool _hasNullPed;
        private readonly Ped _nullPed;

        ~TaskSequence()
        {
            Internal.Function.Call(0x061b, Handle);
        }

        public TaskSequence()
        {
            Handle = Internal.Function.Call<int>(0x0615);

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
                Internal.Function.Call(0x0616, Handle);
            }

            ped.Tasks.ClearAll();

            Internal.Function.Call(0x0618, ped, Handle);
        }

        public Tasks Tasks => _nullPed.Tasks;

        public int Handle { get; }
    }

    public class PedTasks : Tasks
    {
        internal PedTasks(Ped ped) : base(ped) { }

        public void ClearAll()
        {
            Internal.Function.Call(0x0687, Ped);
        }

        public void PerformSequence(TaskSequence sequence)
        {
            if (sequence != null)
            {
                sequence.Perform(Ped);
            }
        }
    }
}
