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
namespace gui
{
    public partial class Form1 : Form
    {
        [DllImport("C:/Users/Kraychik/Documents/Visual Studio 2010/Projects/calcparam/Release/calcparam.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "run")]
        public static extern void run();
        //[DllImport("C:/Users/Kraychik/Documents/Visual Studio 2010/Projects/calcparam/Debug/calcparam.dll", EntryPoint = "run", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        //extern static void run([MarshalAs(UnmanagedType.AnsiBStr)] out String str);
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label1.Text = openFileDialog1.FileName;
            run();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }
    }
}
