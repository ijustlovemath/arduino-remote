# This is just an example to get you started. A typical binary package
# uses this file as the main entry point of the application.
import serial, streams

proc main() =
    #let port = newSerialPort("/dev/ttyUSB0")
        

    let choice = 1
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

    #let port = newSerialPort("/dev/ttyUSB0")
    let port = newSerialStream("/dev/ttyUSB0"
        , 115200
        , Parity.None
        , 8
        , StopBits.One
        , handshake
        , buffered=false
    )

#[
    port.open(115200
        , Parity.None
        , 8
        , StopBits.One
        , handshake
    )
]#

    port.flush()
    port.dtrEnable = false
    port.rtsEnable = false
    defer: close(port)

    port.setTimeouts(1000,100)

    for i in 0..3:
        echo "tryna read"
        echo port.readLine()
    discard port.writeLine("volume up", 100)
    echo "data written, flushing"
    echo "flushed, cleaning up"
    echo port.readLine()


when isMainModule:
    main()
