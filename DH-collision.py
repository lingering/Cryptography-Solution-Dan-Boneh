import gmpy2
from timeit import default_timer as timer
start=timer()
p=gmpy2.mpz(13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171)
g=gmpy2.mpz(11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568)
h=gmpy2.mpz(3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333)
print(p+g)
PA={}
B=gmpy2.mpz(2**20)
index=[]
for i in range(1,2**20):#2**20):
    guess=gmpy2.f_mod( gmpy2.mul(gmpy2.invert( gmpy2.powmod(g,i,p),p),h),p)
    #table[guess%B].append(guess%p)
    #table[guess%B].append(i)
    PA[guess]=i
    
for j in range(1,2**20):
    result=gmpy2.powmod(g,B*j,p)
    if result in PA:
        print("Found X=",PA[result]+j*B)
        break
end=timer()
print(end-start)
