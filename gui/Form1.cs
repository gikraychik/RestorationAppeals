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
    public partial class Form1 : Form
    {
        [DllImport("C:/Users/Kraychik/Documents/Visual Studio 2010/Projects/calcparam/Release/calcparam.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "run")]
        public static extern void run(string path, ref params_time pt);
        [DllImport("C:/Users/Kraychik/D ocuments/Visual Studio 2010/Projects/calcparam/Release/calcparam.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "testing")]
        public static extern void testing(ref my_test t);

        public Form1()
        {
            InitializeComponent();
        }

        public void my_handler()
        {
            //progressBar1.Value += 20;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            //label1.Text = browse_dialog.FileName;
            params_time pt = new params_time();
            //status progress = new status(0);
            label1.Text = "Processing...";
            this.Enabled = false;
            run(browse_dialog.FileName, ref pt);
            this.Enabled = true;
            label1.Text = "Done.";
            unsafe
            {
                textBox2.Text = (0.3).ToString();
                textBox3.Text = (0.8).ToString();
                textBox4.Text = pt.lambda[0].ToString();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            browse_dialog.ShowDialog();
            textBox1.Text = browse_dialog.FileName;
            //status st = new status(3);
            //st.my_event += new my_delegate(my_handler);
            //st.change_value(13);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
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
    public class A
    {
        public int value { get; set; }
        public event EventHandler ValueChanged;
    }
    public delegate void my_delegate();
    [StructLayout(LayoutKind.Sequential)]
    public class status
    {
        public status(int v)
        {
            this.value = v;
        }
        int value;
        public event my_delegate my_event;
        public void change_value(int new_value)
        {
            this.value = new_value;
            if (my_event != null)
                my_event();
        }
    }
}
