using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Airport_ver1._0.FileIO;
using Airport_ver1._0.Tickets;
using Airport_ver1._0.ManageTickets;

namespace Airport_ver1._0.ManageTickets
{
    public partial class ManageTicketForm : Form
    {
        ManageTicketsForm manageTicketsForm;
        string mode;
        Ticket ticket;
        Ticket oldticket;

        //重写默认值
        string FlightNumber;
        string Origin;
        string Terminal;
        string Date;
        string BeginTime;
        string EndTime;
        string Price;
        string Capacity;
        string Allowance;
        string AircraftType;

        public ManageTicketForm()
        {
            //默认构造函数方便调试，直接在主程序中启动
            InitializeComponent();
            StartPosition = FormStartPosition.CenterScreen;
        }

        public ManageTicketForm(ManageTicketsForm manageTicketsForm, string mode, Ticket ticket = null)
        {
            InitializeComponent();
            StartPosition = FormStartPosition.CenterScreen;

            this.manageTicketsForm = manageTicketsForm;
            this.mode = mode;
            this.ticket = ticket;
            oldticket = ticket;


            if (mode == "Add")
            {
                if (manageTicketsForm.mainForm.DebugMode)
                {
                    //处于调试模式下自动填充
                    LoadTestData();
                }
            }

            if (mode == "Update")
            {
                LoadDataFromTicket();
                textBox_FlightNumber.Enabled = false;
            }
        }

        private void button_Confirm_Click(object sender, EventArgs e)
        {
            if (mode == "Add")
            {
                LoadData();

                if (FlightNumber == "" || Origin == "" || Terminal == "" || Date == "" || BeginTime == "" ||
                     EndTime == "" || Price == "" || Capacity == "" || Allowance == "" || AircraftType == "")
                {
                    toolStripStatusLabel1.Text = "Cannot be null!";
                    return;
                }

                ticket = new Ticket(FlightNumber, Origin, Terminal, Date, BeginTime,
                     EndTime, Price, Capacity, Allowance, AircraftType);

                //string insertReturn=TicketsIO.Insert(ticket);
                string insertReturn = manageTicketsForm.mainForm.ticketsIO.Insert(ticket);

                if (insertReturn == "Insert successfully")
                {
                    toolStripStatusLabel1.Text = "Add successfully!";


                    /*//调试中不需要清空文本框
                    if (!manageTicketsForm.mainForm.DebugMode)
                    {
                        ClearData();
                    }*/

                    ClearData();

                    //当此行注释掉，则只有点击关闭才刷新
                    manageTicketsForm.RefreshForm();
                    Close();

                    return;
                }
                else
                {
                    toolStripStatusLabel1.Text = insertReturn;
                    return;
                }
            }
            else if (mode == "Update")
            {
                LoadData();

                if (FlightNumber == "" || Origin == "" || Terminal == "" || Date == "" || BeginTime == "" ||
                     EndTime == "" || Price == "" || Capacity == "" || Allowance == "" || AircraftType == "")
                {
                    toolStripStatusLabel1.Text = "Cannot be null!";
                    return;
                }

                ticket = new Ticket(FlightNumber, Origin, Terminal, Date, BeginTime,
                     EndTime, Price, Capacity, Allowance, AircraftType);
                
                manageTicketsForm.mainForm.ticketsIO.Update(oldticket, ticket);
                toolStripStatusLabel1.Text = "Update successfully!";


                /*//调试中不需要清空文本框
                if (!manageTicketsForm.mainForm.DebugMode)
                {
                    ClearData();
                }*/

                ClearData();

                //当此行注释掉，则只有点击关闭才刷新
                manageTicketsForm.RefreshForm();
                Close();

                return;
            }
        }

        private void ManageTicketForm_Load(object sender, EventArgs e)
        {

        }

        private void button_Close_Click(object sender, EventArgs e)
        {
            manageTicketsForm.RefreshForm();
            Close();
        }


        void LoadTestData()
        {
            textBox_FlightNumber.Text = "TEST_FN001";
            textBox_Origin.Text = "Guangzhou";
            textBox_Terminal.Text = "Shenzhen";
            dateTimePicker.Text = "2019/1/1";
            textBox_BeginTime.Text = "0:00";
            textBox_EndTime.Text = "12:00";
            textBox_Price.Text = "32";
            textBox_Capacity.Text = "32";
            textBox_Allowance.Text = "32";
            textBox_AircraftType.Text = "TEST_AircraftType";
        }

        void LoadData()
        {
            FlightNumber = textBox_FlightNumber.Text;
            Origin = textBox_Origin.Text;
            Terminal = textBox_Terminal.Text;
            Date = dateTimePicker.Text;
            BeginTime = textBox_BeginTime.Text;
            EndTime = textBox_EndTime.Text;
            Price = textBox_Price.Text;
            Capacity = textBox_Capacity.Text;
            Allowance = textBox_Allowance.Text;
            AircraftType = textBox_AircraftType.Text;
        }

        void LoadDataFromTicket()
        {
            textBox_FlightNumber.Text = ticket.FlightNumber;
            textBox_Origin.Text = ticket.Origin;
            textBox_Terminal.Text = ticket.Terminal;
            dateTimePicker.Text = ticket.Date;
            textBox_BeginTime.Text = ticket.BeginTime;
            textBox_EndTime.Text = ticket.EndTime;
            textBox_Price.Text = ticket.Price;
            textBox_Capacity.Text = ticket.Capacity;
            textBox_Allowance.Text = ticket.Allowance;
            textBox_AircraftType.Text = ticket.Aircraft_Type;
        }

        void ClearData()
        {
            textBox_FlightNumber.Text = "";
            textBox_Origin.Text = "";
            textBox_Terminal.Text = "";
            dateTimePicker.Text = "";
            textBox_BeginTime.Text = "";
            textBox_EndTime.Text = "";
            textBox_Price.Text = "";
            textBox_Capacity.Text = "";
            textBox_Allowance.Text = "";
            textBox_AircraftType.Text = "";
        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dateTimePicker_ValueChanged(object sender, EventArgs e)
        {

        }
    }
}
