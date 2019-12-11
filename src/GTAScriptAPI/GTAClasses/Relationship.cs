using System.Collections.Generic;

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
            Id = id;
        }

        public RelationshipGroup Id { get; }

        public void SetRelationTo(RelationshipGroup target, RelationshipType relation)
        {
            Internal.Function.Call(0x0746, (int)relation, (int)Id, (int)target);
        }

        public void RemoveRelationTo(RelationshipGroup target, RelationshipType relation)
        {
            Internal.Function.Call(0x0747, (int)relation, (int)Id, (int)target);
        }

        private static Dictionary<RelationshipGroup, Relationships> _instanceCache;

        public static Relationships FromId(RelationshipGroup id)
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

        public static Relationships Player1 => FromId(RelationshipGroup.Player1);

        public static Relationships Player2 => FromId(RelationshipGroup.Player2);

        public static Relationships PlayerNetwork => FromId(RelationshipGroup.PlayerNetwork);

        public static Relationships PlayerUnused => FromId(RelationshipGroup.PlayerUnused);

        public static Relationships CivMale => FromId(RelationshipGroup.CivMale);

        public static Relationships CivFemale => FromId(RelationshipGroup.CivFemale);

        public static Relationships Cop => FromId(RelationshipGroup.Cop);

        public static Relationships Gang1 => FromId(RelationshipGroup.Gang1);

        public static Relationships Gang2 => FromId(RelationshipGroup.Gang2);

        public static Relationships Gang3 => FromId(RelationshipGroup.Gang3);

        public static Relationships Gang4 => FromId(RelationshipGroup.Gang4);

        public static Relationships Gang5 => FromId(RelationshipGroup.Gang5);

        public static Relationships Gang6 => FromId(RelationshipGroup.Gang6);

        public static Relationships Gang7 => FromId(RelationshipGroup.Gang7);

        public static Relationships Gang8 => FromId(RelationshipGroup.Gang8);

        public static Relationships Gang9 => FromId(RelationshipGroup.Gang9);

        public static Relationships Gang10 => FromId(RelationshipGroup.Gang10);

        public static Relationships Dealer => FromId(RelationshipGroup.Dealer);

        public static Relationships Medic => FromId(RelationshipGroup.Medic);

        public static Relationships Fireman => FromId(RelationshipGroup.Fireman);

        public static Relationships Criminal => FromId(RelationshipGroup.Criminal);

        public static Relationships Bum => FromId(RelationshipGroup.Bum);

        public static Relationships Prostitute => FromId(RelationshipGroup.Prostitute);

        public static Relationships Special => FromId(RelationshipGroup.Special);

        public static Relationships Mission1 => FromId(RelationshipGroup.Mission1);

        public static Relationships Mission2 => FromId(RelationshipGroup.Mission2);

        public static Relationships Mission3 => FromId(RelationshipGroup.Mission3);

        public static Relationships Mission4 => FromId(RelationshipGroup.Mission4);

        public static Relationships Mission5 => FromId(RelationshipGroup.Mission5);

        public static Relationships Mission6 => FromId(RelationshipGroup.Mission6);

        public static Relationships Mission7 => FromId(RelationshipGroup.Mission7);

        public static Relationships Mission8 => FromId(RelationshipGroup.Mission8);
    }
}
