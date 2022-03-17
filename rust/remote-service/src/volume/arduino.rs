// Communicate with our Arduino over a serial port

mod arduino {
    use serialport;
    use std::io::Result;

    pub fn send(path: &str, contents: &str) -> std::io::Result<String> {
        let port = serialport::SerialPortBuilder::path(path)
            .baud_rate(115200)
            .open();
        Ok(String::from("example response"))
    }
}
