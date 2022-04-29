using System.Threading;
using System.IO.Ports;
using System.Windows.Forms;

namespace EZ_serial_monitor
{
    static class Constants
    {
        public static int[] baudRates =
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

        public static int defaultTextBuffSize = 10000;
        public static int defaultPeriod_ms = 100;
    }

    public partial class Form1 : Form
    {
        private Thread tp_thread;
        private Thread l_thread;
        private Thread ps_thread;
        private string filePath = "";
        private string fileBuffer = "";
        private string[] availablePorts = SerialPort.GetPortNames();
        private AutoCompleteStringCollection autoComplete = new AutoCompleteStringCollection();
    }
}
