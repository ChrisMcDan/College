using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace Tax_Program
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void TbxName_TextChanged(object sender, EventArgs e)
        {

        }

        private void TextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void TextBox1_TextChanged_2(object sender, EventArgs e)
        {

        }

        private void MStatus_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Label1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void ToolStripTextBox1_Click(object sender, EventArgs e)
        {

        }

        private void Label2_Click(object sender, EventArgs e)
        {

        }

        private void RadioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void Button1_Click(object sender, EventArgs e)
        {
            double income = Double.Parse(tbxIncome.Text);
            double total = income * 2;
            FederalTaxOutput.Text = total.ToString();

            //array
            double[] SBBase = new double[] { 0, 0, 35.90, 201.05, 719.80, 1794.16, 4650.31, 4673.41 };
            double[] SBMax = new double[] { 88, 447, 1548, 3623, 7460, 16115, 16181, 0 };
            double[] SBPct = new double[] { 0, 0.10, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396 };

            double[] MBBase = new double[] { 0, 0, 71.70, 402, 1144.25, 2008.61, 4335.77, 5062.72 };
            double[] MBMax = new double[] { 333, 1050, 3252, 6221, 9308, 16360, 18437, 0 };
            double[] MBPct = new double[] { 0, 0.10, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396 };

            double[] SMBase = new double[] { 0, 0, 77.70, 435.45, 1559.45, 3887.09, 10075.91, 10125.26 };
            double[] SMMax = new double[] { 192, 969, 3354, 7850, 16163, 34917, 35058, 0 };
            double[] SMPct = new double[]{ 0, 0.10, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396 };

            double[] MMBase = new double[] { 0, 0, 155.40, 871.05, 2479.30, 4351.94, 9394.01, 10969.01 };
            double[] MMMax = new double[] { 721, 2275, 7046, 13479, 20167, 35446, 39946, 0 };
            double[] MMPct = new double[] { 0, 0.10, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396 };


            //variables
            int dependents = Int32.Parse(tbxDependents.Text);
            double grossPay = Int32.Parse(tbxIncome.Text);
            int mStatus = MStatus.SelectedIndex;
            int payPeriod = comboBox1.SelectedIndex;

            //constants
                double SSPCT = 0.062;
                double MEDPCT = 0.0145;
                double BWith = 155.80;
                double MWith = 337.50;

                double fedTax = 0;
                double ssTax = 0;
                double medTax = 0;
                double netPay = 0;                       
                
                if (mStatus == 0)    // single
                {
                    if (payPeriod == 0)   // biweekly
                    {

                        fedTax = CalcFedTax(dependents, BWith, grossPay, SBBase, SBMax, SBPct);
                        
                    }
                    else   //monthly
                    {
                        if (payPeriod == 1)
                        {

                            fedTax = CalcFedTax(dependents, BWith, grossPay, SMBase, SMMax, SMPct);

                        }
                    }
                }
                if (mStatus == 1)   // married
                {
                    if (payPeriod == 0)   // biweekly
                    {

                        fedTax = CalcFedTax(dependents, MWith, grossPay, MBBase, MBMax, MBPct);

                    }
                    else    //monthly
                    {
                        if (payPeriod == 1)    //monthly
                        {

                            fedTax = CalcFedTax(dependents, MWith, grossPay, MMBase, MMMax, MMPct);

                        }
                    }
                }                              
            

            ssTax = grossPay * SSPCT;
            medTax = grossPay * MEDPCT;
            netPay = grossPay - fedTax - ssTax - medTax;

            FederalTaxOutput.Text = fedTax.ToString("0.00");
            SSTaxOutput.Text = ssTax.ToString("0.00");
            MedTaxOutput.Text = medTax.ToString("0.00");
            NetPayOutput.Text = netPay.ToString("0.00");
        }

        double CalcFedTax(int dep, double withDepAmt, double grossPay, double[] Base, double[] Max, double[] Pct)
        {

            double withholding = 0;
            double taxablePay = 0;
            double fedTax = 0;

            withholding = dep * withDepAmt;
            taxablePay = grossPay - withholding;

            if (taxablePay <= Max[0])   //Level 1
            {
                fedTax = 0;
            }
            else if (taxablePay <= Max[1])    //Level 2
            {
                fedTax = Base[1] + (Pct[1] * (taxablePay - Max[0]));
            }
            else if (taxablePay <= Max[2])    //Level 3
            {
                fedTax = Base[2] + (Pct[2] * (taxablePay - Max[1]));
            }
            else if (taxablePay <= Max[3])    //Level 4
            {
                fedTax = Base[3] + (Pct[3] * (taxablePay - Max[2]));
            }
            else if (taxablePay <= Max[4])    //Level 5
            {
                fedTax = Base[4] + (Pct[4] * (taxablePay - Max[3]));
            }
            else if (taxablePay <= Max[5])    //Level 6
            {
                fedTax = Base[5] + (Pct[5] * (taxablePay - Max[4]));
            }
            else if (taxablePay <= Max[6])    //Level 7
            {
                fedTax = Base[6] + (Pct[6] * (taxablePay - Max[5]));
            }
            else    //Level 8
            {
                fedTax = Base[7] + (Pct[7] * (taxablePay - Max[6]));
            }

            return fedTax;
        }

        private void Button1_Click_1(object sender, EventArgs e)
        {
            this.Close();
        }

        private void TextBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void Label4_Click(object sender, EventArgs e)
        {

        }

        private void Dependents_Click(object sender, EventArgs e)
        {

        }

        private void BtnSingle_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void TbxmStatus_Click(object sender, EventArgs e)
        {

        }

        private void NetPayOutput_TextChanged(object sender, EventArgs e)
        {

        }

        private void FederalTaxOutput_TextChanged(object sender, EventArgs e)
        {
            
        }
    }
}