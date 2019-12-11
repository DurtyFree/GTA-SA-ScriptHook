using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public enum RelationshipType
    {
        Respect = 1,
        Like = 2,
        Dislike = 3,
        Hate = 4
    }

    public enum RelationshipGroup
    {
        Player1 = 0,
        Player2 = 1,
        PlayerNetwork = 2,
        PlayerUnused = 3,
        CivMale = 4,
        CivFemale = 5,
        Cop = 6,
        Gang1 = 7,
        Gang2 = 8,
        Gang3 = 9,
        Gang4 = 10,
        Gang5 = 11,
        Gang6 = 12,
        Gang7 = 13,
        Gang8 = 14,
        Gang9 = 15,
        Gang10 = 16,
        Dealer = 17,
        Medic = 18,
        Fireman = 19,
        Criminal = 20,
        Bum = 21,
        Prostitute = 22,
        Special = 23,
        Mission1 = 24,
        Mission2 = 25,
        Mission3 = 26,
        Mission4 = 27,
        Mission5 = 28,
        Mission6 = 29,
        Mission7 = 30,
        Mission8 = 31
    }

    public class Relationships
    {
        private Relationships(RelationshipGroup id)
        {
            this._pedType = id;
        }

        private RelationshipGroup _pedType;

        public RelationshipGroup ID
        {
            get
            {
                return this._pedType;
            }
        }

        public void SetRelationTo(RelationshipGroup target, RelationshipType relation)
        {
            Internal.Function.Call(0x0746, (int)relation, (int)this._pedType, (int)target);
        }

        public void RemoveRelationTo(RelationshipGroup target, RelationshipType relation)
        {
            Internal.Function.Call(0x0747, (int)relation, (int)this._pedType, (int)target);
        }

        private static Dictionary<RelationshipGroup, Relationships> _instanceCache;

        public static Relationships FromID(RelationshipGroup id)
        {
            Relationships retval = null;

            if (_instanceCache == null)
            {
                _instanceCache = new Dictionary<RelationshipGroup, Relationships>();
            }
            else if (_instanceCache.TryGetValue(id, out retval))
            {
                return retval;
            }

            retval = new Relationships(id);
            _instanceCache.Add(id, retval);

            return retval;
        }

        public static Relationships Player1
        {
            get
            {
                return FromID(RelationshipGroup.Player1);
            }
        }

        public static Relationships Player2
        {
            get
            {
                return FromID(RelationshipGroup.Player2);
            }
        }

        public static Relationships PlayerNetwork
        {
            get
            {
                return FromID(RelationshipGroup.PlayerNetwork);
            }
        }

        public static Relationships PlayerUnused
        {
            get
            {
                return FromID(RelationshipGroup.PlayerUnused);
            }
        }

        public static Relationships CivMale
        {
            get
            {
                return FromID(RelationshipGroup.CivMale);
            }
        }

        public static Relationships CivFemale
        {
            get
            {
                return FromID(RelationshipGroup.CivFemale);
            }
        }

        public static Relationships Cop
        {
            get
            {
                return FromID(RelationshipGroup.Cop);
            }
        }

        public static Relationships Gang1
        {
            get
            {
                return FromID(RelationshipGroup.Gang1);
            }
        }

        public static Relationships Gang2
        {
            get
            {
                return FromID(RelationshipGroup.Gang2);
            }
        }

        public static Relationships Gang3
        {
            get
            {
                return FromID(RelationshipGroup.Gang3);
            }
        }

        public static Relationships Gang4
        {
            get
            {
                return FromID(RelationshipGroup.Gang4);
            }
        }

        public static Relationships Gang5
        {
            get
            {
                return FromID(RelationshipGroup.Gang5);
            }
        }

        public static Relationships Gang6
        {
            get
            {
                return FromID(RelationshipGroup.Gang6);
            }
        }

        public static Relationships Gang7
        {
            get
            {
                return FromID(RelationshipGroup.Gang7);
            }
        }

        public static Relationships Gang8
        {
            get
            {
                return FromID(RelationshipGroup.Gang8);
            }
        }

        public static Relationships Gang9
        {
            get
            {
                return FromID(RelationshipGroup.Gang9);
            }
        }

        public static Relationships Gang10
        {
            get
            {
                return FromID(RelationshipGroup.Gang10);
            }
        }

        public static Relationships Dealer
        {
            get
            {
                return FromID(RelationshipGroup.Dealer);
            }
        }

        public static Relationships Medic
        {
            get
            {
                return FromID(RelationshipGroup.Medic);
            }
        }

        public static Relationships Fireman
        {
            get
            {
                return FromID(RelationshipGroup.Fireman);
            }
        }

        public static Relationships Criminal
        {
            get
            {
                return FromID(RelationshipGroup.Criminal);
            }
        }

        public static Relationships Bum
        {
            get
            {
                return FromID(RelationshipGroup.Bum);
            }
        }

        public static Relationships Prostitute
        {
            get
            {
                return FromID(RelationshipGroup.Prostitute);
            }
        }

        public static Relationships Special
        {
            get
            {
                return FromID(RelationshipGroup.Special);
            }
        }

        public static Relationships Mission1
        {
            get
            {
                return FromID(RelationshipGroup.Mission1);
            }
        }

        public static Relationships Mission2
        {
            get
            {
                return FromID(RelationshipGroup.Mission2);
            }
        }

        public static Relationships Mission3
        {
            get
            {
                return FromID(RelationshipGroup.Mission3);
            }
        }

        public static Relationships Mission4
        {
            get
            {
                return FromID(RelationshipGroup.Mission4);
            }
        }

        public static Relationships Mission5
        {
            get
            {
                return FromID(RelationshipGroup.Mission5);
            }
        }

        public static Relationships Mission6
        {
            get
            {
                return FromID(RelationshipGroup.Mission6);
            }
        }

        public static Relationships Mission7
        {
            get
            {
                return FromID(RelationshipGroup.Mission7);
            }
        }

        public static Relationships Mission8
        {
            get
            {
                return FromID(RelationshipGroup.Mission8);
            }
        }
    }
}
