// Takes in a string and returns a vector of the 8 bit ASCII representations of each letter
std::vector<std::bitset<8>> convertToBits(std::string msg) {
    std::vector<std::bitset<8>> textAsBinary;
    for (char letter : msg) {
        textAsBinary.push_back(int(letter));
    }
    return textAsBinary;
}

// Pads the bits so that there is exactly 64 less than a multiple of 512
std::vector<std::bitset<8>> padBits(std::vector<std::bitset<8>> bits) {
    // first find how much to pad
    int numBits = sizeOfBitstream(bits);
    int intervalToPad = 512;
    int amountToPad;
    int* pAmountToPad = &amountToPad;
    while(true) {
        if (numBits > (intervalToPad - 64)) {
            intervalToPad += 512;
        } else {
            *pAmountToPad = intervalToPad - 64 - numBits;
            break;
        }
    }

    // Then pad with 1 + that many zeroes
    for (int i = 0; i < (amountToPad / 8); i++) {
        if (i == 0){
            bits.push_back(128);
        } else {
            bits.push_back(0);
        }
    }

    return bits;
}

// Final Padding is based on length
std::vector<std::bitset<8>> padBitsFromLength(std::vector<std::bitset<8>> bits, int bitSize) {
    std::vector<std::bitset<8>> tempVector;
    while (bitSize > 0) {
        tempVector.insert(tempVector.begin(), std::bitset<8>(bitSize & 0xFF));
        bitSize >>= 8;
    }

    for (int i = 8 - tempVector.size(); i > 0; i--){
        bits.push_back(0);
    }

    for (std::bitset<8> byte : tempVector) {
        bits.push_back(byte);
    }

    return bits;
}


// set first 16 Ws to be the 32 bit words from the 512 block
std::vector<std::bitset<32>> prepareFirstSixteen(std::vector<std::bitset<32>> msgScheduler, std::vector<std::bitset<8>> bits) {
    // Each W is size 32
    std::bitset<32> tempBits = {0};
    // We append every 4 bytes (32 bits) from `bits` to `msgScheduler`
    for (int i = 0; i <= 64; i++){
        if (i % 4 == 0 && i > 0) {
            msgScheduler.push_back(tempBits);
            tempBits = std::bitset<32>(0);
        }

        // Set a temp mask equal to 00000...[the next byte from `bits`]
        tempBits = rotateLeft(tempBits, 8);
        std::bitset<32> tempMask = {0};
        for (int index = 0; index < 8; index ++) {
            tempMask[index] = bits[i][index];
        }
        // combine the mask with the tempBits
        tempBits |= tempMask;
    }

    return msgScheduler;
}
