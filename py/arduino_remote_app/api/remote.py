from datetime import datetime, timezone, timedelta
import serial

ports = ["/dev/ttyUSB0", "/dev/ttyUSB1"]
ser = None
for port in ports:
    try:
        ser = serial.Serial(port, 115200)
        break
    except:
        pass

if ser is None:
    raise ValueError("serial device already in use or doesnt exist")

assert b'foo' == bytes('foo', 'utf-8')

# This part may seem silly, because it could clearly be
# removed from the arduino programming, but without it,
# the first command sent will get no response. This probably
# is because the serial needs to have some buffered data to
# 'sync up' with the reading program, so they're on the same
# page.
startup_messages = 3
for i in range(startup_messages):
    print(ser.readline().decode('utf-8'), end='')

def query(data):
    ser.write((data + '\n').encode('utf-8'))
    response = ser.readline().decode('utf-8').rstrip('\r\n')
    # All responses will look like '[status] message'
    status, message = response[1:].split("] ", 1)
    # Hacky timezone fix, needed to get a semblance of local time
    local_tz = timezone(timedelta(hours=-4.0))
    return dict(status=status
        , message=message
        , utc_time=datetime.utcnow()
        , local_time=datetime.now(local_tz)
        , local_tz=str(local_tz)
    )

#print(query('volume up'))
#print(query('volume down'))

#ser.close()

