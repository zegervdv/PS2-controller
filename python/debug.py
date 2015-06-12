import hid, time
import numpy as np
import matplotlib.pyplot as plt


for d in hid.enumerate(0,0):
    keys = d.keys()
    keys.sort()
    for key in keys:
        print "%s : %s" % (key, d[key])
    print ""

try:
    print "Opening device"
    h = hid.device()
    h.open(0x400, 0x5750)
    print "Manufacturer: %s" % h.get_manufacturer_string()
    arrx = [0] * 10
    arry = [0] * 10
    plt.ion()
    line, = plt.plot(arrx)
    plt.ylim([0, 255])
    plt.xlim([0, 255])
    while True:
        data = h.read(5)
        arrx.append(data[3])
        arry.append(255-data[2])
        print arrx
        arrx.pop(0)
        arry.pop(0)
        line.set_xdata(arrx)
        line.set_ydata(arry)
        plt.draw()
        time.sleep(0.05)
except IOError, ex:
    print ex
    print "Something is wrong"
