namespace Project_2
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.Legend legend5 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            this.lstbx_objects = new System.Windows.Forms.ListBox();
            this.btn_coin = new System.Windows.Forms.Button();
            this.btn_die = new System.Windows.Forms.Button();
            this.btn_gaussian = new System.Windows.Forms.Button();
            this.btn_stop = new System.Windows.Forms.Button();
            this.btn_reset = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtbx_seed = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.histogram = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.generationTimer = new System.Windows.Forms.Timer(this.components);
            this.trkbar_graphSpeed = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.histogram)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkbar_graphSpeed)).BeginInit();
            this.SuspendLayout();
            // 
            // lstbx_objects
            // 
            this.lstbx_objects.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lstbx_objects.FormattingEnabled = true;
            this.lstbx_objects.ItemHeight = 21;
            this.lstbx_objects.Location = new System.Drawing.Point(34, 39);
            this.lstbx_objects.Name = "lstbx_objects";
            this.lstbx_objects.Size = new System.Drawing.Size(174, 445);
            this.lstbx_objects.TabIndex = 6;
            this.lstbx_objects.SelectedIndexChanged += new System.EventHandler(this.lstbx_objects_SelectedIndexChanged);
            // 
            // btn_coin
            // 
            this.btn_coin.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_coin.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btn_coin.FlatAppearance.BorderSize = 2;
            this.btn_coin.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_coin.Font = new System.Drawing.Font("Segoe UI Semibold", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_coin.Location = new System.Drawing.Point(31, 93);
            this.btn_coin.Name = "btn_coin";
            this.btn_coin.Size = new System.Drawing.Size(181, 42);
            this.btn_coin.TabIndex = 1;
            this.btn_coin.Text = "Coin";
            this.btn_coin.UseVisualStyleBackColor = false;
            this.btn_coin.Click += new System.EventHandler(this.object_Click);
            // 
            // btn_die
            // 
            this.btn_die.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_die.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btn_die.FlatAppearance.BorderSize = 2;
            this.btn_die.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_die.Font = new System.Drawing.Font("Segoe UI Semibold", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_die.Location = new System.Drawing.Point(31, 141);
            this.btn_die.Name = "btn_die";
            this.btn_die.Size = new System.Drawing.Size(181, 42);
            this.btn_die.TabIndex = 2;
            this.btn_die.Text = "Die";
            this.btn_die.UseVisualStyleBackColor = false;
            this.btn_die.Click += new System.EventHandler(this.object_Click);
            // 
            // btn_gaussian
            // 
            this.btn_gaussian.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_gaussian.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btn_gaussian.FlatAppearance.BorderSize = 2;
            this.btn_gaussian.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_gaussian.Font = new System.Drawing.Font("Segoe UI Semibold", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_gaussian.Location = new System.Drawing.Point(31, 189);
            this.btn_gaussian.Name = "btn_gaussian";
            this.btn_gaussian.Size = new System.Drawing.Size(181, 42);
            this.btn_gaussian.TabIndex = 3;
            this.btn_gaussian.Text = "Gaussian";
            this.btn_gaussian.UseVisualStyleBackColor = false;
            this.btn_gaussian.Click += new System.EventHandler(this.object_Click);
            // 
            // btn_stop
            // 
            this.btn_stop.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_stop.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btn_stop.FlatAppearance.BorderSize = 2;
            this.btn_stop.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_stop.Font = new System.Drawing.Font("Segoe UI Semibold", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_stop.Location = new System.Drawing.Point(31, 123);
            this.btn_stop.Name = "btn_stop";
            this.btn_stop.Size = new System.Drawing.Size(181, 42);
            this.btn_stop.TabIndex = 4;
            this.btn_stop.Text = "Stop";
            this.btn_stop.UseVisualStyleBackColor = false;
            this.btn_stop.Click += new System.EventHandler(this.btn_stop_Click);
            // 
            // btn_reset
            // 
            this.btn_reset.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_reset.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btn_reset.FlatAppearance.BorderSize = 2;
            this.btn_reset.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_reset.Font = new System.Drawing.Font("Segoe UI Semibold", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_reset.Location = new System.Drawing.Point(31, 171);
            this.btn_reset.Name = "btn_reset";
            this.btn_reset.Size = new System.Drawing.Size(181, 42);
            this.btn_reset.TabIndex = 5;
            this.btn_reset.Text = "Reset";
            this.btn_reset.UseVisualStyleBackColor = false;
            this.btn_reset.Click += new System.EventHandler(this.btn_reset_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Transparent;
            this.groupBox1.Controls.Add(this.txtbx_seed);
            this.groupBox1.Controls.Add(this.btn_gaussian);
            this.groupBox1.Controls.Add(this.btn_die);
            this.groupBox1.Controls.Add(this.btn_coin);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupBox1.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(12, 26);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(244, 258);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Create Object";
            // 
            // txtbx_seed
            // 
            this.txtbx_seed.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtbx_seed.Location = new System.Drawing.Point(31, 39);
            this.txtbx_seed.MaxLength = 5;
            this.txtbx_seed.Name = "txtbx_seed";
            this.txtbx_seed.Size = new System.Drawing.Size(181, 29);
            this.txtbx_seed.TabIndex = 0;
            this.txtbx_seed.Text = "Seed";
            this.txtbx_seed.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Transparent;
            this.groupBox2.Controls.Add(this.trkbar_graphSpeed);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.btn_stop);
            this.groupBox2.Controls.Add(this.btn_reset);
            this.groupBox2.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(12, 303);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(243, 244);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Control Graph";
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Transparent;
            this.groupBox3.Controls.Add(this.lstbx_objects);
            this.groupBox3.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox3.Location = new System.Drawing.Point(284, 26);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(243, 521);
            this.groupBox3.TabIndex = 8;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Objects";
            // 
            // groupBox4
            // 
            this.groupBox4.BackColor = System.Drawing.Color.Transparent;
            this.groupBox4.Controls.Add(this.histogram);
            this.groupBox4.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox4.Location = new System.Drawing.Point(555, 26);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(642, 521);
            this.groupBox4.TabIndex = 9;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Histogram";
            // 
            // histogram
            // 
            legend5.Name = "Legend1";
            this.histogram.Legends.Add(legend5);
            this.histogram.Location = new System.Drawing.Point(6, 24);
            this.histogram.Name = "histogram";
            this.histogram.Size = new System.Drawing.Size(630, 491);
            this.histogram.TabIndex = 0;
            this.histogram.TabStop = false;
            // 
            // generationTimer
            // 
            this.generationTimer.Interval = 500;
            this.generationTimer.Tick += new System.EventHandler(this.generationTimer_Tick);
            // 
            // trkbar_graphSpeed
            // 
            this.trkbar_graphSpeed.BackColor = System.Drawing.Color.White;
            this.trkbar_graphSpeed.LargeChange = 1;
            this.trkbar_graphSpeed.Location = new System.Drawing.Point(69, 59);
            this.trkbar_graphSpeed.Maximum = 1;
            this.trkbar_graphSpeed.Name = "trkbar_graphSpeed";
            this.trkbar_graphSpeed.Size = new System.Drawing.Size(104, 45);
            this.trkbar_graphSpeed.TabIndex = 7;
            this.trkbar_graphSpeed.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkbar_graphSpeed.Scroll += new System.EventHandler(this.trkbar_graphSpeed_Scroll);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(99, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 17);
            this.label1.TabIndex = 10;
            this.label1.Text = "Speed";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1209, 573);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Font = new System.Drawing.Font("Segoe UI", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Pseudo-Random Number Generator";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.histogram)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkbar_graphSpeed)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ListBox lstbx_objects;
        private System.Windows.Forms.Button btn_coin;
        private System.Windows.Forms.Button btn_die;
        private System.Windows.Forms.Button btn_gaussian;
        private System.Windows.Forms.Button btn_stop;
        private System.Windows.Forms.Button btn_reset;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox txtbx_seed;
        private System.Windows.Forms.Timer generationTimer;
        private System.Windows.Forms.DataVisualization.Charting.Chart histogram;
        private System.Windows.Forms.TrackBar trkbar_graphSpeed;
        private System.Windows.Forms.Label label1;
    }
}

