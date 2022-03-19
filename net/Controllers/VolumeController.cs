using Microsoft.AspNetCore.Mvc;
using System.IO.Ports;

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
    public net.ArduinoReponse Get()
    {
        SerialPort _port = new SerialPort();
        _port.PortName = "/dev/ttyUSB0";
        _port.BaudRate = 115200;
        _port.Parity = Parity.None;
        _port.DataBits = 8;
        _port.StopBits = StopBits.One;
        _port.Handshake = Handshake.None;

        _port.ReadTimeout = 10;

        _port.Open();



        _port.WriteLine("volume up");

        string response = _port.ReadLine();       

        _port.Close();

        return new ArduinoReponse(response);
    }
}
}
