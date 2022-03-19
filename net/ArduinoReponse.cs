namespace net{

public class ArduinoReponse
{
    public String Status { get; set; }

    public String Message { get; set; }
    ArduinoReponse(String status, String message)
    {
        Status = status;
        Message = message;
    }

    public ArduinoReponse(string serialResponse)
    {
        // Happy path only for now

        var kind_index = serialResponse.IndexOf(']');
        // Remove leading [ and trailing ]
        var status = serialResponse.Substring(1, kind_index);
        // Skip the space between status and message
        var message = serialResponse.Substring(kind_index + 2);

        Status = status;
        Message = message;
    }

}
}