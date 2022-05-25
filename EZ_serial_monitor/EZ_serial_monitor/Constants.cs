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
        public static readonly string storedPassHash = "1423724DF0A92457205342D4CBB39DC629E7BBCE1BFF4C7829594B9CA6A21EAB3B3F3EF9909BB68478A7BAD0A99791382F5F464931D66AA4D4A55213DB63EDBD1C1DDDD8EF1985D7B5307BED19302C954B7BBED33A962E60AE71A46AF5BB46B484DA5BDBE930CE68C861183A35D7CF30AF12D88E68C0321A1869FE337B94567F4E82AF8BE7A86C6FAE63157F29C193DFBDDC269287147EDABE2B4EB0424D4C8C675651E6C01EDBE6CF61C16D1721EB84467FA5F18AEF2D4046DAE76CEEC9D9F944F257FBBDB80CF7E3C1380E919C404197AF83EA3B887950959EE4A644B467D065A7D8B1E28143B3318712CEFA9EBBD5CA34AE1A2CB92BDFD5637B";
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
        //SHA256 mySHA256 = SHA256.Create();
    }
}
