import serial, time

s = serial.Serial('/dev/tty.usbserial-AH02E64C')
s.baudrate = 115200

datafile = open('datacapture.txt', 'r')
for line in datafile:
    for i in range(len(line)/2):
        char = "%s%s" % (line[2*i],line[2*i+1])
        s.write(char.decode('hex'))
        time.sleep(.05)
