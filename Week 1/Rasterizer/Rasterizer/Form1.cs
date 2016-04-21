using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Rasterizer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
        }
        List<Vector3> vertices = new List<Vector3>();
        List<List<int>> polygons = new List<List<int>>();
        float rotation = 0;


        private void Form1_Load(object sender, EventArgs e)
        {
            loadCilinder();
            //loadCone();
            //loadKube();
        }

        private void loadCilinder()
        {
            vertices.Add(new Vector3(0, 10, 0));

            vertices.Add(new Vector3(0, 0, 5));
            vertices.Add(new Vector3(2, 0, 4));
            vertices.Add(new Vector3(4, 0, 2));

            vertices.Add(new Vector3(5, 0, 0));
            vertices.Add(new Vector3(4, 0, -2));
            vertices.Add(new Vector3(2, 0, -4));

            vertices.Add(new Vector3(0, 0, -5));
            vertices.Add(new Vector3(-2, 0, -4));
            vertices.Add(new Vector3(-4, 0, -2));
                
            vertices.Add(new Vector3(-5, 0, 0));
            vertices.Add(new Vector3(-4, 0, 2));
            vertices.Add(new Vector3(-2, 0, 4));

        }
        private void loadCone()
        {
            vertices.Add(new Vector3(0, 10, 0));

            vertices.Add(new Vector3(0, 0, 5));
            vertices.Add(new Vector3(2, 0, 4));
            vertices.Add(new Vector3(4, 0, 2));

            vertices.Add(new Vector3(5, 0, 0));
            vertices.Add(new Vector3(4, 0, -2));
            vertices.Add(new Vector3(2, 0, -4));

            vertices.Add(new Vector3(0, 0, -5));
            vertices.Add(new Vector3(-2, 0, -4));
            vertices.Add(new Vector3(-4, 0, -2));

            vertices.Add(new Vector3(-5, 0, 0));
            vertices.Add(new Vector3(-4, 0, 2));
            vertices.Add(new Vector3(-2, 0, 4));

            polygons.Add(new List<int>() { 0, 1, 2 });
            polygons.Add(new List<int>() { 0, 2, 3 });
            polygons.Add(new List<int>() { 0, 3, 4 });
            polygons.Add(new List<int>() { 0, 4, 5 });
            polygons.Add(new List<int>() { 0, 5, 6 });
            polygons.Add(new List<int>() { 0, 6, 7 });
            polygons.Add(new List<int>() { 0, 7, 8 });
            polygons.Add(new List<int>() { 0, 8, 9 });
            polygons.Add(new List<int>() { 0, 9, 10 });
            polygons.Add(new List<int>() { 0, 10, 11 });
            polygons.Add(new List<int>() { 0, 11, 12 });
            polygons.Add(new List<int>() { 0, 12, 1 });
        }
        private void loadKube()
        {
            //initialise kube vertices & polygons
            vertices.Add(new Vector3(-1, -1, -1));
            vertices.Add(new Vector3(1, -1, -1));
            vertices.Add(new Vector3(1, 1, -1));
            vertices.Add(new Vector3(-1, 1, -1));
            vertices.Add(new Vector3(-1, -1, 1));
            vertices.Add(new Vector3(1, -1, 1));
            vertices.Add(new Vector3(1, 1, 1));
            vertices.Add(new Vector3(-1, 1, 1));

            polygons.Add(new List<int>() { 0, 1, 2, 3 });
            polygons.Add(new List<int>() { 0, 3, 7, 4 });
            polygons.Add(new List<int>() { 4, 5, 6, 7 });
            polygons.Add(new List<int>() { 1, 2, 6, 5 });
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            rotation += 0.01f;
            Invalidate();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            var g = e.Graphics;
            g.Clear(Color.LightGray);
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            Pen pen = new Pen(Color.Black, 2);

            //setup matrix
            Matrix matrix = Matrix.identity();
            matrix *= Matrix.perspective((float)Math.PI / 2, Width / Height, 0.1f, 20f);
            matrix *= Matrix.translate(new Vector3(0, -3, -10));
            matrix *= Matrix.rotation(rotation + 0.1f, new Vector3(0, 1, 0));

            //draw vertices
            for (int i = 0; i < vertices.Count; i++)
            {
                Vector3 vector = matrix * vertices[i];
                vector.x = Width / 2 + vector.x / vector.z * Width / 2;
                vector.y = Height / 2 + vector.y / vector.z * Height / 2;
                g.DrawRectangle(pen, vector.x - 5, vector.y - 5, 10, 10);
            }
            //draw polygons
            foreach (var polygon in polygons)
            {
                for (int i = 0; i < polygon.Count; i++)
                {
                    int point1 = polygon[i];
                    int point2 = polygon[0];
                    if (i != polygon.Count - 1)
                    {
                        point2 = polygon[i + 1];
                    }

                    Vector3 draw1 = matrix * vertices[point1];
                    draw1.x = Width / 2 + draw1.x / draw1.z * Width / 2;
                    draw1.y = Height / 2 + draw1.y / draw1.z * Height / 2;

                    Vector3 draw2 = matrix * vertices[point2];
                    draw2.x = Width / 2 + draw2.x / draw2.z * Width / 2;
                    draw2.y = Height / 2 + draw2.y / draw2.z * Height / 2;

                    g.DrawLine(pen, new Point((int)draw1.x, (int)draw1.y), new Point((int)draw2.x, (int)draw2.y));
                }
            }
        }

    }
}
