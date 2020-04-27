using System;
using System.Collections.Generic;
using System.Windows.Forms;

using Airport_ver1._0.FileIO;
using Airport_ver1._0.Tickets;

namespace Airport_ver1._0.BookRefundTickets
{
    public partial class BookRefundTicketsForm : Form
    {
        public MainForm mainForm;

        public BookRefundTicketsForm(MainForm mainForm)
        {
            InitializeComponent();
            this.mainForm = mainForm;
        }

        private void BookRefundTicketsForm_Load(object sender, EventArgs e)
        {
            /*List<Ticket> tickets = TicketsIO.ReadAll();
            foreach (Ticket t in tickets)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_AllTickets.Items.Add(listViewItem);
            }*/
            foreach (Ticket t in mainForm.ticketsIO.L)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_AllTickets.Items.Add(listViewItem);
            }

            UsersTicketsIO usersTicketsIO = new UsersTicketsIO(mainForm.user.Username);
            List<Ticket> tickets2= usersTicketsIO.ReadAll();

            foreach (Ticket t in tickets2)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_MyTickets.Items.Add(listViewItem);
            }
            return;
        }

        //刷新窗口
        public void RefreshForm()
        {
            Console.WriteLine("BookRefundTickets RefreshForm.");
            //先清空原有的所有元组
            listView_AllTickets.Items.Clear();

            //刷新机票列表

            /*List<Ticket> tickets = TicketsIO.ReadAll();
            foreach (Ticket t in tickets)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_AllTickets.Items.Add(listViewItem);
            }*/
            foreach (Ticket t in mainForm.ticketsIO.L)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_AllTickets.Items.Add(listViewItem);
            }


            listView_MyTickets.Items.Clear();

            UsersTicketsIO usersTicketsIO = new UsersTicketsIO(mainForm.user.Username);
            List<Ticket> tickets2 = usersTicketsIO.ReadAll();

            foreach (Ticket t in tickets2)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_MyTickets.Items.Add(listViewItem);
            }

        }

        private void listView_AllTickets_SelectedIndexChanged(object sender, EventArgs e)
        {
            string toolStripStatusLabelText;
            ListView.SelectedIndexCollection collection = listView_AllTickets.SelectedIndices;
            if (collection.Count != 0)
            {
                toolStripStatusLabelText = "AllTickets Selected tickets:  ";
                for (int i = 0; i < collection.Count; i++)
                {
                    string FlightNumber = listView_AllTickets.Items[collection[i]].SubItems[0].Text.ToString();
                    toolStripStatusLabelText += "\"" + FlightNumber + "\"";
                    if (i != collection.Count - 1)
                    {
                        //当这个元素不是最后一个元素
                        toolStripStatusLabelText += ", ";
                    }
                }
                toolStripStatusLabelText += ". ";
            }
            else
            {
                toolStripStatusLabelText = "No tickets selected. ";
            }
            toolStripStatusLabel1.Text = toolStripStatusLabelText;
        }

        private void listView_MyTickets_SelectedIndexChanged(object sender, EventArgs e)
        {
            string toolStripStatusLabelText;
            ListView.SelectedIndexCollection collection = listView_MyTickets.SelectedIndices;
            if (collection.Count != 0)
            {
                toolStripStatusLabelText = "MyTickets Selected tickets:  ";
                for (int i = 0; i < collection.Count; i++)
                {
                    string FlightNumber = listView_MyTickets.Items[collection[i]].SubItems[0].Text.ToString();
                    toolStripStatusLabelText += "\"" + FlightNumber + "\"";
                    if (i != collection.Count - 1)
                    {
                        //当这个元素不是最后一个元素
                        toolStripStatusLabelText += ", ";
                    }
                }
                toolStripStatusLabelText += ". ";
            }
            else
            {
                toolStripStatusLabelText = "No tickets selected. ";
            }
            toolStripStatusLabel1.Text = toolStripStatusLabelText;
        }

        private void button_Book_Click(object sender, EventArgs e)
        {
            ListView.SelectedIndexCollection collection = listView_AllTickets.SelectedIndices;
            if (collection.Count == 1)
            {
                Ticket ticket = new Ticket();
                ticket.FromListViewItem(listView_AllTickets.Items[collection[0]]);
                
                Form bookRefundTicketForm1 = new BookRefundTicketForm(this, "Book", ticket);
                bookRefundTicketForm1.ShowDialog(this);
            }
            else if (collection.Count == 0)
            {
                toolStripStatusLabel1.Text = "No tickets selected. Cannot book. ";
                return;
            }
            else
            {
                toolStripStatusLabel1.Text = "Selected too more tickets. Cannot book. ";
                return;
            }
        }

        private void button_Refund_Click(object sender, EventArgs e)
        {
            ListView.SelectedIndexCollection collection = listView_MyTickets.SelectedIndices;
            if (collection.Count == 1)
            {
                Ticket ticket = new Ticket();
                ticket.FromListViewItem(listView_MyTickets.Items[collection[0]]);

                Form bookRefundTicketForm1 = new BookRefundTicketForm(this, "Refund", ticket);
                bookRefundTicketForm1.ShowDialog(this);
            }
            else if (collection.Count == 0)
            {
                toolStripStatusLabel1.Text = "No tickets selected. Cannot refund. ";
                return;
            }
            else
            {
                toolStripStatusLabel1.Text = "Selected too more tickets. Cannot refund. ";
                return;
            }
        }

        private void button_SelectAll_Click(object sender, EventArgs e)
        {
            
            string Origin = textBox_input_origin.Text;
            string Terminal = textBox_input_terminal.Text;
            string Date = dateTimePicker1.Text;

            if (Origin == "" || Terminal == "")
            {
                listView_AllTickets.Items.Clear();

                //刷新机票列表

                foreach (Ticket t in this.mainForm.ticketsIO.L)
                {
                    ListViewItem listViewItem = t.ToListViewItem();
                    listView_AllTickets.Items.Add(listViewItem);
                }

                return;
            }

            List<Ticket> tickets = this.mainForm.ticketsIO.Search(Origin, Terminal, Date);

            listView_AllTickets.Items.Clear();

            //刷新机票列表

            foreach (Ticket t in tickets)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_AllTickets.Items.Add(listViewItem);
            }

            return;
        }

        private void textBox_input_origin_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
