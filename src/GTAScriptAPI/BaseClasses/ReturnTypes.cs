using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class ReturnTypes : ScriptPostInitializer
    {
        public override void OnGameStart()
        {
            Internal.Function.RegisterType(typeof(float), delegate(object value)
            {
                return GTAUtils.ConvertIntAsFloat((int)value);
            });

            Internal.Function.RegisterType(typeof(HandleObject), DoHandleObject<HandleObject>);
            Internal.Function.RegisterType(typeof(Ped), DoHandleObject<Ped>);
            Internal.Function.RegisterType(typeof(Group), DoHandleObject<Group>);
            Internal.Function.RegisterType(typeof(Player), DoHandleObject<Player>);
            Internal.Function.RegisterType(typeof(Vehicle), DoHandleObject<Vehicle>);
            Internal.Function.RegisterType(typeof(Blip), DoHandleObject<Blip>);
            Internal.Function.RegisterType(typeof(Pickup), DoHandleObject<Pickup>);
            Internal.Function.RegisterType(typeof(Sphere), DoHandleObject<Sphere>);
        }

        public static object DoHandleObject<T>(object value) where T : HandleObject
        {
            HandleObject obj = (HandleObject)Activator.CreateInstance<T>();
            obj.Handle = (int)value;

            return obj;
        }
    }
}
