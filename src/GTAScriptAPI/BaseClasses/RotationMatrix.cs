using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public class RotationMatrix
    {
        public float M00 { get; set; }
        public float M01 { get; set; }
        public float M02 { get; set; }

        public float M10 { get; set; }
        public float M11 { get; set; }
        public float M12 { get; set; }

        public float M20 { get; set; }
        public float M21 { get; set; }
        public float M22 { get; set; }

        public static RotationMatrix Multiply(RotationMatrix left, RotationMatrix right)
        {
            RotationMatrix result = new RotationMatrix();
            result.M00 = (left.M00 * right.M00) + (left.M01 * right.M10) + (left.M02 * right.M20);
            result.M01 = (left.M00 * right.M01) + (left.M01 * right.M11) + (left.M02 * right.M21);
            result.M02 = (left.M00 * right.M02) + (left.M01 * right.M12) + (left.M02 * right.M22);

            result.M10 = (left.M10 * right.M00) + (left.M11 * right.M10) + (left.M12 * right.M20);
            result.M11 = (left.M10 * right.M01) + (left.M11 * right.M11) + (left.M12 * right.M21);
            result.M12 = (left.M10 * right.M02) + (left.M11 * right.M12) + (left.M12 * right.M22);

            result.M20 = (left.M20 * right.M00) + (left.M21 * right.M10) + (left.M22 * right.M20);
            result.M21 = (left.M20 * right.M01) + (left.M21 * right.M11) + (left.M22 * right.M21);
            result.M22 = (left.M20 * right.M02) + (left.M21 * right.M12) + (left.M22 * right.M22);

            return result;

            // this code was before I remembered matrix multiplication is hard.
            /*RotationMatrix m = new RotationMatrix();
            m.M00 = m1.M00 * m2.M00;
            m.M01 = m1.M01 * m2.M01;
            m.M02 = m1.M02 * m2.M02;

            m.M10 = m1.M10 * m2.M10;
            m.M11 = m1.M11 * m2.M11;
            m.M12 = m1.M12 * m2.M12;

            m.M20 = m1.M20 * m2.M20;
            m.M21 = m1.M21 * m2.M21;
            m.M22 = m1.M22 * m2.M22;

            return m;*/
        }

        public static RotationMatrix operator *(RotationMatrix left, RotationMatrix right)
        {
            return Multiply(left, right);
        }

        public static RotationMatrix RotateX(float degrees)
        {
            float radians = (float)(degrees * (Math.PI / 180));

            RotationMatrix matrix = new RotationMatrix();
            matrix.M00 = 1;
            matrix.M01 = 0;
            matrix.M02 = 0;

            matrix.M10 = 0;
            matrix.M11 = (float)Math.Cos(radians);
            matrix.M12 = -((float)Math.Sin(radians));

            matrix.M20 = 0;
            matrix.M21 = (float)Math.Sin(radians);
            matrix.M22 = (float)Math.Cos(radians);

            return matrix;
        }

        public static RotationMatrix RotateY(float degrees)
        {
            float radians = (float)(degrees * (Math.PI / 180));

            RotationMatrix matrix = new RotationMatrix();
            matrix.M00 = (float)Math.Cos(radians);
            matrix.M01 = -((float)Math.Sin(radians));
            matrix.M02 = 0;

            matrix.M10 = (float)Math.Sin(radians);
            matrix.M11 = (float)Math.Cos(radians);
            matrix.M12 = 0;

            matrix.M20 = 0;
            matrix.M21 = 0;
            matrix.M22 = 1;

            return matrix;
        }

        public static RotationMatrix RotateZ(float degrees)
        {
            float radians = (float)(degrees * (Math.PI / 180));

            RotationMatrix matrix = new RotationMatrix();
            matrix.M00 = (float)Math.Cos(radians);
            matrix.M01 = 0;
            matrix.M02 = (float)Math.Sin(radians);

            matrix.M10 = 0;
            matrix.M11 = 1;
            matrix.M12 = 0;

            matrix.M20 = -((float)Math.Sin(radians));
            matrix.M21 = 0;
            matrix.M22 = (float)Math.Cos(radians);

            return matrix;
        }

        public static RotationMatrix Rotate(float x, float y, float z)
        {
            return RotationMatrix.RotateX(x) * RotationMatrix.RotateY(y) * RotationMatrix.RotateZ(z);
        }

        // code from http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToEuler/index.htm
        // adapted to C# and the flipped Y/Z of game coordinates
        public float[] ToEuler()
        {
            float[] retval = new float[3];

            if (M10 > 0.998f)
            {
                retval[0] = 0f;
                retval[1] = (float)(Math.PI / 2);
                retval[2] = (float)Math.Atan2(M02, M22);

                return ToDeg(retval);
            }

            if (M10 < -0.998f)
            {
                retval[0] = 0f;
                retval[1] = -((float)(Math.PI / 2));
                retval[2] = (float)Math.Atan2(M02, M22);

                return ToDeg(retval);
            }

            retval[0] = (float)Math.Atan2(-M12, M11);
            retval[1] = (float)Math.Asin(M10);
            retval[2] = (float)Math.Atan2(-M20, M00);

            return ToDeg(retval);
        }

        private float[] ToDeg(float[] value)
        {
            float[] retval = new float[3];
            retval[0] = (float)(value[0] / (Math.PI / 180));
            retval[1] = (float)(value[1] / (Math.PI / 180));
            retval[2] = (float)(value[2] / (Math.PI / 180));

            return retval;
        }
    }
}
