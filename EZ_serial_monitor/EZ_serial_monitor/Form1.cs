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
        public Form1()
        {            
            tp_thread = new Thread(testPorts_Thread);
            l_thread = new Thread(log_Thread);
            ps_thread = new Thread(periodicSend_Thread);
            //string s = algirithm.Create();
            InitializeComponent();
            //checkConfigFile();

            foreach (int baud in Constants.baudRates)
            {
                comboBox2.Items.Add(baud);
            }
            comboBox2.SelectedItem = Constants.baudRates[2];

            trackBar1.Value = Constants.defaultTextBuffSize;
            label3.Text = "Text buffer size " + trackBar1.Value.ToString();

            textBox1.AutoCompleteCustomSource = autoComplete;

            tp_thread.IsBackground = true;
            l_thread.IsBackground = true;
            ps_thread.IsBackground = true;

            tp_thread.Start();
            l_thread.Start();         
           
        }

        private void checkConfigFile()
        {
            throw new NotImplementedException();
        }

        public void updateCOMs(string[] ports)
        {
            comboBox1.BeginInvoke(new Action(() =>
            {
                comboBox1.Items.Clear();
                foreach (string port in ports)
                {
                    comboBox1.Items.Add(port);
                }
            }));

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
                Thread.Sleep(500);
                if (checkBox2.Checked == true && serialPort1.IsOpen)
                {
                    if (File.Exists(filePath))
                    {
                        using (StreamWriter sw = File.AppendText(filePath))
                        {
                            sw.Write(fileBuffer);
                            fileBuffer = "";
                        }
                    }
                }
            }
        }

        private void periodicSend_Thread()
        {
            int period_ms = Constants.defaultPeriod_ms; 
            while (true)
            {
                try
                {
                    if (int.TryParse(s: textBox2.Text, result: out period_ms)) { }
                    period_ms = period_ms < 1 ? 1 : period_ms;
                }
                catch (System.FormatException) { }
                catch { }
                Thread.Sleep(period_ms);
                if (serialPort1.IsOpen)
                {
                    try
                    {
                        serialPort1.Write(textBox1.Text);
                    }
                    catch (System.IO.IOException) { }
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
                richTextBox1.Text += Environment.NewLine + "Sent -> " + textBox1.Text + " " + Environment.NewLine;
                richTextBox1.Text += "Received: -> ";
                autoComplete.Add(textBox1.Text);
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = comboBox1.SelectedItem.ToString();
            }
            catch { }
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            Int32 Int32BaudRate = 0;
            try
            {
                if(int.TryParse(s: comboBox2.SelectedItem.ToString(), result: out Int32BaudRate))
                {
                    serialPort1.BaudRate = Int32BaudRate;
                }
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
                status.Text = "Connected";
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
                status.Text = "Not connected";
                status.BackColor = Color.Red;
                comboBox1.Enabled = true;
                checkBox2.Enabled = true;
                button5.Enabled = true;
            }
        }

        private void updateMsg(object msg)
        {
            richTextBox1.BeginInvoke(new Action(() =>
            {
                richTextBox1.SelectionColor = Color.Green;
                richTextBox1.Text += msg;
                if (richTextBox1.TextLength > trackBar1.Value)
                {
                    richTextBox1.Clear();
                }
            }));
            checkBox2.BeginInvoke(new Action(() =>
            {
                if (checkBox2.Checked == true)
                {
                    fileBuffer += msg;
                }
            }));

        }

        private void onReceive(object sender, SerialDataReceivedEventArgs e)
        {
            string receive = "";
            int timeout = serialPort1.BytesToRead;

            while (timeout > 0)
            {
                try
                {
                    receive += Convert.ToChar(serialPort1.ReadByte());
                    timeout--;
                }
                catch (System.InvalidOperationException) { }
                catch { }
            }
            updateMsg(receive);
            //ThreadPool.QueueUserWorkItem(updateMsg, receive);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            fileBuffer = "";
        }

        private void Form_onClose(object sender, FormClosedEventArgs e)
        {
            //tp_thread.Abort();
            //l_thread.Abort();
            //ps_thread.Abort();
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

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label3.Text = "Text buffer size " + trackBar1.Value.ToString();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            Algo algorithm = new Algo(textBox1.Text, 256);
            string strPass = algorithm.Create();
            if (strPass.Equals(Constants.storedPassHash))
            {
                button2.Enabled = true;
                button3.Enabled = true;
                richTextBox1.AppendText("pass ok");
            }
            Console.WriteLine(strPass);
        }
    }
}
