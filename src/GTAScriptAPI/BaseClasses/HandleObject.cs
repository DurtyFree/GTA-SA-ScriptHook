using GTA.Internal;

namespace GTA
{
    public class HandleObject
    {
        public int Handle { get; set; }
        public object ExtraData { get; set; }

        public HandleObject()
        {
            Handle = 0;
        }

        public HandleObject(int handle)
        {
            Handle = handle;
        }

        public static implicit operator Parameter(HandleObject source)
        {
            return new Parameter(source.Handle);
        }

        public static explicit operator HandleObject(int source)
        {
            return new HandleObject(source);
        }

        public static explicit operator HandleObject(VarPointer source)
        {
            return new HandleObject((int)source);
        }

        public override bool Equals(object obj)
        {
            return this == (HandleObject)obj;
        }

        public static bool operator ==(HandleObject left, HandleObject right)
        {
            if (ReferenceEquals(left, null))
            {
                return (ReferenceEquals(right, null));
            }

            if (ReferenceEquals(right, null))
            {
                return false;
            }

            return (left.Handle == right.Handle);
        }

        public static bool operator !=(HandleObject left, HandleObject right)
        {
            return (!(left == right));
        }

        public override int GetHashCode()
        {
            return Handle;
        }
    }
}
