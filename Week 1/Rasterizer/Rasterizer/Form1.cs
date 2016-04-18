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
            Matrix m = Matrix.identity();
            Matrix m2 = Matrix.identity();
            Vector3 v = new Vector3(4, 5, 6);
            Matrix r = m * m2;
            this.DoubleBuffered = true;
        }
        List<Vector3> vertices = new List<Vector3>();
        List<List<int>> polygons = new List<List<int>>();
        float rotation = 0;


        private void Form1_Load(object sender, EventArgs e)
        {
            //initialise vertices & polygons here
            vertices.Add(new Vector3(-1, -1, -1));
            vertices.Add(new Vector3(1, -1, -1));
            vertices.Add(new Vector3(1, 1, -1));
            vertices.Add(new Vector3(-1, 1, -1));

            vertices.Add(new Vector3(-1, -1, 1));
            vertices.Add(new Vector3(1, -1, 1));
            vertices.Add(new Vector3(1, 1, 1));
            vertices.Add(new Vector3(-1, 1, 1));
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

            Matrix m = Matrix.identity();
            m *= Matrix.perspective((float)Math.PI / 2, Width/Height, 0.1f, 20f);
            m *= Matrix.rotation(rotation, new Vector3(0, 1, 0));

            m *= Matrix.translate(new Vector3(0, 0, -2));
            foreach (Vector3 v in vertices)
            {
                Vector3 p = m * v;

                p.x = Width / 2 + p.x / p.z * Width / 2;
                p.y = Height / 2 + p.y / p.z * Height / 2;

                g.DrawRectangle(pen, p.x - 5, p.y - 5, 10, 10);
            }
        }
    }
}
