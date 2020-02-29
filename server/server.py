import serial

ser = serial.Serial('/dev/cu.usbmodem5105671', 115200)
print(ser.name)

while True:
    print(ser.readline())


