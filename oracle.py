import urllib.request
import urllib.error
import sys
import binascii
TARGET = 'http://crypto-class.appspot.com/po?er='
#--------------------------------------------------------------
# padding oracle
#--------------------------------------------------------------
class PaddingOracle(object):
    def Padding(self,number):
        if number<16:
            return '0'+hex(number)[2:]
        else:
            return hex(number)[2:]
    def query(self):
        ct="f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4"
        ciphertext=[a[:64],a[32:96],a[64:]]
        pt=''
        for a in ciphertext:
            result=['00']*16
            for j in range(1,17):
                padding=''
                for k in range(1,j):
                    pads=int(result[16-j+k],16)^j

                    padding+=self.Padding(pads)
                #print("paddi:"+padding)

                for i in range(256):
                    if(i==0xc0):
                        #print("bingo")
                        continue
                    #print(a[-32-j*2:-32-(j-1)*2],i,j,hex(int(a[-32-j*2:-32-(j-1)*2],16)^i^j))
                    value=self.Padding(i)
                    q=a[:-32-j*2]+value+padding+a[-32:]
                    target = TARGET + urllib.request.quote(q)    # Create query URL
                    req = urllib.request.Request(target)         # Send HTTP request to server
                    try:
                        f = urllib.request.urlopen(req)
                    except urllib.error.HTTPError as e:          

                        if e.code == 404:
                            print("[+] last "+str(j)+" byte of pt is "+hex(i)) 
                            result[16-j]=self.Padding(i^j)
                            break 
                            # good padding
                    # bad padding
            pt+=''.join(result)
            #print(type(pt),len(pt),pt)
        plaintext=bytes.fromhex(pt)
        ct_to_dec=bytes.fromhex(ct[:96])
        for i,j in zip(plaintext,ct_to_dec):
            print(chr(i^j),end='')

if __name__ == "__main__":
    po = PaddingOracle()
    po.query()  


sad
