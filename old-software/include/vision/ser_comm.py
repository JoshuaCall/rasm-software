import serial
import time
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=5)

time.sleep(2)

while True:
    txt = input()
    ser.write(txt.encode())
    #ser.write('^+030\x00'.encode())
    ser.flush()
    print(ser.read_until().decode())
