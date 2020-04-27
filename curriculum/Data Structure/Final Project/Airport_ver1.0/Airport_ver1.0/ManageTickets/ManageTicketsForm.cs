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

namespace Airport_ver1._0.ManageTickets
{
    public partial class ManageTicketsForm : Form
    {
        public MainForm mainForm;

        public bool showDeleteTicketForm = true;

        public ManageTicketsForm(MainForm mainForm)
        {
            InitializeComponent();
            this.mainForm = mainForm;
        }

        private void ManageTicketsForm_Load(object sender, EventArgs e)
        {
            /*List<Ticket> tickets = TicketsIO.ReadAll();
            foreach (Ticket t in tickets)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_Tickets.Items.Add(listViewItem);
            }*/

            foreach (Ticket t in mainForm.ticketsIO.L)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_Tickets.Items.Add(listViewItem);
            }

            return;
        }

        private void listView_Tickets_SelectedIndexChanged(object sender, EventArgs e)
        {
            string toolStripStatusLabelText;
            ListView.SelectedIndexCollection collection = listView_Tickets.SelectedIndices;
            if (collection.Count != 0)
            {
                toolStripStatusLabelText = "Selected tickets:  ";
                for(int i=0;i< collection.Count;i++)
                {
                    string FlightNumber = listView_Tickets.Items[collection[i]].SubItems[0].Text.ToString();
                    toolStripStatusLabelText += "\""+FlightNumber+"\"";
                    if(i!= collection.Count - 1)
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

        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button_Add_Click(object sender, EventArgs e)
        {
            Form manageTicketForm = new ManageTicketForm(this,"Add");
            manageTicketForm.ShowDialog(this);
        }

        private void button_Update_Click(object sender, EventArgs e)
        {
            ListView.SelectedIndexCollection collection = listView_Tickets.SelectedIndices;
            if (collection.Count ==1)
            {
                Ticket ticket=new Ticket();
                ticket.FromListViewItem(listView_Tickets.Items[collection[0]]);

                Console.WriteLine("update ticket= "+ticket.ToString());
                
                Form manageTicketForm = new ManageTicketForm(this, "Update",ticket);
                manageTicketForm.ShowDialog(this);
                
            }
            else if(collection.Count == 0)
            {
                toolStripStatusLabel1.Text = "No tickets selected. Cannot update. ";
                return;
            }
            else
            {
                toolStripStatusLabel1.Text = "Selected too more tickets. Cannot update. ";
                return;
            }
        }

        private void button_Delete_Click(object sender, EventArgs e)
        {
            ListView.SelectedIndexCollection collection = listView_Tickets.SelectedIndices;
            if (collection.Count != 0)
            {
                List<Ticket> tickets=new List<Ticket>();
                for (int i = 0; i < collection.Count; i++)
                {
                    //只识别主码的实现
                    //string FlightNumber = listView_Tickets.Items[collection[i]].SubItems[0].Text.ToString();
                    //tickets.Add(new Ticket(FlightNumber));

                    //整体识别的实现
                    Ticket ticket = new Ticket();
                    ticket.FromListViewItem(listView_Tickets.Items[collection[i]]);
                    Console.WriteLine("!!!"+ticket.MyToString());
                    tickets.Add(ticket);
                }

                if (showDeleteTicketForm)
                {
                    Form deleteTicketForm = new DeleteTicketForm(this, tickets);
                    deleteTicketForm.ShowDialog(this);
                }
                else
                {
                    foreach (Ticket ticket in tickets)
                    {
                        Console.WriteLine(ticket.MyToString());
                        mainForm.ticketsIO.Delete(ticket);
                    }
                    RefreshForm();
                }
            }
            else
            {
                toolStripStatusLabel1.Text = "No tickets selected. Cannot delete. ";
                return;
            }
        }

        //刷新窗口
        public void RefreshForm()
        {
            Console.WriteLine("ManageTickets RefreshForm.");
            //先清空原有的所有元组
            listView_Tickets.Items.Clear();

            //刷新机票列表
            /*List<Ticket> tickets = TicketsIO.ReadAll();
            foreach (Ticket t in tickets)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_Tickets.Items.Add(listViewItem);
            }*/

            foreach (Ticket t in mainForm.ticketsIO.L)
            {
                ListViewItem listViewItem = t.ToListViewItem();
                listView_Tickets.Items.Add(listViewItem);
            }

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void statusStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void button_Select_Click(object sender, EventArgs e)
        {

        }
    }
}
