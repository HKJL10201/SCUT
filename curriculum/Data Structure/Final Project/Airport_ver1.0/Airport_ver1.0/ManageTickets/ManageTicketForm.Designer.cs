namespace Airport_ver1._0.ManageTickets
{
    partial class ManageTicketForm
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
            this.label_FlightNumber = new System.Windows.Forms.Label();
            this.label_Origin = new System.Windows.Forms.Label();
            this.textBox_FlightNumber = new System.Windows.Forms.TextBox();
            this.textBox_Origin = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.label_BeginTime = new System.Windows.Forms.Label();
            this.textBox_Terminal = new System.Windows.Forms.TextBox();
            this.label_Terminal = new System.Windows.Forms.Label();
            this.textBox_BeginTime = new System.Windows.Forms.TextBox();
            this.label_EndTime = new System.Windows.Forms.Label();
            this.label_Price = new System.Windows.Forms.Label();
            this.label_Capacity = new System.Windows.Forms.Label();
            this.label_Allowance = new System.Windows.Forms.Label();
            this.label_AircraftType = new System.Windows.Forms.Label();
            this.textBox_EndTime = new System.Windows.Forms.TextBox();
            this.textBox_Price = new System.Windows.Forms.TextBox();
            this.textBox_Capacity = new System.Windows.Forms.TextBox();
            this.textBox_Allowance = new System.Windows.Forms.TextBox();
            this.textBox_AircraftType = new System.Windows.Forms.TextBox();
            this.button_Confirm = new System.Windows.Forms.Button();
            this.button_Close = new System.Windows.Forms.Button();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.dateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.label_Date = new System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label_FlightNumber
            // 
            this.label_FlightNumber.AutoSize = true;
            this.label_FlightNumber.Location = new System.Drawing.Point(8, 1);
            this.label_FlightNumber.Name = "label_FlightNumber";
            this.label_FlightNumber.Size = new System.Drawing.Size(77, 12);
            this.label_FlightNumber.TabIndex = 0;
            this.label_FlightNumber.Text = "FlightNumber";
            // 
            // label_Origin
            // 
            this.label_Origin.AutoSize = true;
            this.label_Origin.Location = new System.Drawing.Point(8, 28);
            this.label_Origin.Name = "label_Origin";
            this.label_Origin.Size = new System.Drawing.Size(41, 12);
            this.label_Origin.TabIndex = 1;
            this.label_Origin.Text = "Origin";
            // 
            // textBox_FlightNumber
            // 
            this.textBox_FlightNumber.Location = new System.Drawing.Point(91, 4);
            this.textBox_FlightNumber.Name = "textBox_FlightNumber";
            this.textBox_FlightNumber.Size = new System.Drawing.Size(232, 21);
            this.textBox_FlightNumber.TabIndex = 2;
            // 
            // textBox_Origin
            // 
            this.textBox_Origin.Location = new System.Drawing.Point(91, 31);
            this.textBox_Origin.Name = "textBox_Origin";
            this.textBox_Origin.Size = new System.Drawing.Size(232, 21);
            this.textBox_Origin.TabIndex = 3;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.label_BeginTime, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.textBox_Terminal, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.textBox_Origin, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.label_Origin, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.label_Terminal, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.textBox_BeginTime, 1, 4);
            this.tableLayoutPanel1.Controls.Add(this.label_EndTime, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.label_Price, 0, 6);
            this.tableLayoutPanel1.Controls.Add(this.label_Capacity, 0, 7);
            this.tableLayoutPanel1.Controls.Add(this.label_Allowance, 0, 8);
            this.tableLayoutPanel1.Controls.Add(this.label_AircraftType, 0, 9);
            this.tableLayoutPanel1.Controls.Add(this.textBox_EndTime, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.textBox_Price, 1, 6);
            this.tableLayoutPanel1.Controls.Add(this.textBox_Capacity, 1, 7);
            this.tableLayoutPanel1.Controls.Add(this.textBox_Allowance, 1, 8);
            this.tableLayoutPanel1.Controls.Add(this.textBox_AircraftType, 1, 9);
            this.tableLayoutPanel1.Controls.Add(this.textBox_FlightNumber, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.label_FlightNumber, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.dateTimePicker, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.label_Date, 0, 3);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 18);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.Padding = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.tableLayoutPanel1.RowCount = 11;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(323, 282);
            this.tableLayoutPanel1.TabIndex = 4;
            this.tableLayoutPanel1.Paint += new System.Windows.Forms.PaintEventHandler(this.tableLayoutPanel1_Paint);
            // 
            // label_BeginTime
            // 
            this.label_BeginTime.AutoSize = true;
            this.label_BeginTime.Location = new System.Drawing.Point(8, 109);
            this.label_BeginTime.Name = "label_BeginTime";
            this.label_BeginTime.Size = new System.Drawing.Size(59, 12);
            this.label_BeginTime.TabIndex = 9;
            this.label_BeginTime.Text = "BeginTime";
            // 
            // textBox_Terminal
            // 
            this.textBox_Terminal.Location = new System.Drawing.Point(91, 58);
            this.textBox_Terminal.Name = "textBox_Terminal";
            this.textBox_Terminal.Size = new System.Drawing.Size(232, 21);
            this.textBox_Terminal.TabIndex = 5;
            // 
            // label_Terminal
            // 
            this.label_Terminal.AutoSize = true;
            this.label_Terminal.Location = new System.Drawing.Point(8, 55);
            this.label_Terminal.Name = "label_Terminal";
            this.label_Terminal.Size = new System.Drawing.Size(53, 12);
            this.label_Terminal.TabIndex = 4;
            this.label_Terminal.Text = "Terminal";
            // 
            // textBox_BeginTime
            // 
            this.textBox_BeginTime.Location = new System.Drawing.Point(91, 112);
            this.textBox_BeginTime.Name = "textBox_BeginTime";
            this.textBox_BeginTime.Size = new System.Drawing.Size(232, 21);
            this.textBox_BeginTime.TabIndex = 7;
            // 
            // label_EndTime
            // 
            this.label_EndTime.AutoSize = true;
            this.label_EndTime.Location = new System.Drawing.Point(8, 136);
            this.label_EndTime.Name = "label_EndTime";
            this.label_EndTime.Size = new System.Drawing.Size(47, 12);
            this.label_EndTime.TabIndex = 10;
            this.label_EndTime.Text = "EndTime";
            // 
            // label_Price
            // 
            this.label_Price.AutoSize = true;
            this.label_Price.Location = new System.Drawing.Point(8, 163);
            this.label_Price.Name = "label_Price";
            this.label_Price.Size = new System.Drawing.Size(35, 12);
            this.label_Price.TabIndex = 11;
            this.label_Price.Text = "Price";
            // 
            // label_Capacity
            // 
            this.label_Capacity.AutoSize = true;
            this.label_Capacity.Location = new System.Drawing.Point(8, 190);
            this.label_Capacity.Name = "label_Capacity";
            this.label_Capacity.Size = new System.Drawing.Size(53, 12);
            this.label_Capacity.TabIndex = 12;
            this.label_Capacity.Text = "Capacity";
            // 
            // label_Allowance
            // 
            this.label_Allowance.AutoSize = true;
            this.label_Allowance.Location = new System.Drawing.Point(8, 217);
            this.label_Allowance.Name = "label_Allowance";
            this.label_Allowance.Size = new System.Drawing.Size(59, 12);
            this.label_Allowance.TabIndex = 13;
            this.label_Allowance.Text = "Allowance";
            // 
            // label_AircraftType
            // 
            this.label_AircraftType.AutoSize = true;
            this.label_AircraftType.Location = new System.Drawing.Point(8, 244);
            this.label_AircraftType.Name = "label_AircraftType";
            this.label_AircraftType.Size = new System.Drawing.Size(77, 12);
            this.label_AircraftType.TabIndex = 14;
            this.label_AircraftType.Text = "AircraftType";
            // 
            // textBox_EndTime
            // 
            this.textBox_EndTime.Location = new System.Drawing.Point(91, 139);
            this.textBox_EndTime.Name = "textBox_EndTime";
            this.textBox_EndTime.Size = new System.Drawing.Size(232, 21);
            this.textBox_EndTime.TabIndex = 15;
            // 
            // textBox_Price
            // 
            this.textBox_Price.Location = new System.Drawing.Point(91, 166);
            this.textBox_Price.Name = "textBox_Price";
            this.textBox_Price.Size = new System.Drawing.Size(232, 21);
            this.textBox_Price.TabIndex = 16;
            // 
            // textBox_Capacity
            // 
            this.textBox_Capacity.Location = new System.Drawing.Point(91, 193);
            this.textBox_Capacity.Name = "textBox_Capacity";
            this.textBox_Capacity.Size = new System.Drawing.Size(232, 21);
            this.textBox_Capacity.TabIndex = 17;
            // 
            // textBox_Allowance
            // 
            this.textBox_Allowance.Location = new System.Drawing.Point(91, 220);
            this.textBox_Allowance.Name = "textBox_Allowance";
            this.textBox_Allowance.Size = new System.Drawing.Size(232, 21);
            this.textBox_Allowance.TabIndex = 18;
            // 
            // textBox_AircraftType
            // 
            this.textBox_AircraftType.Location = new System.Drawing.Point(91, 247);
            this.textBox_AircraftType.Name = "textBox_AircraftType";
            this.textBox_AircraftType.Size = new System.Drawing.Size(232, 21);
            this.textBox_AircraftType.TabIndex = 19;
            // 
            // button_Confirm
            // 
            this.button_Confirm.Location = new System.Drawing.Point(179, 306);
            this.button_Confirm.Name = "button_Confirm";
            this.button_Confirm.Size = new System.Drawing.Size(75, 23);
            this.button_Confirm.TabIndex = 5;
            this.button_Confirm.Text = "Confirm";
            this.button_Confirm.UseVisualStyleBackColor = true;
            this.button_Confirm.Click += new System.EventHandler(this.button_Confirm_Click);
            // 
            // button_Close
            // 
            this.button_Close.Location = new System.Drawing.Point(260, 306);
            this.button_Close.Name = "button_Close";
            this.button_Close.Size = new System.Drawing.Size(75, 23);
            this.button_Close.TabIndex = 6;
            this.button_Close.Text = "Close";
            this.button_Close.UseVisualStyleBackColor = true;
            this.button_Close.Click += new System.EventHandler(this.button_Close_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 332);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(347, 22);
            this.statusStrip1.TabIndex = 7;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(131, 17);
            this.toolStripStatusLabel1.Text = "toolStripStatusLabel1";
            // 
            // dateTimePicker
            // 
            this.dateTimePicker.Location = new System.Drawing.Point(91, 85);
            this.dateTimePicker.Name = "dateTimePicker";
            this.dateTimePicker.Size = new System.Drawing.Size(232, 21);
            this.dateTimePicker.TabIndex = 29;
            this.dateTimePicker.ValueChanged += new System.EventHandler(this.dateTimePicker_ValueChanged);
            // 
            // label_Date
            // 
            this.label_Date.AutoSize = true;
            this.label_Date.Location = new System.Drawing.Point(8, 82);
            this.label_Date.Name = "label_Date";
            this.label_Date.Size = new System.Drawing.Size(35, 12);
            this.label_Date.TabIndex = 28;
            this.label_Date.Text = "Date:";
            // 
            // ManageTicketForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(347, 354);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.button_Close);
            this.Controls.Add(this.button_Confirm);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "ManageTicketForm";
            this.Text = "ManageTicketForm";
            this.Load += new System.EventHandler(this.ManageTicketForm_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label label_FlightNumber;
        private System.Windows.Forms.Label label_Origin;
        private System.Windows.Forms.TextBox textBox_FlightNumber;
        private System.Windows.Forms.TextBox textBox_Origin;
        private System.Windows.Forms.Label label_BeginTime;
        private System.Windows.Forms.TextBox textBox_Terminal;
        private System.Windows.Forms.Label label_Terminal;
        private System.Windows.Forms.TextBox textBox_BeginTime;
        private System.Windows.Forms.Label label_EndTime;
        private System.Windows.Forms.Label label_Price;
        private System.Windows.Forms.Label label_Capacity;
        private System.Windows.Forms.Label label_Allowance;
        private System.Windows.Forms.Label label_AircraftType;
        private System.Windows.Forms.TextBox textBox_EndTime;
        private System.Windows.Forms.TextBox textBox_Price;
        private System.Windows.Forms.TextBox textBox_Capacity;
        private System.Windows.Forms.TextBox textBox_Allowance;
        private System.Windows.Forms.TextBox textBox_AircraftType;
        private System.Windows.Forms.Button button_Confirm;
        private System.Windows.Forms.Button button_Close;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.DateTimePicker dateTimePicker;
        private System.Windows.Forms.Label label_Date;
    }
}