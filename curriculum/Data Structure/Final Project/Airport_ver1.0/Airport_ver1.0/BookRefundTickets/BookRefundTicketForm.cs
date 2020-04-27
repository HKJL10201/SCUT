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

namespace Airport_ver1._0.BookRefundTickets
{
    public partial class BookRefundTicketForm : Form
    {
        BookRefundTicketsForm bookRefundTicketsForm;
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

        public BookRefundTicketForm()
        {
            //默认构造函数方便调试，直接在主程序中启动
            InitializeComponent();
            StartPosition = FormStartPosition.CenterScreen;
        }

        public BookRefundTicketForm(BookRefundTicketsForm bookRefundTicketsForm, string mode, Ticket ticket = null)
        {
            InitializeComponent();
            StartPosition = FormStartPosition.CenterScreen;

            this.bookRefundTicketsForm = bookRefundTicketsForm;
            this.mode = mode;
            this.ticket = ticket;
            oldticket = ticket;

            if (mode == "Book" || mode == "Refund")
            {
                LoadDataFromTicket();
                numericUpDown1.Minimum = 0;
                numericUpDown1.Maximum = int.Parse(textBox_Allowance.Text);
            }

        }

        private void button_Confirm_Click(object sender, EventArgs e)
        {
            LoadData();

            if (mode == "Book")
            {

                int ChangeNumber = (int)numericUpDown1.Value;
                if (ChangeNumber <= 0 || ChangeNumber > Convert.ToInt32(Allowance))//注释掉这行运行订购候补
                {
                    if (bookRefundTicketsForm.mainForm.DebugMode && ChangeNumber < 0)
                    {
                        ;//DebugMode下可以修改为负数
                    }
                    else
                    {
                        toolStripStatusLabel1.Text = "无效的数值，请修改！";
                        return;
                    }
                }

                //登记候补
                /*if(ChangeNumber > Convert.ToInt32(Allowance))
                {
                    UsersTicketsIO utio = new UsersTicketsIO(bookRefundTicketsForm.mainForm.user.Username);
                    utio.Standby(FlightNumber);
                    return;
                }*/

                Ticket newticket = new Ticket(FlightNumber, Origin, Terminal, Date, BeginTime,
                     EndTime, Price, Capacity, (int.Parse(Allowance) - ChangeNumber).ToString(), AircraftType);

                string bookReturn = bookRefundTicketsForm.mainForm.ticketsIO.Update(ticket, newticket);

                if (bookReturn == "Update successfully")
                {
                    //前面是从机票列表扣除

                    toolStripStatusLabel1.Text = "Book successfully!";

                    //插入用户购票列表
                    UsersTicketsIO utio = new UsersTicketsIO(bookRefundTicketsForm.mainForm.user.Username);
                    Ticket myticket = new Ticket(FlightNumber, Origin, Terminal, Date, BeginTime,
                     EndTime, Price, Capacity, (ChangeNumber).ToString(), AircraftType);
                    utio.Append(myticket);

                    /**/
                    
                    /**/


                    //当此行注释掉，则只有点击关闭才刷新
                    bookRefundTicketsForm.RefreshForm();
                    Close();

                    return;
                }
                else
                {
                    toolStripStatusLabel1.Text = "遇到了未知错误，请洗脸。";
                    return;
                }
            }
            else if (mode == "Refund")
            {
                int ChangeNumber = (int)numericUpDown1.Value;
                int curAmount = int.Parse(ticket.Allowance);

                //List<Ticket> tmp= bookRefundTicketsForm.mainForm.ticketsIO.Search(Origin, Terminal, Date);

                int target = Sort_Search.Binary_search_FlightNumber(bookRefundTicketsForm.mainForm.ticketsIO.L, bookRefundTicketsForm.mainForm.ticketsIO.L.Count, FlightNumber);

                if (target == bookRefundTicketsForm.mainForm.ticketsIO.L.Count)
                {
                    toolStripStatusLabel1.Text = "要退的票不在上列表，遇到了错误的数据。";
                    return;
                }

                /*if (tmp.Count == 0)
                {
                    toolStripStatusLabel1.Text = "要退的票不在上列表，遇到了错误的数据。";
                    return;
                }*/

                //Ticket oldticket = tmp[0];
                Ticket oldticket = bookRefundTicketsForm.mainForm.ticketsIO.L[target];

                /*int i = 1;
                while (oldticket.FlightNumber != ticket.FlightNumber)
                    oldticket = tmp[i++];*/

                //Ticket newticket = oldticket;
                Ticket newticket = new Ticket();
                newticket.Copy(oldticket);

                newticket.Allowance = (int.Parse(oldticket.Allowance) + ChangeNumber).ToString();

                toolStripStatusLabel1.Text = newticket.Allowance;
                Console.WriteLine("---------------------\n"+newticket.Allowance);

                string bookReturn = bookRefundTicketsForm.mainForm.ticketsIO.Update(oldticket, newticket);

                if (bookReturn == "Update successfully")
                {
                    //前面是往机票列表增加

                    toolStripStatusLabel1.Text = "Refund successfully!";


                    UsersTicketsIO utio = new UsersTicketsIO(bookRefundTicketsForm.mainForm.user.Username);

                    int newAllowance = curAmount - ChangeNumber;

                    //toolStripStatusLabel1.Text = newAllowance.ToString();

                    if (newAllowance == 0)
                    {
                        //当全部退票时删除用户购票列表
                        Ticket myticket = new Ticket(FlightNumber, Origin, Terminal, Date, BeginTime,
                        EndTime, Price, Capacity, Allowance, AircraftType);

                        utio.Delete(myticket);

                    }
                    else
                    {
                        Ticket oldticket2 = new Ticket(FlightNumber, Origin, Terminal, Date, BeginTime,
                        EndTime, Price, Capacity, curAmount.ToString(), AircraftType);

                        Ticket myticket = new Ticket(FlightNumber, Origin, Terminal, Date, BeginTime,
                        EndTime, Price, Capacity, newAllowance.ToString(), AircraftType);

                        utio.Update(oldticket2, myticket);
                    }
                    //当此行注释掉，则只有点击关闭才刷新
                    bookRefundTicketsForm.RefreshForm();
                    Close();

                    return;
                }
                else
                {
                    toolStripStatusLabel1.Text = "遇到了未知错误，请洗脸。";
                    return;
                }
            }
        }

        private void ManageTicketForm_Load(object sender, EventArgs e)
        {

        }

        private void button_Close_Click(object sender, EventArgs e)
        {
            bookRefundTicketsForm.RefreshForm();
            Close();
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

            numericUpDown1.Minimum = -1023;
            numericUpDown1.Maximum = 1023;
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

        private void dateTimePicker_ValueChanged(object sender, EventArgs e)
        {

        }
    }
}
