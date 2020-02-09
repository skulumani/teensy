import serial

ser = serial.Serial('/dev/cu.usbmodem5105671')
print(ser.name)

