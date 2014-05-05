/*using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Text;

namespace gui
{
    [StructLayout(LayoutKind.Sequential)]
    unsafe public struct params_time
    {
        public int* position;
        public double* lambda;
        public int n;
    }
    [StructLayout(LayoutKind.Sequential)]
    unsafe public struct my_test
    {
        public int* arr;
        public int n;
        //public int x;
        //public byte y;
    }
    public partial class Form1 : Form
    {
        [DllImport("C:/Users/Kraychik/Documents/Visual Studio 2010/Projects/calcparam/Release/calcparam.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "run")]
        public static extern void run(string path, ref params_time pt);
        [DllImport("C:/Users/Kraychik/Documents/Visual Studio 2010/Projects/calcparam/Release/calcparam.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "testing")]
        public static extern void testing(ref my_test t);
        
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label1.Text = browse_dialog.FileName;
            params_time pt = new params_time();
            run(browse_dialog.FileName, ref pt);
            unsafe {
                label2.Text = pt.lambda[0].ToString();
                label1.Text = pt.position[0].ToString();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            browse_dialog.ShowDialog();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
