namespace Parser_WFA
{
    partial class main_window
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(main_window));
            this.program_title = new System.Windows.Forms.Label();
            this.partition_btn = new System.Windows.Forms.Button();
            this.library_btn = new System.Windows.Forms.Button();
            this.padframe_btn = new System.Windows.Forms.Button();
            this.netlist_btn = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.library_txtbox = new System.Windows.Forms.TextBox();
            this.padframe_txtbox = new System.Windows.Forms.TextBox();
            this.netlist_txtbox = new System.Windows.Forms.TextBox();
            this.help_link = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // program_title
            // 
            this.program_title.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.program_title.AutoSize = true;
            this.program_title.BackColor = System.Drawing.Color.Transparent;
            this.program_title.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.program_title.Location = new System.Drawing.Point(209, 19);
            this.program_title.Name = "program_title";
            this.program_title.Size = new System.Drawing.Size(226, 24);
            this.program_title.TabIndex = 0;
            this.program_title.Text = "The Final Solution";
            this.program_title.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // partition_btn
            // 
            this.partition_btn.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.partition_btn.BackColor = System.Drawing.Color.LightSkyBlue;
            this.partition_btn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.partition_btn.Location = new System.Drawing.Point(261, 287);
            this.partition_btn.Name = "partition_btn";
            this.partition_btn.Size = new System.Drawing.Size(122, 40);
            this.partition_btn.TabIndex = 4;
            this.partition_btn.Text = "Get Wrecked";
            this.partition_btn.UseVisualStyleBackColor = false;
            this.partition_btn.Click += new System.EventHandler(this.partition_btn_Click);
            // 
            // library_btn
            // 
            this.library_btn.BackColor = System.Drawing.Color.LightSkyBlue;
            this.library_btn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.library_btn.Location = new System.Drawing.Point(243, 70);
            this.library_btn.Name = "library_btn";
            this.library_btn.Size = new System.Drawing.Size(158, 40);
            this.library_btn.TabIndex = 5;
            this.library_btn.Text = "Cell Library";
            this.library_btn.UseVisualStyleBackColor = false;
            this.library_btn.Click += new System.EventHandler(this.library_btn_Click);
            // 
            // padframe_btn
            // 
            this.padframe_btn.BackColor = System.Drawing.Color.LightSkyBlue;
            this.padframe_btn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.padframe_btn.Location = new System.Drawing.Point(35, 70);
            this.padframe_btn.Name = "padframe_btn";
            this.padframe_btn.Size = new System.Drawing.Size(158, 40);
            this.padframe_btn.TabIndex = 6;
            this.padframe_btn.Text = "Padframe";
            this.padframe_btn.UseVisualStyleBackColor = false;
            this.padframe_btn.Click += new System.EventHandler(this.padframe_btn_Click);
            // 
            // netlist_btn
            // 
            this.netlist_btn.BackColor = System.Drawing.Color.LightSkyBlue;
            this.netlist_btn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.netlist_btn.Location = new System.Drawing.Point(451, 70);
            this.netlist_btn.Name = "netlist_btn";
            this.netlist_btn.Size = new System.Drawing.Size(158, 40);
            this.netlist_btn.TabIndex = 7;
            this.netlist_btn.Text = "Netlist";
            this.netlist_btn.UseVisualStyleBackColor = false;
            this.netlist_btn.Click += new System.EventHandler(this.netlist_btn_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Location = new System.Drawing.Point(32, 180);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(98, 15);
            this.label4.TabIndex = 8;
            this.label4.Text = "Cell Library:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Location = new System.Drawing.Point(32, 140);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(70, 15);
            this.label5.TabIndex = 9;
            this.label5.Text = "Padframe:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.Location = new System.Drawing.Point(32, 220);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(63, 15);
            this.label6.TabIndex = 10;
            this.label6.Text = "Netlist:";
            // 
            // library_txtbox
            // 
            this.library_txtbox.BackColor = System.Drawing.Color.White;
            this.library_txtbox.Location = new System.Drawing.Point(137, 177);
            this.library_txtbox.Name = "library_txtbox";
            this.library_txtbox.ReadOnly = true;
            this.library_txtbox.ScrollBars = System.Windows.Forms.ScrollBars.Horizontal;
            this.library_txtbox.Size = new System.Drawing.Size(475, 23);
            this.library_txtbox.TabIndex = 14;
            // 
            // padframe_txtbox
            // 
            this.padframe_txtbox.BackColor = System.Drawing.Color.White;
            this.padframe_txtbox.Location = new System.Drawing.Point(137, 137);
            this.padframe_txtbox.Name = "padframe_txtbox";
            this.padframe_txtbox.ReadOnly = true;
            this.padframe_txtbox.ScrollBars = System.Windows.Forms.ScrollBars.Horizontal;
            this.padframe_txtbox.Size = new System.Drawing.Size(475, 23);
            this.padframe_txtbox.TabIndex = 15;
            // 
            // netlist_txtbox
            // 
            this.netlist_txtbox.BackColor = System.Drawing.Color.White;
            this.netlist_txtbox.Location = new System.Drawing.Point(137, 217);
            this.netlist_txtbox.Name = "netlist_txtbox";
            this.netlist_txtbox.ReadOnly = true;
            this.netlist_txtbox.ScrollBars = System.Windows.Forms.ScrollBars.Horizontal;
            this.netlist_txtbox.Size = new System.Drawing.Size(475, 23);
            this.netlist_txtbox.TabIndex = 16;
            // 
            // help_link
            // 
            this.help_link.AutoSize = true;
            this.help_link.Location = new System.Drawing.Point(597, 337);
            this.help_link.Name = "help_link";
            this.help_link.Size = new System.Drawing.Size(35, 15);
            this.help_link.TabIndex = 17;
            this.help_link.TabStop = true;
            this.help_link.Text = "Help";
            this.help_link.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.help_link.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.help_link_LinkClicked);
            // 
            // main_window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(644, 361);
            this.Controls.Add(this.help_link);
            this.Controls.Add(this.netlist_txtbox);
            this.Controls.Add(this.padframe_txtbox);
            this.Controls.Add(this.library_txtbox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.netlist_btn);
            this.Controls.Add(this.padframe_btn);
            this.Controls.Add(this.library_btn);
            this.Controls.Add(this.partition_btn);
            this.Controls.Add(this.program_title);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(660, 395);
            this.Name = "main_window";
            this.ShowIcon = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Very Large Stuff Incorporated";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label program_title;
        private System.Windows.Forms.Button partition_btn;
        private System.Windows.Forms.Button library_btn;
        private System.Windows.Forms.Button padframe_btn;
        private System.Windows.Forms.Button netlist_btn;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox library_txtbox;
        private System.Windows.Forms.TextBox padframe_txtbox;
        private System.Windows.Forms.TextBox netlist_txtbox;
        private System.Windows.Forms.LinkLabel help_link;
    }
}

