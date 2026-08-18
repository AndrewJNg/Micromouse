import serial

ser = serial.Serial("COM6", 115200)

while True:
    line = ser.readline().decode().strip()
    print(line)