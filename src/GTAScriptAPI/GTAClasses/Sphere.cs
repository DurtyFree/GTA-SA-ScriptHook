using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class Sphere : HandleObject
    {
        public void Delete()
        {
            Internal.Function.Call(0x03BD, this);
        }
    }
}
