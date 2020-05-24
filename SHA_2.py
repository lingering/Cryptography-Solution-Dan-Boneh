from Crypto.Hash import SHA256
import os
import binascii

#name='intro.mp4'
name="CMakeLists.txt"
size=os.path.getsize(name)
print(size)
f=open(name,'rb')
chunk=size
h=SHA256.new()
h.update(bytearray.fromhex(binascii.hexlify(f.read(chunk)).decode("ascii")))
 
def video_mac():
    name="file"
    size=os.path.getsize(name)
    h=SHA256.new()

    chunk=1024
    with open(name,'rb') as f:
        for pos in range(size-size%chunk,0,-chunk):
            h=h.new()


            #print("current position:"+str(pos))
            f.seek(pos)

            #data=bytearray.fromhex(binascii.hexlify(f.read(chunk)).decode("ascii"))
            
            if pos==size-size%chunk:
                data=bytearray.fromhex(binascii.hexlify(f.read(size%chunk)).decode("ascii"))

                #print('data',binascii.hexlify( data))
                h.update(data)
                digest=h.hexdigest()
                print(len(bytearray.fromhex(digest))," ",len(data),digest)
            else:
                data=bytearray.fromhex(binascii.hexlify(f.read(chunk)).decode("ascii"))

                h.update(data+bytearray.fromhex(digest))
                digest=h.hexdigest()
                #print(len(bytearray.fromhex(digest))," ",len(data),digest)
                

        print("position "+str(pos))
        
        if pos > 0:
            h=h.new()

            f.seek(0)
            data=bytearray.fromhex(binascii.hexlify(f.read(chunk)).decode("ascii"))
            h.update(data+bytearray.fromhex(digest))
            digest=h.hexdigest()
            print(len(bytearray.fromhex(digest)),len(data+bytearray.fromhex(digest)) )

        print("file digset="+digest)


    f.close()
video_mac()