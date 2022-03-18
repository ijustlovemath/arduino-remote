// Communicate with our Arduino over a serial port
use serialport;
use std::io::{Result, Error, ErrorKind};
use std::time::Duration;

pub fn send(path: &str, contents: &[u8]) -> Result<String> {
    let maybe_port = serialport::new(path, 115200)
        .timeout(Duration::from_millis(500))
        .data_bits(serialport::DataBits::Eight)
        .parity(serialport::Parity::None)
        .stop_bits(serialport::StopBits::One)
        .open();
    match maybe_port {
        Ok(mut port) => {
            // Clear out the startup messages from the incoming buffer
            port.clear(serialport::ClearBuffer::Input).expect("couldn't clear input buffer");
            port.clear(serialport::ClearBuffer::Output).expect("couldn't clear output buffer");
            let written = match port.write(contents.into()) {
                Ok(bytes_written) => {
                    bytes_written
                }
                Err(err) => {
                    return Err(err.into());
                }

            };
            println!("wrote {} bytes, message: {}", written, std::str::from_utf8(&contents).unwrap());

            // TODO: assert we wrote all the bytes, but lets just do happy path for now

            // TODO: read when theres data, aka async, but for now lets just sleep
            std::thread::sleep(Duration::from_millis(500));

            let mut buffer = std::vec::Vec::<u8>::new();
            loop {
                match port.read_to_end(&mut buffer) {
                    Ok(bytes_read) => { 
                        if bytes_read == 0 {
                            continue;
                        }
                        println!("got a read!! {:?}", buffer);
                        let s = match std::str::from_utf8(&buffer) {
                            Ok(v) => v,
                            Err(_) => {
                                return Err(
                                    Error::new(
                                        ErrorKind::Other, 
                                        "invalid utf8 response from arduino"
                                    )
                                );
                            }
                        }; 
                        return Ok(s.to_owned());
                    },
                    Err(ref e) if e.kind() == ErrorKind::TimedOut => {
                        continue;
                    },
                    Err(err) => {
                        println!("issue reading from the serial device");
                        return Err(err.into());
                    }
                }
            }
        }
        Err(err) => {
            // Couldn't get the serial port opened
            Err(err.into())
        }
    }
}
