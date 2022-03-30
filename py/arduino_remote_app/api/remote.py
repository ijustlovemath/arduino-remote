import datetime
import serial
ser = serial.Serial('/dev/ttyUSB1', 115200)

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
    return dict(status=status
        , message=message
        , utc_time=datetime.datetime.utcnow()
    )

#print(query('volume up'))
#print(query('volume down'))

#ser.close()

