using Microsoft.AspNetCore.Mvc;
using System.IO.Ports;
//using RJCP.IO.Ports;
using System.Text;

namespace net.Controllers {

[ApiController]
[Route("/volume/up")]
public class VolumeController : ControllerBase
{

    private readonly ILogger<VolumeController> _logger;

    public VolumeController(ILogger<VolumeController> logger)
    {
        _logger = logger;
    }

    [HttpGet(Name = "up")]
    //public net.ArduinoReponse Get()
    public async Task<string> Get()
    {
        /*
        SerialPort _port = new SerialPort();
        _port.PortName = "/dev/ttyUSB0";
        _port.BaudRate = 115200;
        _port.Parity = Parity.None;
        _port.DataBits = 8;
        _port.StopBits = StopBits.One;
        _port.Handshake = Handshake.RequestToSendXOnXOff;

        _port.ReadTimeout = 100;
        
        string response = "[ERROR] No response received";

        try {
            _port.Open();
            _port.WriteLine("volume up");
            Console.WriteLine("wrote command, sleeping");
            Thread.Sleep(300);
            response = _port.ReadExisting();
            Console.WriteLine("got reponse: '{0}'", response);
        } finally {
            Console.WriteLine("closing port");
            _port.Close();
            Console.WriteLine("port closed");
        }
*/
        //var serial = new SerialPortStream("/dev/ttyUSB0", 115200);
        var serial = new SerialPort("/dev/ttyUSB0", 115200);
        serial.Handshake = Handshake.None;//DtrXOn;
        serial.ReadTimeout = 300;
        serial.Open();
        for(int i = 0; i < 3; i++) {
            string startup = serial.ReadLine();
            Console.WriteLine("[STARTUP] " + startup);
        }
        //serial.Flush();
        //byte[] command = ASCIIEncoding.ASCII.GetBytes("volume up\n");
        //var channel = new CancellationToken();
        //serial.WriteAsync(command, 0, command.Length, channel);

        Console.WriteLine("");
        serial.WriteLine("volume up");
        string response = "jokes";
        Console.WriteLine("attempting to read...");
        //while(!serial.CanRead);
        //string latest = serial.ReadExisting();
        //response = latest;
        //Thread.Sleep(300);
        response = serial.ReadLine();
        /*
        var read_buffer = new byte[256];
        var bytes_read = await serial.ReadAsync(read_buffer, 0, 20);
        Console.WriteLine("read {0} bytes", bytes_read);
        response = Encoding.ASCII.GetString(
            read_buffer
                .Take(bytes_read)
                .ToArray()
        );
        */
        Console.WriteLine("Read '{0}'! attempting to close...", response);
        
        serial.Close();

        /* remember to change the function signature if you change this */         
        return response;//new ArduinoReponse(response);
    }
}
}
