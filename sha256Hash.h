#include <bitset>
#include <string>
#include <vector>

#include "bitstreamManipulation.h"
#include "hashComputation.h"
#include "hashPreprocess.h"

std::vector<std::bitset<32>> sha256Hash(std::string msg) {
    // Initialize Important variables (I didn't need the pointers for each of the constants, but I was playing around with them and the -> operator)
    std::bitset<32> h0(0x6a09e667);
    std::bitset<32> h1(0xbb67ae85);
    std::bitset<32> h2(0x3c6ef372);
    std::bitset<32> h3(0xa54ff53a);
    std::bitset<32> h4(0x510e527f);
    std::bitset<32> h5(0x9b05688c);
    std::bitset<32> h6(0x1f83d9ab);
    std::bitset<32> h7(0x5be0cd19);

    std::bitset<32>* pH0 = &h0;
    std::bitset<32>* pH1 = &h1;
    std::bitset<32>* pH2 = &h2;
    std::bitset<32>* pH3 = &h3;
    std::bitset<32>* pH4 = &h4;
    std::bitset<32>* pH5 = &h5;
    std::bitset<32>* pH6 = &h6;
    std::bitset<32>* pH7 = &h7;


    std::vector<std::bitset<32>> constants = {std::bitset<32>(0x428a2f98), std::bitset<32>(0x71374491), std::bitset<32>(0xb5c0fbcf), std::bitset<32>(0xe9b5dba5), std::bitset<32>(0x3956c25b), std::bitset<32>(0x59f111f1), std::bitset<32>(0x923f82a4), std::bitset<32>(0xab1c5ed5),
                       std::bitset<32>(0xd807aa98), std::bitset<32>(0x12835b01), std::bitset<32>(0x243185be), std::bitset<32>(0x550c7dc3), std::bitset<32>(0x72be5d74), std::bitset<32>(0x80deb1fe), std::bitset<32>(0x9bdc06a7), std::bitset<32>(0xc19bf174),
                       std::bitset<32>(0xe49b69c1), std::bitset<32>(0xefbe4786), std::bitset<32>(0x0fc19dc6), std::bitset<32>(0x240ca1cc), std::bitset<32>(0x2de92c6f), std::bitset<32>(0x4a7484aa), std::bitset<32>(0x5cb0a9dc), std::bitset<32>(0x76f988da),
                       std::bitset<32>(0x983e5152), std::bitset<32>(0xa831c66d), std::bitset<32>(0xb00327c8), std::bitset<32>(0xbf597fc7), std::bitset<32>(0xc6e00bf3), std::bitset<32>(0xd5a79147), std::bitset<32>(0x06ca6351), std::bitset<32>(0x14292967),
                       std::bitset<32>(0x27b70a85), std::bitset<32>(0x2e1b2138), std::bitset<32>(0x4d2c6dfc), std::bitset<32>(0x53380d13), std::bitset<32>(0x650a7354), std::bitset<32>(0x766a0abb), std::bitset<32>(0x81c2c92e), std::bitset<32>(0x92722c85),
                       std::bitset<32>(0xa2bfe8a1), std::bitset<32>(0xa81a664b), std::bitset<32>(0xc24b8b70), std::bitset<32>(0xc76c51a3), std::bitset<32>(0xd192e819), std::bitset<32>(0xd6990624), std::bitset<32>(0xf40e3585), std::bitset<32>(0x106aa070),
                       std::bitset<32>(0x19a4c116), std::bitset<32>(0x1e376c08), std::bitset<32>(0x2748774c), std::bitset<32>(0x34b0bcb5), std::bitset<32>(0x391c0cb3), std::bitset<32>(0x4ed8aa4a), std::bitset<32>(0x5b9cca4f), std::bitset<32>(0x682e6ff3),
                       std::bitset<32>(0x748f82ee), std::bitset<32>(0x78a5636f), std::bitset<32>(0x84c87814), std::bitset<32>(0x8cc70208), std::bitset<32>(0x90befffa), std::bitset<32>(0xa4506ceb), std::bitset<32>(0xbef9a3f7), std::bitset<32>(0xc67178f2)};

    // Preprocess the msg. Convert to bits, and pad it to be a multiple of 512
    std::vector<std::bitset<8>> bits = convertToBits(msg);
    int original_size = sizeOfBitstream(bits);
    bits = padBits(bits);
    bits = padBitsFromLength(bits, original_size);
    int nBlocks = sizeOfBitstream(bits) / 512;

    // The computations to run on each of the N blocks
    for (int i = 0; i < nBlocks; i++){
        std::vector<std::bitset<32>> messageScheduler;
        // prepare the message scheduler W0-63
        messageScheduler = prepareFirstSixteen(messageScheduler, bits);
        for (int wSub = 16; wSub < 64; wSub ++) {
            unsigned long int addition = smallSigma1(messageScheduler[wSub - 2]).to_ullong() + messageScheduler[wSub - 7].to_ullong() + smallSigma0(messageScheduler[wSub - 15]).to_ullong() + messageScheduler[wSub - 16].to_ullong();
            messageScheduler.push_back(std::bitset<32>(addition % 4294967296));
        }

        // some computations to mix up the bits for the hash
        std::bitset<32> a = std::bitset<32>(*pH0);
        std::bitset<32> b = std::bitset<32>(*pH1);
        std::bitset<32> c = std::bitset<32>(*pH2);
        std::bitset<32> d = std::bitset<32>(*pH3);
        std::bitset<32> e = std::bitset<32>(*pH4);
        std::bitset<32> f = std::bitset<32>(*pH5);
        std::bitset<32> g = std::bitset<32>(*pH6);
        std::bitset<32> h = std::bitset<32>(*pH7);

        for (int t = 0; t < 64; t++){
            unsigned long int t1Addition = h.to_ullong() + bigSigma1(e).to_ullong() + choose(e, f, g).to_ullong() + constants[t].to_ullong() + messageScheduler[t].to_ullong();
            std::bitset<32> T1 = std::bitset<32>(t1Addition % 4294967296);

            unsigned long int t2Addition = bigSigma0(a).to_ullong() + maj(a, b, c).to_ulong();
            std::bitset<32> T2 = std::bitset<32>(t2Addition % 4294967296);

            h = g;
            g = f;
            f = e;
            e = std::bitset<32>((d.to_ullong() + T1.to_ullong()) % 4294967296);
            d = c;
            c = b;
            b = a;
            a = std::bitset<32>((T1.to_ullong() + T2.to_ullong()) % 4294967296);
        }

        *pH0 = std::bitset<32>((pH0->to_ullong() + a.to_ullong()) % 4294967296);
        *pH1 = std::bitset<32>((pH1->to_ullong() + b.to_ullong()) % 4294967296);
        *pH2 = std::bitset<32>((pH2->to_ullong() + c.to_ullong()) % 4294967296);
        *pH3 = std::bitset<32>((pH3->to_ullong() + d.to_ullong()) % 4294967296);
        *pH4 = std::bitset<32>((pH4->to_ullong() + e.to_ullong()) % 4294967296);
        *pH5 = std::bitset<32>((pH5->to_ullong() + f.to_ullong()) % 4294967296);
        *pH6 = std::bitset<32>((pH6->to_ullong() + g.to_ullong()) % 4294967296);
        *pH7 = std::bitset<32>((pH7->to_ullong() + h.to_ullong()) % 4294967296);

        // Instead of actually breaking the msg up into N blocks, I just remove 512 bits (64 bytes) every run through.
        std::vector<std::bitset<8>> temporaryVector;
        for (int toCopy = 64; toCopy < bits.size(); toCopy++){
            temporaryVector.push_back(bits[toCopy]);
        }
        bits = temporaryVector;
    }

    // returns a vector of 8 32 bit words that need to be merged to make up the hash
    std::vector<std::bitset<32>> answer = {(*pH0), (*pH1), (*pH2), (*pH3), (*pH4), (*pH5), (*pH6), (*pH7)};
    return answer;
}

void logAnswer(std::vector<std::bitset<32>> answer) {
    // doesn't print out 01, but rather 1. If you want to include iomanip and use std::setw(2) and std::setfill('0') you can.
    std::cout << std::hex << answer[0].to_ullong() << answer[1].to_ullong() << answer[2].to_ullong() << answer[3].to_ullong() << answer[4].to_ullong() << answer[5].to_ullong() << answer[6].to_ullong() << answer[7].to_ullong();
}
