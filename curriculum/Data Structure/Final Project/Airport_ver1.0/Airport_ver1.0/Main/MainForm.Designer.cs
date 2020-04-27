namespace Airport_ver1._0
{
    partial class MainForm
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
            this.button_Login = new System.Windows.Forms.Button();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.button_Register = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.ManageTickets = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.listView_History = new System.Windows.Forms.ListView();
            this.label_Username = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.listView1 = new System.Windows.Forms.ListView();
            this.button_ChangeLevel = new System.Windows.Forms.Button();
            this.statusStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_Login
            // 
            this.button_Login.Location = new System.Drawing.Point(616, 12);
            this.button_Login.Name = "button_Login";
            this.button_Login.Size = new System.Drawing.Size(75, 23);
            this.button_Login.TabIndex = 0;
            this.button_Login.Text = "Login";
            this.button_Login.UseVisualStyleBackColor = true;
            this.button_Login.Click += new System.EventHandler(this.button_Login_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 389);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(784, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel
            // 
            this.toolStripStatusLabel.Name = "toolStripStatusLabel";
            this.toolStripStatusLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // button_Register
            // 
            this.button_Register.Location = new System.Drawing.Point(697, 12);
            this.button_Register.Name = "button_Register";
            this.button_Register.Size = new System.Drawing.Size(75, 23);
            this.button_Register.TabIndex = 2;
            this.button_Register.Text = "Register";
            this.button_Register.UseVisualStyleBackColor = true;
            this.button_Register.Click += new System.EventHandler(this.button_Regitser_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.ManageTickets);
            this.panel1.Location = new System.Drawing.Point(13, 13);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 373);
            this.panel1.TabIndex = 3;
            // 
            // ManageTickets
            // 
            this.ManageTickets.Location = new System.Drawing.Point(3, 347);
            this.ManageTickets.Name = "ManageTickets";
            this.ManageTickets.Size = new System.Drawing.Size(113, 23);
            this.ManageTickets.TabIndex = 8;
            this.ManageTickets.Text = "ManageTickets";
            this.ManageTickets.UseVisualStyleBackColor = true;
            this.ManageTickets.Click += new System.EventHandler(this.ManageTickets_Click);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.listView_History);
            this.panel2.Location = new System.Drawing.Point(572, 42);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(200, 344);
            this.panel2.TabIndex = 4;
            // 
            // listView_History
            // 
            this.listView_History.GridLines = true;
            this.listView_History.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listView_History.Location = new System.Drawing.Point(3, 3);
            this.listView_History.Name = "listView_History";
            this.listView_History.Size = new System.Drawing.Size(193, 337);
            this.listView_History.TabIndex = 0;
            this.listView_History.UseCompatibleStateImageBehavior = false;
            this.listView_History.View = System.Windows.Forms.View.Details;
            // 
            // label_Username
            // 
            this.label_Username.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label_Username.Location = new System.Drawing.Point(461, 12);
            this.label_Username.Name = "label_Username";
            this.label_Username.Size = new System.Drawing.Size(149, 23);
            this.label_Username.TabIndex = 5;
            this.label_Username.Text = "Please login or register";
            this.label_Username.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.listView1);
            this.panel3.Location = new System.Drawing.Point(367, 42);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(200, 344);
            this.panel3.TabIndex = 6;
            // 
            // listView1
            // 
            this.listView1.GridLines = true;
            this.listView1.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listView1.Location = new System.Drawing.Point(4, 3);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(193, 337);
            this.listView1.TabIndex = 1;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // button_ChangeLevel
            // 
            this.button_ChangeLevel.Location = new System.Drawing.Point(371, 12);
            this.button_ChangeLevel.Name = "button_ChangeLevel";
            this.button_ChangeLevel.Size = new System.Drawing.Size(84, 23);
            this.button_ChangeLevel.TabIndex = 9;
            this.button_ChangeLevel.Text = "ChangeLevel";
            this.button_ChangeLevel.UseVisualStyleBackColor = true;
            this.button_ChangeLevel.Visible = false;
            this.button_ChangeLevel.Click += new System.EventHandler(this.button_ChangeLevel_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 411);
            this.Controls.Add(this.button_ChangeLevel);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.label_Username);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.button_Register);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.button_Login);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "MainForm";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_Login;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel;
        private System.Windows.Forms.Button button_Register;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.ListView listView_History;
        private System.Windows.Forms.Label label_Username;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.Button ManageTickets;
        private System.Windows.Forms.Button button_ChangeLevel;
    }
}