import serial
encoding = 'utf-8'


ser = serial.Serial(port='/dev/ttyS4', baudrate=9600, timeout=2)


while True:

    try:
        x = ser.readline()
        x = x.decode(encoding)

        with open("serial_data.csv", "a") as f:
            f.write(x)

        print(x)
    except KeyboardInterrupt:
        ser.close()
