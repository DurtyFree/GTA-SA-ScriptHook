using GTA.Internal;

namespace GTA
{
    public class HandleObject
    {
        public int Handle { get; set; }
        public object ExtraData { get; set; }

        public HandleObject()
        {
            this.Handle = 0;
        }

        public HandleObject(int handle)
        {
            this.Handle = handle;
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
            if (object.ReferenceEquals(left, null))
            {
                return (object.ReferenceEquals(right, null));
            }

            if (object.ReferenceEquals(right, null))
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
            return this.Handle;
        }
    }
}
