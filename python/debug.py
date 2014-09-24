import hid, time

for d in hid.enumerate(0,0):
    keys = d.keys()
    keys.sort()
    for key in keys:
        print "%s : %s" % (key, d[key])
    print ""

try:
    print "Open device"
    h = hid.device()
    h.open(0x400, 0x5750)

    print "Manufacturer: %s" % h.get_manufacturer_string()
    while True:
        data = h.read(5)
        print data
        time.sleep(0.05)
except IOError, ex:
    print ex
    print "Something is wrong"
