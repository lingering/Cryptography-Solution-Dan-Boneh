from oracle import *
import sys
import binascii
if len(sys.argv) < 2:
    print "Usage: python sample.py <filename>"
    sys.exit(-1)

f = open(sys.argv[1])
data = f.read()
f.close()
print(len(data))
Oracle_Connect()

tag = Mac(data[:32], 32)
m3=binascii.hexlify(data[32:48])
print(m3)
s3=bytearray.fromhex('e7b1a8215f655ebe2ea4edf0d13394c9')
cc= s3+data[48:]
print(len(cc))
tag2=Mac(cc,32)
print(binascii.hexlify(tag2))
ret = Vrfy(data, len(data), tag2)
print
print ret
if (ret==1):
    print "Message verified successfully!"
else:
    print "Message verification failed."

Oracle_Disconnect()
