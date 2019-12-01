using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class Group : HandleObject
    {
        internal static Group FromPlayer(Player player)
        {
            return Internal.Function.Call<Group>(0x07AF, player);
        }

        public static Group CreateGroup(Ped leader)
        {
            var group = Internal.Function.Call<Group>(0x062F, 0);
            group.AddPed(leader, true);

            return group;
        }

        public void AddPed(Ped ped)
        {
            AddPed(ped, false);
        }

        public void AddPed(Ped ped, bool isLeader)
        {
            if (isLeader)
            {
                Internal.Function.Call(0x0630, this, ped);
            }
            else
            {
                Internal.Function.Call(0x0631, this, ped);
            }
        }

        public bool IsPedInGroup(Ped ped)
        {
            return Internal.Function.Call(0x06EE, ped, this);
        }

        public bool IsPedLeader(Ped ped)
        {
            return Internal.Function.Call(0x06EF, ped, this);
        }

        public void Delete()
        {
            Internal.Function.Call(0x0632, this);
        }

        public float MaxDistance
        {
            set
            {
                Internal.Function.Call(0x06F0, this, value);
            }
        }

        public int MemberCount
        {
            get
            {
                return Internal.Function.Call<int>(0x07F6, this, new VarPointer());
            }
        }

        public int LeaderCount
        {
            get
            {
                VarPointer vp = new VarPointer();
                Internal.Function.Call(0x07F6, this, vp, new VarPointer());
                return (int)vp;
            }
        }

        public Ped[] Members
        {
            get
            {
                int count = MemberCount; // possible '+ LeaderCount?'
                List<Ped> retval = new List<Ped>();

                for (int i = 0; i < count; i++)
                {
                    retval.Add(Internal.Function.Call<Ped>(0x092B, this, i));
                }

                return retval.ToArray();
            }
        }
    }
}
