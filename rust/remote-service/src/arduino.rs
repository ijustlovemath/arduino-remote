// Communicate with our Arduino over a serial port
use serialport;

pub fn send(path: &str, contents: &str) -> std::io::Result<String> {
    let port = serialport::new(path, 115200)
        .open();
    Ok(String::from("example response"))
}
