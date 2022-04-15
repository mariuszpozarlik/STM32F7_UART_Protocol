using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.IO.Ports;

namespace EZ_serial_monitor
{
    public partial class Form1 : Form
    {
        public string[] availablePorts = SerialPort.GetPortNames();
        public int[] baudRates = 
        {
            2400,
            4800,
            9600,
            14400,
            19200,
            38400,
            57600,
            115200,
            128000
        };
        private Thread t;

        public Form1()
        {
            
            //t = new Thread(new ThreadStart(update));
            InitializeComponent();
            foreach(string port in availablePorts)
            {
                comboBox1.Items.Add(port);
            }
            foreach (int baud in baudRates)
            {
                comboBox2.Items.Add(baud);
            }
            comboBox2.SelectedItem = 9600;

            if (comboBox1.Items.Count > 0)
            {
                serialPort1.PortName = availablePorts[0];
                comboBox1.SelectedItem = availablePorts[0];
            }
            //t.Start();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Write(textBox1.Text);                    
                }
                catch (System.IO.IOException)
                {
                    richTextBox1.SelectionColor = Color.Red;
                    richTextBox1.AppendText("Send error" + Environment.NewLine);
                    return;
                }
                richTextBox1.AppendText(Environment.NewLine);
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = comboBox1.SelectedItem.ToString();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                serialPort1.BaudRate = int.Parse(comboBox2.SelectedItem.ToString());
            }
            catch (System.IO.IOException)
            {
                richTextBox1.SelectionColor = Color.Red;
                richTextBox1.AppendText("Can't change baudrate" + Environment.NewLine);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Open();
                }
                catch (System.IO.IOException)
                {
                    status.BackColor = Color.Red;
                    comboBox1.Enabled = true;
                    richTextBox1.SelectionColor = Color.Red;
                    richTextBox1.AppendText(comboBox1.Text + " port error" + Environment.NewLine);
                    return;
                }
                status.BackColor = Color.Green;
                comboBox1.Enabled = false;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Close();
                }
                catch (System.IO.IOException)
                {
                    richTextBox1.SelectionColor = Color.Red;
                    richTextBox1.AppendText(comboBox1.Text + " port error" + Environment.NewLine);
                }
                status.BackColor = Color.Red;
                comboBox1.Enabled = true;
            }
        }

        private void updateMsg(string s)
        {
            if (InvokeRequired)
            {
                this.Invoke(new Action<string>(updateMsg), new object[] { s });
                return;
            }
            richTextBox1.SelectionColor = Color.Green;
            richTextBox1.AppendText(s);
            
        }

        private void onReceive(object sender, SerialDataReceivedEventArgs e)
        {
            string reveive = "";
            int timeout = serialPort1.BytesToRead;
            while(timeout > 0)
            {
                reveive += Convert.ToChar(serialPort1.ReadByte());
                timeout--;
            }
            updateMsg(reveive);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
        }        
    }
}
