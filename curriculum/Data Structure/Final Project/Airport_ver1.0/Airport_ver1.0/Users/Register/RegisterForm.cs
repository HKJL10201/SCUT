using System;

using System.Windows.Forms;

namespace Airport_ver1._0.Register
{
    partial class RegisterForm : Form
    {
        MainForm mainForm;

        public RegisterForm(MainForm mainForm)
        {
            InitializeComponent();
            this.mainForm = mainForm;
        }

        private void button_Register_Click(object sender, EventArgs e)
        {
            string InputUsername = textBox_Username.Text;
            string InputPassword = textBox_Password.Text;

            if (InputUsername == "" || InputPassword == "")
            {
                toolStripStatusLabel.Text = "Username and Password cannot be null!";
                return;
            }
            else if (InputUsername == "Administrator")
            {
                toolStripStatusLabel.Text = "Username cannot be \"Administrator\"!";
                return;
            }//这里可能多余了，因为Administrator已经有了，不可能再注册，可能不需要特判
            else
            {
                RegisterProgram registerProgram = new RegisterProgram(InputUsername, InputPassword);
                string Status = registerProgram.Register();
                toolStripStatusLabel.Text = Status;
                if (Status == "Register successfully")
                {
                    mainForm.RegisterSucessfully(InputUsername);
                    Close();
                }
                return;
            }
        }

        private void button_Close_Click(object sender, EventArgs e)
        {
            Close();
        }

        
    }
}
