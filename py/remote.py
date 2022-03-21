import serial
ser = serial.Serial('/dev/ttyUSB0', 115200)

for i in range(3):
    print(ser.readline())

def query(data):
    print(f"commanding: {data}")
    ser.write(data)
    return ser.readline()

print(query(b'volume up\n'))

