using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Airport_ver1._0.Login;

namespace Airport_ver1._0.Login
{
    public partial class LoginForm : Form
    {
        MainForm mainForm;

        public LoginForm(MainForm mainForm)
        {
            InitializeComponent();
            this.mainForm=mainForm;
        }

        private void button_Login_Click(object sender, EventArgs e)
        {
            string InputUsername = textBox_Username.Text;
            string InputPassword = textBox_Password.Text;

            if (InputUsername == "" || InputPassword == "")
            {
                toolStripStatusLabel.Text = "Username and Password cannot be null!";
                return;
            }
            else if(InputUsername == "Administrator" && InputPassword == "Administrator")
            {
                toolStripStatusLabel.Text = "Administrator Login successfully";
                mainForm.LoginSucessfully(InputUsername);
                Close();
                return;
            }
            else
            {
                LoginProgram loginProgram = new LoginProgram(InputUsername, InputPassword);
                string Status = loginProgram.Login();
                toolStripStatusLabel.Text = Status;
                if(Status== "Login successfully")
                {
                    mainForm.LoginSucessfully(InputUsername);
                    Close();
                }
                return;
            }
        }

        private void button_Close_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void LoginForm_Load(object sender, EventArgs e)
        {

        }

    }
}
