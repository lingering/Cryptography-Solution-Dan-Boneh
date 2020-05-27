//g++ -g -O2 -std=c++11 -pthread -march=native foo.cpp -o foo -lntl -lgmp -lm
//#include<NTL/ZZ.h>
//#include<NTL/tools.h>
//#include<NTL/
#include<gmpxx.h>
#include<string>
#include<mpfr.h>
#include<unordered_map>
#include<iostream>
#include<chrono>
using namespace std;
int main(void){
   // mpz_t p;
    //ZZ k{"13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171"};
    //ZZ pp{"11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568"};
    const string P{"13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171"};
    const string G{"11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568"};
    const string H{"3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333"};
    //mpz_init(p);
    mpz_class p(P);
    mpz_class g(G);
    mpz_class h(H);
    mpz_class it("0");
    mpz_class result,guess;
    mpz_class constant{"1048576"};    
        

    unordered_map<string,int> HashTable;
    auto start = chrono::system_clock::now();

    for(;it.get_ui()<pow(2,20);it++){
        mpz_powm(result.get_mpz_t(),g.get_mpz_t(),it.get_mpz_t(),p.get_mpz_t());
        mpz_invert(result.get_mpz_t(),result.get_mpz_t(),p.get_mpz_t());
        mpz_mul(result.get_mpz_t(),result.get_mpz_t(),h.get_mpz_t());
        mpz_mod(result.get_mpz_t(),result.get_mpz_t(),p.get_mpz_t());
        HashTable[result.get_str()]=it.get_ui();
        
    }
    
    for(it=0;it.get_ui()<pow(2,20);it++){
        mpz_mul(result.get_mpz_t(),constant.get_mpz_t(),it.get_mpz_t());
        mpz_powm(guess.get_mpz_t(),g.get_mpz_t(),result.get_mpz_t(),p.get_mpz_t());
        if(HashTable.find(guess.get_str())!=HashTable.end()){
            mpz_class product{HashTable[guess.get_str()]},final_result;
            mpz_mul(final_result.get_mpz_t(),constant.get_mpz_t(),it.get_mpz_t());
            mpz_add(final_result.get_mpz_t(),final_result.get_mpz_t(),product.get_mpz_t());
            
            cout<<"found x:"<<final_result.get_mpz_t()<<endl;
            break;
        }
    }
    auto end1 = chrono::system_clock::now();
    auto duration =chrono::duration_cast<chrono::microseconds>(end1-start);
    cout<<"time total:"<<double(duration.count())* chrono::microseconds::period::num/chrono::microseconds::period::den<<"seconds"<<endl;
        

    //unordered_map<mpz_class,long> Hash_Table;
   // cout<<"P:"<<p.get_mpz_t()<<" G:"<<g.get_mpz_t()<<" Result:"<<HashTable[guess.get_str()]<<endl;
    return 0;
}

