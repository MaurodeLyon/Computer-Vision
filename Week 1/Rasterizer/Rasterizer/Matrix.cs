using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rasterizer
{
    struct Matrix
    {
        float[,] data;

        private Matrix(int size = 4)
        {
            data = new float[size, size];
        }


        public static Matrix identity()
        {
            Matrix matrix = new Matrix(4);
            matrix.data[0, 0] = 1;
            matrix.data[1, 1] = 1;
            matrix.data[2, 2] = 1;
            matrix.data[3, 3] = 1;
            return matrix;
        }

        public static Matrix perspective(float fov, float aspect, float zNear, float zFar)
        {
            Matrix result = identity();

            result.data[0, 0] = (float)(Math.Atan(fov / 2)) / (aspect);
            result.data[1, 1] = (float)Math.Atan(fov / 2);
            result.data[2, 2] = (zFar) / (zFar - zNear);
            result.data[2, 3] = -1;
            result.data[3, 2] = (zNear * zFar) / (zFar - zNear);
            result.data[3, 3] = 0;

            return result;
        }

        public static Matrix rotation(float angle, Vector3 axis)
        {
            Matrix result = identity();
            float c = (float)Math.Cos(angle);
            float s = (float)Math.Sin(angle);
            float x = axis.x;
            float y = axis.y;
            float z = axis.z;

            result.data[0, 0] = x * x * (1 - c) + c;
            result.data[0, 1] = x * y * (1 - c) - z * s;
            result.data[0, 2] = x * z * (1 - c) + y * s;
            result.data[0, 3] = 0;

            result.data[1, 0] = x * y * (1 - c) + z * s;
            result.data[1, 1] = y * y * (1 - c) + c;
            result.data[1, 2] = y * z * (1 - c) - x * s;
            result.data[1, 3] = 0;


            result.data[2, 0] = x * z * (1 - c) - y * s;
            result.data[2, 1] = y * z * (1 - c) + x * s;
            result.data[2, 2] = z * z * (1 - c) + c;
            result.data[2, 3] = 0;


            result.data[3, 0] = 0;
            result.data[3, 1] = 0;
            result.data[3, 2] = 0;
            result.data[3, 3] = 1;

            return result;
        }

        public static Matrix translate(Vector3 offset)
        {
            Matrix result = identity();

            result.data[3, 0] += offset.x;
            result.data[3, 1] += offset.y;
            result.data[3, 2] += offset.z;
            result.data[3, 3] = 1;

            return result;
        }

        public static Vector3 operator *(Matrix mat, Vector3 vec)
        {
            Vector3 result = new Vector3(0, 0, 0);

            result.x = mat.data[0, 0] * vec.x + mat.data[0, 1] * vec.y + mat.data[0, 2] * vec.z + mat.data[0, 3];
            result.y = mat.data[1, 0] * vec.x + mat.data[1, 1] * vec.y + mat.data[1, 2] * vec.z + mat.data[1, 3];
            result.z = mat.data[2, 0] * vec.x + mat.data[2, 1] * vec.y + mat.data[2, 2] * vec.z + mat.data[2, 3];

            return result;
        }

        public static Matrix operator *(Matrix mat1, Matrix mat2)
        {
            Matrix matrix = identity();
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    matrix.data[x, y] = (mat1.data[x, 0] * mat2.data[0, y]) + 
                                        (mat1.data[x, 1] * mat2.data[1, y]) + 
                                        (mat1.data[x, 2] * mat2.data[2, y]) + 
                                        (mat1.data[x, 3] * mat2.data[3, y]);
                }
            }
            return matrix;
        }
    }
}
