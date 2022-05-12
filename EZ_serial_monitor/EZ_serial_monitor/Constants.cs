using System.Threading;
using System.IO.Ports;
using System.Windows.Forms;
using System.Security.Cryptography;
using System.IO;

namespace EZ_serial_monitor
{
    static class Constants
    {
        public static readonly int[] baudRates =
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

        public static readonly int defaultTextBuffSize = 10000;
        public static readonly int defaultPeriod_ms = 100;
        public static readonly string storedPassHash = "1452478524424015113731322411689153190191421981611321121852106923646132127551111637496";
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
        StreamWriter cfgFile = new StreamWriter($"{Directory.GetCurrentDirectory()}\\config.cfg");
        SHA256 mySHA256 = SHA256.Create();
        
    }
}
