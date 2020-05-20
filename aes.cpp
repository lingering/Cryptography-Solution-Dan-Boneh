#include <cstring>
#include<iostream>
#include <wmmintrin.h>
#include<string>
#include<stdint.h>
#define cpuid(func,ax,bx,cx,dx)\
    __asm__ __volatile__("cpuid":\
    "=a"(ax),"=b"(bx),"=c"(cx),"=d"(dx):"a"(func));
static __m128i Key_schedule[20];
inline __m128i AES_128_ASSIST(__m128i key,__m128i generate_key){
    generate_key=_mm_shuffle_epi32(generate_key,0xff);
    key=_mm_xor_si128(key,_mm_slli_si128(key,0x4));
    key=_mm_xor_si128(key,_mm_slli_si128(key,0x4));
    key=_mm_xor_si128(key,_mm_slli_si128(key,0x4));
 //   std::cout<<"AES_128_assist"<<std::endl;
    return _mm_xor_si128(key,generate_key);

}
void AES_128_Key_Expansion(unsigned char* key)
                            
{
   // std::cout<<"there"<<std::endl;
    //__m128i Key_schedule[11] ;
    Key_schedule[0]=_mm_loadu_si128((__m128i*)key);
    Key_schedule[1]=AES_128_ASSIST(Key_schedule[0],_mm_aeskeygenassist_si128(Key_schedule[0],0x1));
    Key_schedule[2]=AES_128_ASSIST(Key_schedule[1],_mm_aeskeygenassist_si128(Key_schedule[1],0x2));
    Key_schedule[3]=AES_128_ASSIST(Key_schedule[2],_mm_aeskeygenassist_si128(Key_schedule[2],0x4));
    Key_schedule[4]=AES_128_ASSIST(Key_schedule[3],_mm_aeskeygenassist_si128(Key_schedule[3],0x8));
    Key_schedule[5]=AES_128_ASSIST(Key_schedule[4],_mm_aeskeygenassist_si128(Key_schedule[4],0x10));
    Key_schedule[6]=AES_128_ASSIST(Key_schedule[5],_mm_aeskeygenassist_si128(Key_schedule[5],0x20));
    Key_schedule[7]=AES_128_ASSIST(Key_schedule[6],_mm_aeskeygenassist_si128(Key_schedule[6],0x40));
    Key_schedule[8]=AES_128_ASSIST(Key_schedule[7],_mm_aeskeygenassist_si128(Key_schedule[7],0x80));
    Key_schedule[9]=AES_128_ASSIST(Key_schedule[8],_mm_aeskeygenassist_si128(Key_schedule[8],0x1B));
    Key_schedule[10]=AES_128_ASSIST(Key_schedule[9],_mm_aeskeygenassist_si128(Key_schedule[9],0x36));
  Key_schedule[11] = _mm_aesimc_si128(Key_schedule[9]);
    Key_schedule[12] = _mm_aesimc_si128(Key_schedule[8]);
    Key_schedule[13] = _mm_aesimc_si128(Key_schedule[7]);
    Key_schedule[14] = _mm_aesimc_si128(Key_schedule[6]);
    Key_schedule[15] = _mm_aesimc_si128(Key_schedule[5]);
    Key_schedule[16] = _mm_aesimc_si128(Key_schedule[4]);
    Key_schedule[17] = _mm_aesimc_si128(Key_schedule[3]);
    Key_schedule[18] = _mm_aesimc_si128(Key_schedule[2]);
    Key_schedule[19] = _mm_aesimc_si128(Key_schedule[1]);
    //return Key_schedule;
}
void AES_ENC(unsigned char *plaintext,size_t length,unsigned char*  key,unsigned char* ciphertext,unsigned char* IV){
    __m128i feedback=_mm_loadu_si128 ((__m128i*)IV);
    __m128i m;
    AES_128_Key_Expansion(key);
    __m128i *ks=Key_schedule;
    for(int i=0;i<length;i++){
   	m=_mm_loadu_si128 (&((__m128i*)plaintext)[i]);
        feedback=     _mm_xor_si128(m,feedback);
        feedback=     _mm_xor_si128(feedback,ks[0]);
    //stfeedback::cout<<"after key efeedbackpansion"<<std::endl;
        feedback = _mm_aesenc_si128(feedback, ks[ 1]);
        feedback = _mm_aesenc_si128(feedback, ks[ 2]);
        feedback = _mm_aesenc_si128(feedback, ks[ 3]);
        feedback = _mm_aesenc_si128(feedback, ks[ 4]);
        feedback = _mm_aesenc_si128(feedback, ks[ 5]);
        feedback = _mm_aesenc_si128(feedback, ks[ 6]);
        feedback = _mm_aesenc_si128(feedback, ks[ 7]);
        feedback = _mm_aesenc_si128(feedback, ks[ 8]);
        feedback = _mm_aesenc_si128(feedback, ks[ 9]);
        feedback=_mm_aesenclast_si128(feedback,ks[10]);
	//std::cout<<"after key expansion"<<std::endl;
   // _mm_storeu_si128((__m128i*)ciphertext,m);
    _mm_storeu_si128(&((__m128i*)ciphertext)[i],feedback);
    }    
}
void AES_128_DEC(unsigned char *plaintext,size_t length,unsigned char*  key,unsigned char *ciphertext,unsigned char *IV){
    AES_128_Key_Expansion(key);
    __m128i *ks=Key_schedule,m;
    __m128i feedback=_mm_loadu_si128((__m128i*)IV);
    for(int i=0;i<length;i++){
    __m128i block=_mm_loadu_si128(&((__m128i*)ciphertext)[i]);

    m = _mm_xor_si128(block, ks[ 10]);
    m = _mm_aesdec_si128(m, ks[ 11]);
    m = _mm_aesdec_si128(m, ks[ 12]);
    m = _mm_aesdec_si128(m, ks[ 13]);
    m = _mm_aesdec_si128(m, ks[ 14]);
    m = _mm_aesdec_si128(m, ks[ 15]);
    m = _mm_aesdec_si128(m, ks[ 16]);
    m = _mm_aesdec_si128(m, ks[ 17]);
    m = _mm_aesdec_si128(m, ks[ 18]);
    m = _mm_aesdec_si128(m, ks[ 19]);
    m=_mm_aesdeclast_si128(m,ks[0]);
    m=_mm_xor_si128 (m,feedback);
    //_mm_storeu_si128((__m128i*)plantext,m);
    _mm_storeu_si128 (&((__m128i*)plaintext)[i],m);
    feedback=block;
    }

}
void trans(std::string orign,unsigned char *dest){
	std::string k1;
	std::cout<<orign<<" "<<orign.length()<<std::endl;
	for(int i=0;i<orign.length()/2;i++){
		k1+=orign[i*2];
		k1+=orign[i*2+1];
		dest[i]=std::stoi(k1,nullptr,16);
		k1.clear();
	}
}
size_t padding(std::string &pt){
	size_t len;
	if(pt.length()%32==0){
		len=pt.length()/32+1;
		for(int i=0;i<16;i++){
			pt+="10";
		}
	}
	else{
		len=pt.length()/32;
		static const char* digits = "0123456789ABCDEF";
		int size=16-(pt.length()%32)/2;
		for(int i=0;i<size;i++){
			pt+='0';
			pt+=digits[size];
		}
	}
	return len;
}
void AES_CBC(const unsigned char *in,
                     unsigned char *out,
                     unsigned char ivec[16],
                     unsigned long length,
                     unsigned char *key){
	__m128i feedback;
}
int main(void){
    unsigned char plain[]     = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    unsigned char enc_key[]    = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    unsigned char cipher[]     = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};
    unsigned char *computed_cipher;
    unsigned char Key[16];
    unsigned char IV[16];
    std::string key="140b41b22a29beb4061bda66b6747e14";
   // aes128_load_key(enc_key);
   // std::string iv= "5b68629feb8606f9a6667670b75b38a5";//4ca00ff4c898d61e1edbf1800618fb28;
    std::string iv="4ca00ff4c898d61e1edbf1800618fb28";
    std::string pt="61616262636340676D61696C2E636F6D6A3131";
    std::string ct="28a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81";
    //std::string ct="b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253";
    unsigned char CipherT[ct.length()/2];
    trans(key,Key);
    trans(iv,IV);
    trans(ct,CipherT);
    size_t len=padding(pt);
    unsigned char computed_plain[ct.length()/2],plaintext[(len+1)*16],ciphertext[(len+1)*16];
    trans(pt,plaintext);
    
    //AES_ENC(plaintext,len,Key,ciphertext,IV);
    AES_128_DEC(computed_plain,ct.length()/16,Key,CipherT,IV);

    //std::cout<<"ciphertext:"<<ciphertext<<" "<<sizeof(ciphertext)<<std::endl;
    std::cout<<"computed_plaintext:"<<computed_plain<<std::endl;
 //   if(!memcmp(cipher,computed_cipher,sizeof(cipher))) std::cout<<"encryption success!"<<std::endl;
   // if(!memcmp(plain,computed_plain,sizeof(plain))) std::cout<<"decryption sucess!"<<std::endl;
}
