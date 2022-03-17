// Communicate with our Arduino over a serial port
use serialport;
use std::io::{Result, Error, ErrorKind};

pub fn send(path: &str, contents: &[u8]) -> Result<String> {
    let maybe_port = serialport::new(path, 115200)
        .open();
    match maybe_port {
        Ok(mut port) => {
            let _written = match port.write(contents.into()) {
                Ok(bytes_written) => {
                    bytes_written
                }
                Err(err) => {
                    return Err(err.into());
                }

            };
            // TODO: assert we wrote all the bytes, but lets just do happy path for now
            let mut buffer = std::vec::Vec::<u8>::new();
            match port.read(&mut buffer) {
                Ok(_) => {
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
                    Ok(s.to_owned())
                }
                Err(err) => {
                    Err(err.into())
                }
            }
        }
        Err(err) => {
            Err(err.into())
        }
    }
}
