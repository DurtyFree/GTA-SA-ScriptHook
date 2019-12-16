using System;
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

        /// <summary>
        /// Handle is added as the first parameter
        /// </summary>
        /// <param name="opCode"></param>
        /// <param name="parameters"></param>
        /// <returns></returns>
        public bool OpCodeCallOnHandle(OpCodes opCode, params Parameter[] parameters) => OpCode.Call(opCode, this.GetCallParameter(parameters));

        /// <summary>
        /// Handle is added as the first parameter
        /// </summary>
        /// <typeparam name="TReturn"></typeparam>
        /// <param name="opCode"></param>
        /// <param name="parameters"></param>
        /// <returns></returns>
        public TReturn OpCodeCallOnHandle<TReturn>(OpCodes opCode, params Parameter[] parameters) => OpCode.Call<TReturn>(opCode, this.GetCallParameter(parameters));

        private Parameter[] GetCallParameter(Parameter[] parameters)
        {
            var param = new Parameter[parameters.Length + 1];
            param[0] = this;

            if (parameters.Length > 0)
            {
                Buffer.BlockCopy(parameters, 0, param, 1, parameters.Length);
            }

            return param;
        }
    }
}
