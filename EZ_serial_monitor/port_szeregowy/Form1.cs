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
using System.IO;

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
        private Thread tp_thread;
        private Thread l_thread;
        private Thread ps_thread;
        private string filePath = "";
        private string fileBuffer = "";

        public Form1()
        {
            tp_thread = new Thread(testPorts_Thread);
            l_thread = new Thread(log_Thread);
            ps_thread = new Thread(periodicSend_Thread);
            InitializeComponent();

            foreach (int baud in baudRates)
            {
                comboBox2.Items.Add(baud);
            }
            comboBox2.SelectedItem = baudRates[2];

            tp_thread.Start();
            l_thread.Start();
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

        private void testPorts_Thread()
        {
            while (true)
            {
                availablePorts = SerialPort.GetPortNames();
                updateCOMs(availablePorts);

                Thread.Sleep(1000);
            }
        }

        private void log_Thread()
        {
            while (true)
            {
                Thread.Sleep(300);
                if (checkBox2.Checked == true && serialPort1.IsOpen)
                {
                    if (File.Exists(filePath))
                    {
                        using (StreamWriter sw = new StreamWriter(filePath))
                        {
                            sw.Write(fileBuffer);
                        }
                    }
                }
            }
        }

        private void periodicSend_Thread()
        {
            while (true)
            {
                Thread.Sleep(300);
                if (serialPort1.IsOpen)
                {
                    try
                    {
                        serialPort1.Write(textBox1.Text);
                    }
                    catch (System.IO.IOException)
                    {
                        return;
                    }
                    catch { }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
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
                checkBox2.Enabled = false;
                button5.Enabled = false;
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
                checkBox2.Enabled = true;
                button5.Enabled = true;
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
            if (checkBox2.Checked == true)
            {
                fileBuffer += s;
            }
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
            fileBuffer = "";
        }

        private void Form_onClose(object sender, FormClosedEventArgs e)
        {
            tp_thread.Abort();
            l_thread.Abort();
            ps_thread.Abort();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                if (!ps_thread.IsAlive)
                {
                    ps_thread.Start();
                }
                else
                {
                    ps_thread.Resume();
                }
            }
            else
            {
                if (ps_thread.IsAlive)
                {
                    ps_thread.Suspend();
                }
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            DialogResult restult = openFileDialog1.ShowDialog();
            
            if(restult == DialogResult.OK)
            {
                filePath = openFileDialog1.FileName;
                if(filePath.EndsWith(".txt"))
                {
                    label2.Text = filePath;
                }
                else
                {
                    label2.Text = "File must be txt file";
                }                
            }
        }
    }
}
