#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <iostream>
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include <cryptopp/files.h>
#include <fstream>
#include<iterator>
using namespace CryptoPP;

#include<string>
void trans(std::string orign,unsigned char *dest){
        std::string k1;
        for(int i=0;i<orign.length()/2;i++){
                k1+=orign[i*2];
                k1+=orign[i*2+1];
                dest[i]=std::stoi(k1,nullptr,16);
                //std::cout<<" "<<k1<<" "<<dest[i]<<std::endl;
                k1.clear();
        }
}
int main (void){
    SHA256 hash;
    std::cout<<"Name:"<<hash.AlgorithmName()<<std::endl;
    std::cout<<"digest size:"<<hash.DigestSize()<<std::endl;
    std::cout<<"block size:"<<hash.BlockSize()<<std::endl;
    HexEncoder encoder(new FileSink(std::cout));
    std::string msg="",digest;
    hash.Update((const byte*)msg.data(),msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);
    std::cout << "Message: " << msg << std::endl;

    std::cout << "Digest: ";
    StringSource(digest, true, new Redirector(encoder));
    std::cout << std::endl;
    digest.clear();

try{
    
    std::ifstream infile("intro.mp4", std::ifstream::binary|std::ifstream::in|std::ifstream::ate);
    size_t size_of_file=infile.tellg();
    
    std::string encoded;
    int size=1024;
    std::string str(size,'\0');
    SHA256 hash;
    for(int i=size_of_file%size;i<=size_of_file;i=i+1024){
        hash=* new SHA256 ;
        infile.seekg(-i,std::ifstream::end);

        //std::cout<<sizeof(dest)<<" "<<dest<<"\n";
        if(i==size_of_file%size){
            infile.read(&str[0],i);
            hash.Update((const byte*)str.data(),i);
            digest.resize(hash.DigestSize());
            hash.Final((byte*)&digest[0]);
            std::cout<<digest.length()<<std::endl;
        }
        else
        {
            infile.read(&str[0],size);
            hash.Update((const byte*)(str+digest).data(),digest.length()+size);
            digest.resize(hash.DigestSize());
            hash.Final((byte*)&digest[0]);
        }
        
}

    StringSource(digest, true, new Redirector(encoder));
    std::cout << std::endl;
    //infile.read(last,128);
    
    //last[10]='\0';
        //infile.seekg(-128,std::ifstream::end);
    char *last="ssadadasdasd\0";
    std::string last1(last);
    StringSource (last1, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	);
        std::cout << "all characters read successfully."<< encoded<<std::endl;
        encoded.clear();
        infile.close();
        }
catch(const CryptoPP::Exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
    
/*
    std::string last1281((std::istreambuf_iterator<char>(infile)),(std::istreambuf_iterator<char>(infile)));
    StringSource ss(last1281, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	);
    std::cout << encoded << std::endl;
    encoded.clear();
    infile.seekg(0,infile.beg);
    //char * last=new char[129];
    //infile.read(last,128);
    //last[128]='\0';
    //std::cout<<last<<std::endl;
    std::string last128(last);
    StringSource (last128, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	);
    std::cout << encoded << std::endl;
    if(infile)       std::cout << "all characters read successfully."<< last<<std::endl;
    else             std::cout << "error: only " << infile.gcount() << " could be read"<< std::endl;
*/
    
    return 0;
}
