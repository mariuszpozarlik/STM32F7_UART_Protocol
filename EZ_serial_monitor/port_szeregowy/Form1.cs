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
            t = new Thread(testPorts_thread);
            InitializeComponent();

            foreach (int baud in baudRates)
            {
                comboBox2.Items.Add(baud);
            }
            comboBox2.SelectedItem = baudRates[2];

            t.Start();
        }

        private void updateCOMs(string[] ports)
        {
            if (this.comboBox1.InvokeRequired)
            {
                this.Invoke(new Action<string[]>(updateCOMs), new object[] { ports });
                return;
            }
            comboBox1.Items.Clear();
            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);
            }
        }

        private void testPorts_thread()
        {            
            while (true)
            {
                availablePorts = SerialPort.GetPortNames();
                updateCOMs(availablePorts);

                Thread.Sleep(1000);
            }
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
                catch { }
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
                catch { }
                
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
                catch { }
                status.BackColor = Color.Red;
                comboBox1.Enabled = true;
            }
        }

        private void updateMsg(object s)
        {
            if (this.richTextBox1.InvokeRequired)
            {
                this.Invoke(new Action<string>(updateMsg), new object[] { s });
                return;
            }
            richTextBox1.SelectionColor = Color.Green;
            richTextBox1.AppendText((string)s);            
        }

        private void onReceive(object sender, SerialDataReceivedEventArgs e)
        {
            string receive = "";
            int timeout = serialPort1.BytesToRead;
            
            while (timeout > 0)
            {
                receive += Convert.ToChar(serialPort1.ReadByte());
                timeout--;
            }
            ThreadPool.QueueUserWorkItem(updateMsg, receive);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
        }        

        private void Form_onClose(object sender, FormClosedEventArgs e)
        {
            t.Abort();
        }

    }
}
