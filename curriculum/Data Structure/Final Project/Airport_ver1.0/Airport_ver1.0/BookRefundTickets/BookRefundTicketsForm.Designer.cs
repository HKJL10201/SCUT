namespace Airport_ver1._0.BookRefundTickets
{
    public partial class BookRefundTicketsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button_Refund = new System.Windows.Forms.Button();
            this.button_Book = new System.Windows.Forms.Button();
            this.button_SelectAll = new System.Windows.Forms.Button();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.AircraftType = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Allowance = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Capacity = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Price = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.EndTime = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.BeginTime = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Date = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Terminal = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Origin = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.FlightNumber = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.listView_AllTickets = new System.Windows.Forms.ListView();
            this.listView_MyTickets = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader7 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader8 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader9 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader10 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.button_SelectMy = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_input_origin = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_input_terminal = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_Refund
            // 
            this.button_Refund.Location = new System.Drawing.Point(811, 597);
            this.button_Refund.Name = "button_Refund";
            this.button_Refund.Size = new System.Drawing.Size(75, 23);
            this.button_Refund.TabIndex = 17;
            this.button_Refund.Text = "Refund";
            this.button_Refund.UseVisualStyleBackColor = true;
            this.button_Refund.Click += new System.EventHandler(this.button_Refund_Click);
            // 
            // button_Book
            // 
            this.button_Book.Location = new System.Drawing.Point(811, 260);
            this.button_Book.Name = "button_Book";
            this.button_Book.Size = new System.Drawing.Size(75, 23);
            this.button_Book.TabIndex = 15;
            this.button_Book.Text = "Book";
            this.button_Book.UseVisualStyleBackColor = true;
            this.button_Book.Click += new System.EventHandler(this.button_Book_Click);
            // 
            // button_SelectAll
            // 
            this.button_SelectAll.Location = new System.Drawing.Point(730, 260);
            this.button_SelectAll.Name = "button_SelectAll";
            this.button_SelectAll.Size = new System.Drawing.Size(75, 23);
            this.button_SelectAll.TabIndex = 14;
            this.button_SelectAll.Text = "Select";
            this.button_SelectAll.UseVisualStyleBackColor = true;
            this.button_SelectAll.Click += new System.EventHandler(this.button_SelectAll_Click);
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(131, 17);
            this.toolStripStatusLabel1.Text = "toolStripStatusLabel1";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 623);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(898, 22);
            this.statusStrip1.TabIndex = 13;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // AircraftType
            // 
            this.AircraftType.Text = "AircraftType";
            this.AircraftType.Width = 120;
            // 
            // Allowance
            // 
            this.Allowance.Text = "Allowance";
            // 
            // Capacity
            // 
            this.Capacity.Text = "Capacity";
            // 
            // Price
            // 
            this.Price.Text = "Price";
            this.Price.Width = 70;
            // 
            // EndTime
            // 
            this.EndTime.Text = "EndTime";
            this.EndTime.Width = 70;
            // 
            // BeginTime
            // 
            this.BeginTime.Text = "BeginTime";
            this.BeginTime.Width = 70;
            // 
            // Date
            // 
            this.Date.Text = "Date";
            this.Date.Width = 120;
            // 
            // Terminal
            // 
            this.Terminal.Text = "Terminal";
            this.Terminal.Width = 100;
            // 
            // Origin
            // 
            this.Origin.Text = "Origin";
            this.Origin.Width = 100;
            // 
            // FlightNumber
            // 
            this.FlightNumber.Text = "FlightNumber";
            this.FlightNumber.Width = 90;
            // 
            // listView_AllTickets
            // 
            this.listView_AllTickets.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.FlightNumber,
            this.Origin,
            this.Terminal,
            this.Date,
            this.BeginTime,
            this.EndTime,
            this.Price,
            this.Capacity,
            this.Allowance,
            this.AircraftType});
            this.listView_AllTickets.FullRowSelect = true;
            this.listView_AllTickets.GridLines = true;
            this.listView_AllTickets.Location = new System.Drawing.Point(12, 32);
            this.listView_AllTickets.Name = "listView_AllTickets";
            this.listView_AllTickets.Size = new System.Drawing.Size(874, 222);
            this.listView_AllTickets.TabIndex = 11;
            this.listView_AllTickets.UseCompatibleStateImageBehavior = false;
            this.listView_AllTickets.View = System.Windows.Forms.View.Details;
            this.listView_AllTickets.SelectedIndexChanged += new System.EventHandler(this.listView_AllTickets_SelectedIndexChanged);
            // 
            // listView_MyTickets
            // 
            this.listView_MyTickets.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6,
            this.columnHeader7,
            this.columnHeader8,
            this.columnHeader9,
            this.columnHeader10});
            this.listView_MyTickets.FullRowSelect = true;
            this.listView_MyTickets.GridLines = true;
            this.listView_MyTickets.Location = new System.Drawing.Point(12, 404);
            this.listView_MyTickets.Name = "listView_MyTickets";
            this.listView_MyTickets.Size = new System.Drawing.Size(874, 187);
            this.listView_MyTickets.TabIndex = 18;
            this.listView_MyTickets.UseCompatibleStateImageBehavior = false;
            this.listView_MyTickets.View = System.Windows.Forms.View.Details;
            this.listView_MyTickets.SelectedIndexChanged += new System.EventHandler(this.listView_MyTickets_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "FlightNumber";
            this.columnHeader1.Width = 90;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Origin";
            this.columnHeader2.Width = 100;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Terminal";
            this.columnHeader3.Width = 100;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Date";
            this.columnHeader4.Width = 120;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Text = "BeginTime";
            this.columnHeader5.Width = 70;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Text = "EndTime";
            this.columnHeader6.Width = 70;
            // 
            // columnHeader7
            // 
            this.columnHeader7.Text = "Price";
            this.columnHeader7.Width = 70;
            // 
            // columnHeader8
            // 
            this.columnHeader8.Text = "Capacity";
            // 
            // columnHeader9
            // 
            this.columnHeader9.Text = "Amount";
            // 
            // columnHeader10
            // 
            this.columnHeader10.Text = "AircraftType";
            this.columnHeader10.Width = 120;
            // 
            // button_SelectMy
            // 
            this.button_SelectMy.Location = new System.Drawing.Point(730, 597);
            this.button_SelectMy.Name = "button_SelectMy";
            this.button_SelectMy.Size = new System.Drawing.Size(75, 23);
            this.button_SelectMy.TabIndex = 19;
            this.button_SelectMy.Text = "Select";
            this.button_SelectMy.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 389);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 20;
            this.label1.Text = "MyTickets";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 17);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 21;
            this.label2.Text = "AllTickets";
            // 
            // textBox_input_origin
            // 
            this.textBox_input_origin.Location = new System.Drawing.Point(555, 262);
            this.textBox_input_origin.Name = "textBox_input_origin";
            this.textBox_input_origin.Size = new System.Drawing.Size(169, 21);
            this.textBox_input_origin.TabIndex = 22;
            this.textBox_input_origin.TextChanged += new System.EventHandler(this.textBox_input_origin_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(502, 265);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 23;
            this.label3.Text = "Origin:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(490, 292);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 12);
            this.label4.TabIndex = 24;
            this.label4.Text = "Terminal:";
            // 
            // textBox_input_terminal
            // 
            this.textBox_input_terminal.Location = new System.Drawing.Point(555, 289);
            this.textBox_input_terminal.Name = "textBox_input_terminal";
            this.textBox_input_terminal.Size = new System.Drawing.Size(169, 21);
            this.textBox_input_terminal.TabIndex = 25;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(514, 319);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 12);
            this.label5.TabIndex = 26;
            this.label5.Text = "Date:";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(555, 316);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(169, 21);
            this.dateTimePicker1.TabIndex = 27;
            // 
            // BookRefundTicketsForm
            // 
            this.ClientSize = new System.Drawing.Size(898, 645);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox_input_terminal);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox_input_origin);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_SelectMy);
            this.Controls.Add(this.listView_MyTickets);
            this.Controls.Add(this.button_Refund);
            this.Controls.Add(this.button_Book);
            this.Controls.Add(this.button_SelectAll);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.listView_AllTickets);
            this.Name = "BookRefundTicketsForm";
            this.Text = "BookRefundTicketsForm";
            this.Load += new System.EventHandler(this.BookRefundTicketsForm_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_Refund;
        private System.Windows.Forms.Button button_Book;
        private System.Windows.Forms.Button button_SelectAll;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ColumnHeader AircraftType;
        private System.Windows.Forms.ColumnHeader Allowance;
        private System.Windows.Forms.ColumnHeader Capacity;
        private System.Windows.Forms.ColumnHeader Price;
        private System.Windows.Forms.ColumnHeader EndTime;
        private System.Windows.Forms.ColumnHeader BeginTime;
        private System.Windows.Forms.ColumnHeader Date;
        private System.Windows.Forms.ColumnHeader Terminal;
        private System.Windows.Forms.ColumnHeader Origin;
        private System.Windows.Forms.ColumnHeader FlightNumber;
        private System.Windows.Forms.ListView listView_AllTickets;
        private System.Windows.Forms.ListView listView_MyTickets;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.ColumnHeader columnHeader7;
        private System.Windows.Forms.ColumnHeader columnHeader8;
        private System.Windows.Forms.ColumnHeader columnHeader9;
        private System.Windows.Forms.ColumnHeader columnHeader10;
        private System.Windows.Forms.Button button_SelectMy;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_input_origin;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_input_terminal;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
    }
}