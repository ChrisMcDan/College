namespace Tax_Program
{
    partial class Form1
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
            this.Income = new System.Windows.Forms.Label();
            this.PayPeriods = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.btnSubmit = new System.Windows.Forms.Button();
            this.tbxIncome = new System.Windows.Forms.TextBox();
            this.FederalTaxOutput = new System.Windows.Forms.TextBox();
            this.btnExit = new System.Windows.Forms.Button();
            this.Dependents = new System.Windows.Forms.Label();
            this.tbxDependents = new System.Windows.Forms.TextBox();
            this.bxName = new System.Windows.Forms.Label();
            this.tbxName = new System.Windows.Forms.TextBox();
            this.tbxMStatus = new System.Windows.Forms.Label();
            this.fedTax = new System.Windows.Forms.Label();
            this.ssTax = new System.Windows.Forms.Label();
            this.medTax = new System.Windows.Forms.Label();
            this.netPay = new System.Windows.Forms.Label();
            this.SSTaxOutput = new System.Windows.Forms.TextBox();
            this.MedTaxOutput = new System.Windows.Forms.TextBox();
            this.NetPayOutput = new System.Windows.Forms.TextBox();
            this.MStatus = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // Income
            // 
            this.Income.AutoSize = true;
            this.Income.Location = new System.Drawing.Point(12, 65);
            this.Income.Name = "Income";
            this.Income.Size = new System.Drawing.Size(62, 20);
            this.Income.TabIndex = 0;
            this.Income.Text = "Income";
            this.Income.Click += new System.EventHandler(this.Label1_Click);
            // 
            // PayPeriods
            // 
            this.PayPeriods.AutoSize = true;
            this.PayPeriods.Location = new System.Drawing.Point(375, 92);
            this.PayPeriods.Name = "PayPeriods";
            this.PayPeriods.Size = new System.Drawing.Size(92, 20);
            this.PayPeriods.TabIndex = 1;
            this.PayPeriods.Text = "Pay Periods\r\n";
            this.PayPeriods.Click += new System.EventHandler(this.Label2_Click);
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "Biweekly",
            "Monthly"});
            this.comboBox1.Location = new System.Drawing.Point(539, 92);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 28);
            this.comboBox1.TabIndex = 4;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // btnSubmit
            // 
            this.btnSubmit.Location = new System.Drawing.Point(238, 468);
            this.btnSubmit.Name = "btnSubmit";
            this.btnSubmit.Size = new System.Drawing.Size(90, 30);
            this.btnSubmit.TabIndex = 5;
            this.btnSubmit.Text = "Submit";
            this.btnSubmit.UseVisualStyleBackColor = true;
            this.btnSubmit.Click += new System.EventHandler(this.Button1_Click);
            // 
            // tbxIncome
            // 
            this.tbxIncome.Location = new System.Drawing.Point(175, 65);
            this.tbxIncome.Name = "tbxIncome";
            this.tbxIncome.Size = new System.Drawing.Size(100, 26);
            this.tbxIncome.TabIndex = 6;
            this.tbxIncome.TextChanged += new System.EventHandler(this.TextBox1_TextChanged);
            // 
            // FederalTaxOutput
            // 
            this.FederalTaxOutput.Location = new System.Drawing.Point(399, 248);
            this.FederalTaxOutput.Name = "FederalTaxOutput";
            this.FederalTaxOutput.Size = new System.Drawing.Size(100, 26);
            this.FederalTaxOutput.TabIndex = 7;
            this.FederalTaxOutput.TextChanged += new System.EventHandler(this.FederalTaxOutput_TextChanged);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(397, 468);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(76, 30);
            this.btnExit.TabIndex = 8;
            this.btnExit.Text = "Exit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.Button1_Click_1);
            // 
            // Dependents
            // 
            this.Dependents.AutoSize = true;
            this.Dependents.Location = new System.Drawing.Point(11, 128);
            this.Dependents.Name = "Dependents";
            this.Dependents.Size = new System.Drawing.Size(97, 20);
            this.Dependents.TabIndex = 9;
            this.Dependents.Text = "Dependents";
            this.Dependents.Click += new System.EventHandler(this.Dependents_Click);
            // 
            // tbxDependents
            // 
            this.tbxDependents.Location = new System.Drawing.Point(175, 128);
            this.tbxDependents.Name = "tbxDependents";
            this.tbxDependents.Size = new System.Drawing.Size(100, 26);
            this.tbxDependents.TabIndex = 10;
            this.tbxDependents.TextChanged += new System.EventHandler(this.TextBox1_TextChanged_2);
            // 
            // bxName
            // 
            this.bxName.AutoSize = true;
            this.bxName.Location = new System.Drawing.Point(12, 9);
            this.bxName.Name = "bxName";
            this.bxName.Size = new System.Drawing.Size(51, 20);
            this.bxName.TabIndex = 11;
            this.bxName.Text = "Name";
            this.bxName.Click += new System.EventHandler(this.Label4_Click);
            // 
            // tbxName
            // 
            this.tbxName.Location = new System.Drawing.Point(175, 9);
            this.tbxName.Name = "tbxName";
            this.tbxName.Size = new System.Drawing.Size(100, 26);
            this.tbxName.TabIndex = 12;
            this.tbxName.TextChanged += new System.EventHandler(this.TbxName_TextChanged);
            // 
            // tbxMStatus
            // 
            this.tbxMStatus.AutoSize = true;
            this.tbxMStatus.Location = new System.Drawing.Point(375, 30);
            this.tbxMStatus.Name = "tbxMStatus";
            this.tbxMStatus.Size = new System.Drawing.Size(107, 20);
            this.tbxMStatus.TabIndex = 13;
            this.tbxMStatus.Text = "Marital Status";
            this.tbxMStatus.Click += new System.EventHandler(this.TbxmStatus_Click);
            // 
            // fedTax
            // 
            this.fedTax.AutoSize = true;
            this.fedTax.Location = new System.Drawing.Point(236, 248);
            this.fedTax.Name = "fedTax";
            this.fedTax.Size = new System.Drawing.Size(92, 20);
            this.fedTax.TabIndex = 14;
            this.fedTax.Text = "Federal Tax";
            // 
            // ssTax
            // 
            this.ssTax.AutoSize = true;
            this.ssTax.Location = new System.Drawing.Point(235, 280);
            this.ssTax.Name = "ssTax";
            this.ssTax.Size = new System.Drawing.Size(142, 20);
            this.ssTax.TabIndex = 15;
            this.ssTax.Text = "Social Security Tax";
            // 
            // medTax
            // 
            this.medTax.AutoSize = true;
            this.medTax.Location = new System.Drawing.Point(236, 312);
            this.medTax.Name = "medTax";
            this.medTax.Size = new System.Drawing.Size(92, 20);
            this.medTax.TabIndex = 16;
            this.medTax.Text = "Medical Tax";
            // 
            // netPay
            // 
            this.netPay.AutoSize = true;
            this.netPay.Location = new System.Drawing.Point(235, 344);
            this.netPay.Name = "netPay";
            this.netPay.Size = new System.Drawing.Size(64, 20);
            this.netPay.TabIndex = 17;
            this.netPay.Text = "Net Pay";
            // 
            // SSTaxOutput
            // 
            this.SSTaxOutput.Location = new System.Drawing.Point(399, 280);
            this.SSTaxOutput.Name = "SSTaxOutput";
            this.SSTaxOutput.Size = new System.Drawing.Size(100, 26);
            this.SSTaxOutput.TabIndex = 18;
            // 
            // MedTaxOutput
            // 
            this.MedTaxOutput.Location = new System.Drawing.Point(399, 312);
            this.MedTaxOutput.Name = "MedTaxOutput";
            this.MedTaxOutput.Size = new System.Drawing.Size(100, 26);
            this.MedTaxOutput.TabIndex = 19;
            // 
            // NetPayOutput
            // 
            this.NetPayOutput.Location = new System.Drawing.Point(399, 344);
            this.NetPayOutput.Name = "NetPayOutput";
            this.NetPayOutput.Size = new System.Drawing.Size(100, 26);
            this.NetPayOutput.TabIndex = 20;
            this.NetPayOutput.TextChanged += new System.EventHandler(this.NetPayOutput_TextChanged);
            // 
            // MStatus
            // 
            this.MStatus.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.MStatus.FormattingEnabled = true;
            this.MStatus.Items.AddRange(new object[] {
            "Single",
            "Married"});
            this.MStatus.Location = new System.Drawing.Point(539, 30);
            this.MStatus.Name = "MStatus";
            this.MStatus.Size = new System.Drawing.Size(121, 28);
            this.MStatus.TabIndex = 21;
            this.MStatus.SelectedIndexChanged += new System.EventHandler(this.MStatus_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(770, 672);
            this.Controls.Add(this.MStatus);
            this.Controls.Add(this.NetPayOutput);
            this.Controls.Add(this.MedTaxOutput);
            this.Controls.Add(this.SSTaxOutput);
            this.Controls.Add(this.netPay);
            this.Controls.Add(this.medTax);
            this.Controls.Add(this.ssTax);
            this.Controls.Add(this.fedTax);
            this.Controls.Add(this.tbxMStatus);
            this.Controls.Add(this.tbxName);
            this.Controls.Add(this.bxName);
            this.Controls.Add(this.tbxDependents);
            this.Controls.Add(this.Dependents);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.FederalTaxOutput);
            this.Controls.Add(this.tbxIncome);
            this.Controls.Add(this.btnSubmit);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.PayPeriods);
            this.Controls.Add(this.Income);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label Income;
        private System.Windows.Forms.Label PayPeriods;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button btnSubmit;
        private System.Windows.Forms.TextBox tbxIncome;
        private System.Windows.Forms.TextBox FederalTaxOutput;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Label Dependents;
        private System.Windows.Forms.TextBox tbxDependents;
        private System.Windows.Forms.Label bxName;
        private System.Windows.Forms.TextBox tbxName;
        private System.Windows.Forms.Label tbxMStatus;
        private System.Windows.Forms.Label fedTax;
        private System.Windows.Forms.Label ssTax;
        private System.Windows.Forms.Label medTax;
        private System.Windows.Forms.Label netPay;
        private System.Windows.Forms.TextBox SSTaxOutput;
        private System.Windows.Forms.TextBox MedTaxOutput;
        private System.Windows.Forms.TextBox NetPayOutput;
        private System.Windows.Forms.ComboBox MStatus;
    }
}

