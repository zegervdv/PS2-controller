import serial, sys

s = serial.Serial('/dev/tty.usbserial-AH02E64C')
s.baudrate = 115200

datafile = open('datacapture.txt', 'w')
databuffer = []
count = 0
while True:
    data = s.read()
    databuffer.append(data.encode('hex'))
    if len(databuffer) == 22 and databuffer[0] == '55' and databuffer[1] == '55':
        count += 1
        datafile.write("".join(databuffer))
        datafile.write("\n")
    if count >= 5000:
        break
    if len(databuffer) > 21:
        databuffer.pop(0)
