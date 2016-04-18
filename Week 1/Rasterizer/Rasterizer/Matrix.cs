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
            Matrix m = new Matrix(4);
            m.data[0, 0] = 1;
            m.data[1, 1] = 1;
            m.data[2, 2] = 1;
            m.data[3, 3] = 1;
            return m;
        }

        public static Matrix perspective(float fov, float aspect, float zNear, float zFar)
        {
            Matrix temp = Matrix.identity();
            temp.data[3, 2] = -1;
            temp.data[3, 3] = 0;


            temp.data[0, 0] = (float)((1 / Math.Tan(fov / 2)) / aspect);
            temp.data[1, 1] = (float)(1 / Math.Tan(fov / 2));
            temp.data[2, 2] = (float)(zFar / (zFar - zNear));
            temp.data[2, 3] = (float)((zNear * zFar) / (zFar - zNear));


            return temp;

            //1/tan

        }

        public static Matrix rotation(float angle, Vector3 axis)
        {
            double c = Math.Cos((double)angle);
            double s = Math.Sin((double)angle);
            Matrix temp = Matrix.identity();

            temp.data[0, 0] = (float)((Math.Sqrt((double)axis.x)) * (1 - c) + c);
            temp.data[0, 1] = (float)((axis.x * axis.y) * (1 - c) - (axis.z * s));
            temp.data[0, 2] = (float)((axis.x * axis.z) * (1 - c) + (axis.y * s));

            temp.data[1, 0] = (float)((axis.x * axis.y) * (1 - c) + (axis.z * s));
            temp.data[1, 1] = (float)((Math.Sqrt((double)axis.y)) * (1 - c) + c);
            temp.data[1, 2] = (float)((axis.y * axis.z) * (1 - c) - (axis.x * s));

            temp.data[2, 0] = (float)((axis.x * axis.z) * (1 - c) - (axis.y * s));
            temp.data[2, 1] = (float)((axis.y * axis.z) * (1 - c) + (axis.x * s));
            temp.data[2, 2] = (float)((Math.Sqrt((double)axis.z)) * (1 - c) + c);

            return temp;

        }
        public static Matrix translate(Vector3 offset)
        {
            Matrix temp = Matrix.identity();

            temp.data[0, 3] = offset.x;
            temp.data[1, 3] = offset.y;
            temp.data[2, 3] = offset.z;

            return temp;
        }



        public static Vector3 operator *(Matrix mat, Vector3 vec)
        {
            float tempx, tempy, tempz;

            tempx = (mat.data[0, 0] * vec.x) + (mat.data[0, 1] * vec.y) + (mat.data[0, 2] * vec.z) + mat.data[0, 3];
            tempy = (mat.data[1, 0] * vec.x) + (mat.data[1, 1] * vec.y) + (mat.data[1, 2] * vec.z) + mat.data[1, 3];
            tempz = (mat.data[2, 0] * vec.x) + (mat.data[2, 1] * vec.y) + (mat.data[2, 2] * vec.z) + mat.data[2, 3];

            return new Vector3(tempx, tempy, tempz);
        }

        public static Matrix operator *(Matrix mat1, Matrix mat2)
        {
            Matrix temp = Matrix.identity();


            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    temp.data[y, x] = (mat1.data[y, 0] * mat2.data[0, x]) +
                                      (mat1.data[y, 1] * mat2.data[1, x]) +
                                      (mat1.data[y, 2] * mat2.data[2, x]) +
                                      (mat1.data[y, 3] * mat2.data[3, x]);
                }
            }

            return temp;

            //for (int i = 0; i < 2; i++)
            //{
            //    temp.data[i, 0] = (mat1.data[0, 0] * mat2.data[0, 0]) + (mat1.data[0, 1] * mat2.data[1, 0]) + (mat1.data[0, 2] * mat2.data[2, 0]);
            //    temp.data[i, 1] = (mat1.data[0, 0] * mat2.data[0, 1]) + (mat1.data[0, 1] * mat2.data[1, 1]) + (mat1.data[0, 2] * mat2.data[2, 1]);
            //    temp.data[i, 2] = (mat1.data[0, 0] * mat2.data[0, 2]) + (mat1.data[0, 1] * mat2.data[1, 2]) + (mat1.data[0, 2] * mat2.data[2, 2]);
            //}

            //temp.data[0, 0] = (mat1.data[0, 0] * mat2.data[0, 0]) + (mat1.data[0, 1] * mat2.data[1, 0]) + (mat1.data[0, 2] * mat2.data[2, 0]);
            //temp.data[0, 1] = (mat1.data[0, 0] * mat2.data[0, 1]) + (mat1.data[0, 1] * mat2.data[1, 1]) + (mat1.data[0, 2] * mat2.data[2, 1]);
            //temp.data[0, 2] = (mat1.data[0, 0] * mat2.data[0, 2]) + (mat1.data[0, 1] * mat2.data[1, 2]) + (mat1.data[0, 2] * mat2.data[2, 2]);


            throw new NotImplementedException();
        }

    }
}
