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
    public partial class DeleteTicketForm : Form
    {
        ManageTicketsForm manageTicketsForm;
        List<Ticket> tickets;

        //删除单个元素的重载，已废弃
        /*
        
        //一起被废弃的成员函数
        Ticket ticket;
        public DeleteTicketForm(ManageTicketsForm manageTicketsForm, Ticket ticket)
        {
            InitializeComponent();
            this.manageTicketsForm = manageTicketsForm;
            this.ticket = ticket;
        }*/

        //删除多个元素的重载
        public DeleteTicketForm(ManageTicketsForm manageTicketsForm, List<Ticket> tickets)
        {
            InitializeComponent();
            this.manageTicketsForm = manageTicketsForm;
            this.tickets = tickets;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (checkBox.Checked)
            {
                manageTicketsForm.showDeleteTicketForm = false;
                Console.WriteLine(manageTicketsForm.showDeleteTicketForm);
            }

            foreach (Ticket ticket in tickets)
            {
                //低效的实现方法，时间复杂度与被删除元素的数量相关，时间成倍增加
                //复杂度O(nm)
                //若原本序列有序则应该像归并排序一样实现，复杂度应该是O(n+m)
                //TicketsIO.Delete(ticket);
                manageTicketsForm.mainForm.ticketsIO.Delete(ticket);
            }

            manageTicketsForm.RefreshForm();

            Close();

            return;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (checkBox.Checked)
            {
                manageTicketsForm.showDeleteTicketForm = false;
                Console.WriteLine(manageTicketsForm.showDeleteTicketForm);
            }
            
            Close();
        }
    }
}
