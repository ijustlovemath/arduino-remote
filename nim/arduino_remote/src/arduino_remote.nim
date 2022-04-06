# This is just an example to get you started. A typical binary package
# uses this file as the main entry point of the application.
import serial, streams

proc main() =
    #let port = newSerialPort("/dev/ttyUSB0")
        

    let choice = 3
    var handshake = Handshake.None
    case choice
    of 2:
        handshake = Handshake.XOnXOff
    of 3:
        handshake = Handshake.RequestToSend
    of 4:
        handshake = Handshake.RequestToSendXOnXOff
    else:
        handshake = Handshake.None

    let port = newSerialPort("/dev/ttyUSB1")
#[
    let port = newSerialStream("/dev/ttyUSB1"
        , 115200
        , Parity.None
        , 8
        , StopBits.One
        , handshake
        , buffered=false
    )
]#

    port.open(115200
        , Parity.None
        , 8
        , StopBits.One
        , handshake
    )


    # Set the RTS/DTR lines
    port.dtrEnable = true
    port.rtsEnable = true
    port.iflush()
 #   defer: close(port)

    port.setTimeouts(1000,100)

    #for i in 0..3:
    #    echo "tryna read"
    #    echo port.read(100)
    let command = "volume up\n"
    discard port.write(command) #, len(command))
    echo "data written"
    #port.flush()
    #echo "flushed, cleaning up"
    echo "reading response"
    try:
        echo port.read(100)
    except:
        echo "no data"

    echo "closing port"
    port.close()
#[
    echo "closing port (again)"
    close(port)
]#
when isMainModule:
    main()
