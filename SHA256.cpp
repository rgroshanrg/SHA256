#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include "conversions.h"

#include "functions.h"

#define ADD Function::ADD

std::string HASH0 = "0x6a09e667";
std::string HASH1 = "0xbb67ae85";
std::string HASH2 = "0x3c6ef372";
std::string HASH3 = "0xa54ff53a";
std::string HASH4 = "0x510e527f";
std::string HASH5 = "0x9b05688c";
std::string HASH6 = "0x1f83d9ab";
std::string HASH7 = "0x5be0cd19";

std::string HEXA_CONSTANTS[] = {
   "0x428a2f98", "0x71374491", "0xb5c0fbcf", "0xe9b5dba5", "0x3956c25b", "0x59f111f1", "0x923f82a4", "0xab1c5ed5",
   "0xd807aa98", "0x12835b01", "0x243185be", "0x550c7dc3", "0x72be5d74", "0x80deb1fe", "0x9bdc06a7", "0xc19bf174",
   "0xe49b69c1", "0xefbe4786", "0x0fc19dc6", "0x240ca1cc", "0x2de92c6f", "0x4a7484aa", "0x5cb0a9dc", "0x76f988da",
   "0x983e5152", "0xa831c66d", "0xb00327c8", "0xbf597fc7", "0xc6e00bf3", "0xd5a79147", "0x06ca6351", "0x14292967",
   "0x27b70a85", "0x2e1b2138", "0x4d2c6dfc", "0x53380d13", "0x650a7354", "0x766a0abb", "0x81c2c92e", "0x92722c85",
   "0xa2bfe8a1", "0xa81a664b", "0xc24b8b70", "0xc76c51a3", "0xd192e819", "0xd6990624", "0xf40e3585", "0x106aa070",
   "0x19a4c116", "0x1e376c08", "0x2748774c", "0x34b0bcb5", "0x391c0cb3", "0x4ed8aa4a", "0x5b9cca4f", "0x682e6ff3",
   "0x748f82ee", "0x78a5636f", "0x84c87814", "0x8cc70208", "0x90befffa", "0xa4506ceb", "0xbef9a3f7", "0xc67178f2"
};


class SHA256 {
    public :
        std::string msg;
        SHA256() { }
        void padding(std::string &);
        void block_decomposition(std::string &, std::vector<std::string> &);
        void make_chunks(std::string &, std::vector<std::string> &);
        void hash_computation(std::vector<std::string> &, std::vector<std::string> &);
        std::vector<std::string> hash(std::string);


};

void SHA256::padding(std::string &msg) {
    int len = msg.length();
    msg += "1";
    std::bitset<64> B(len);
    int times = 512 - ((len + 1 + 64)%512);     // check here
    while(times--) msg += "0";
    msg += B.to_string();
    std::cout << msg << "\n";
}

void SHA256::make_chunks(std::string &msg, std::vector<std::string> &chunks) {
    long int len = msg.length();
    for(long int i = 0; i < len; i += 512) {
        chunks.push_back( msg.substr(i, 512) );
    }
}

void SHA256::block_decomposition(std::string &chunk, std::vector<std::string> &blocks) {
    for(int i = 0; i < 16; i++) {
        blocks[i] = chunk.substr((i*32), 32);
    }
    for(int i = 16; i < 64; ++i) {
        blocks[i] = ADD( Function::sigma1(blocks[i-2]), ADD(blocks[i-7], ADD(Function::sigma0(blocks[i-15]), blocks[i-16])) );
    }
}

void SHA256::hash_computation(std::vector<std::string> &blocks, std::vector<std::string> &BIN_CONST) {
    std::string a = HASH0;
    std::string b = HASH1;
    std::string c = HASH2;
    std::string d = HASH3;
    std::string e = HASH4;
    std::string f = HASH5;
    std::string g = HASH6;
    std::string h = HASH7;
    std::string T1, T2;
    for(int i = 0; i < 64; ++i) {
        T1 = ADD(h, ADD(Function::summation1(e), ADD(Function::choice(e, f, g), ADD(BIN_CONST[i], blocks[i]))));
        T2 = ADD(Function::summation0(a), Function::majority(a, b, c));
        h = g;
        g = f;
        f = e;
        e = ADD(d, T1);
        d = c;
        c = b;
        b = a;
        a = ADD(T1, T2);
    }

    HASH0 = ADD(HASH0, a);
    HASH1 = ADD(HASH1, b);
    HASH2 = ADD(HASH2, c);
    HASH3 = ADD(HASH3, d);
    HASH4 = ADD(HASH4, e);
    HASH5 = ADD(HASH5, f);
    HASH6 = ADD(HASH6, g);
    HASH7 = ADD(HASH7, h);

}

std::vector<std::string> SHA256::hash(std::string message) {

    message = Conversion::strToBin(message);
    // message = Conversion::hexToBin("616263");

    HASH0 = Conversion::hexToBin(HASH0);
    HASH1 = Conversion::hexToBin(HASH1);
    HASH2 = Conversion::hexToBin(HASH2);
    HASH3 = Conversion::hexToBin(HASH3);
    HASH4 = Conversion::hexToBin(HASH4);
    HASH5 = Conversion::hexToBin(HASH5);
    HASH6 = Conversion::hexToBin(HASH6);
    HASH7 = Conversion::hexToBin(HASH7);
    std::vector<std::string> BIN_CONST(64);
    for(int i = 0; i < 64; ++i) {
        BIN_CONST[i] = Conversion::hexToBin(HEXA_CONSTANTS[i]);
    }

    padding(message);

    std::vector<std::string> chunks;
    make_chunks(message, chunks);
    std::vector<std::string> blocks(64);
    
    for(std::string &chunk : chunks) {

        block_decomposition(chunk, blocks);
        hash_computation(blocks, BIN_CONST);

    }

    std::vector<std::string> final_hash;
    final_hash.push_back( Conversion::binToHex(HASH0) );
    final_hash.push_back( Conversion::binToHex(HASH1) );
    final_hash.push_back( Conversion::binToHex(HASH2) );
    final_hash.push_back( Conversion::binToHex(HASH3) );
    final_hash.push_back( Conversion::binToHex(HASH4) );
    final_hash.push_back( Conversion::binToHex(HASH5) );
    final_hash.push_back( Conversion::binToHex(HASH6) );
    final_hash.push_back( Conversion::binToHex(HASH7) );

    return final_hash;

}



int main () {
    std::string message = "Hello World!";
    SHA256 sha256;
    std::vector<std::string> hash = sha256.hash(message);

    for(auto i : hash) std::cout << i << " ";
    std::cout << "\n";
}