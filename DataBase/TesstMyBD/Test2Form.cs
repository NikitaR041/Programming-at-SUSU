using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TesstMyBD
{
    public partial class Test2Form : Form
    {
        private string connestionString;
        public Test2Form(string ds)
        {
            InitializeComponent();
            connestionString = ds;
        }

        private void Test2Form_Load(object sender, EventArgs e)
        {

        }
    }
}
