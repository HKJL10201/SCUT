using System;
using System.Windows.Forms;

using Airport_ver1._0.BookRefundTickets;
using Airport_ver1._0.ManageTickets;
using Airport_ver1._0.Login;
using Airport_ver1._0.Users;
using Airport_ver1._0.Register;

using Airport_ver1._0.FileIO;

namespace Airport_ver1._0
{
    public partial class MainForm : Form
    {
        //公有的 调试模式：用于触发自动登录以及自动填充
        public bool DebugMode = true;

        public User user = new User();
        bool Logined = false;

        public TicketsIO ticketsIO;//lee****************

        public MainForm()
        {
            InitializeComponent();
            StartPosition = FormStartPosition.CenterScreen;

            ticketsIO = new TicketsIO();//lee*************************

            listView_History.Columns.Add("History");
            if (DebugMode)
            {
                LoginSucessfully("Administrator");
            }
        }


        private void button_Login_Click(object sender, EventArgs e)
        {
            if (Logined)
            {
                toolStripStatusLabel.Text = "需求外的功能，暂未被实现。";
            }
            else
            {
                Form loginForm = new LoginForm(this);
                loginForm.ShowDialog(this);
            }
        }

        private void button_Regitser_Click(object sender, EventArgs e)
        {
            if (Logined)
            {
                Logout();
            }
            else
            {
                Form registerForm = new RegisterForm(this);
                registerForm.ShowDialog(this);
            }
        }

        private void button_Test_Click(object sender, EventArgs e)
        {
            ListViewItem listViewItem = new ListViewItem();
            listViewItem.Text = "!";
            listView_History.Items.Add(listViewItem);
        }

        public void UpdateStatus(string NewStatus)
        {
            toolStripStatusLabel.Text = NewStatus;
        }

        public void LoginSucessfully(string Username)
        {
            Login(Username);
            toolStripStatusLabel.Text = "Login sucessfully, welcome " + Username+".";
        }

        public void RegisterSucessfully(string Username)
        {
            Login(Username);
            toolStripStatusLabel.Text = "Register sucessfully, welcome " + Username+".";
        }

        void Login(string Username)
        {
            user.Username = Username;
            if(user.Username== "Administrator")
            {
                AdministratorLogin();
            }

            Logined = true;
            label_Username.Text = "Username: " + Username;
            button_Login.Text = "Manage User";
            button_Register.Text = "Logout";
        }

        void Logout()
        {
            if (user.Username == "Administrator")
            {
                AdministratorLogout();
            }

            user.Username = null;

            Logined = false;
            label_Username.Text = "Please login or register";
            button_Login.Text = "Login";
            button_Register.Text = "Register";

            toolStripStatusLabel.Text = "Logout sucessfully.";
        }

        void AdministratorLogin()
        {
            user.Level = "Administrator";
            button_ChangeLevel.Visible = true;
        }

        void AdministratorLogout()
        {
            user.Level = "User";
            button_ChangeLevel.Visible = false;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        private void ManageTickets_Click(object sender, EventArgs e)
        {
            if (user.Level == "Administrator")
            {
                Form manageTicketsForm = new ManageTicketsForm(this);
                manageTicketsForm.ShowDialog(this);
            }
            else
            {
                Form bookRefundTicketsForm = new BookRefundTicketsForm(this);
                bookRefundTicketsForm.ShowDialog(this);
            }
        }

        private void button_ChangeLevel_Click(object sender, EventArgs e)
        {
            if (user.Level != "Administrator")
            {
                user.Level = "Administrator";
            }
            else
            {
                user.Level = "User";
            }

            toolStripStatusLabel.Text = "User level change to \"" + user.Level + "\"";
        }
    }
}
