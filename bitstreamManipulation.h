// returns how many bits in a vector of bits
template <size_t N>
int sizeOfBitstream(const std::vector<std::bitset<N>>& bits){
    return bits.size() * N;
}

// Loops through every chunk of bits in a vector of bits and prints them out separated by a ' '
template <size_t N>
void logBitStream(std::vector<std::bitset<N>>& bits){
    for (std::bitset<N> someBits : bits){
        std::cout << someBits << ' ';
    }
}


// rotates all bits left by a certain amount for any size bitset
template <size_t N>
std::bitset<N> rotateLeft(const std::bitset<N>& bits, int rotateAmount) {
    std::bitset<N> rotatedBits = bits;

    for (int i = 0; i < rotateAmount % N; i++) {
        bool temp = rotatedBits[N - 1];
        rotatedBits <<= 1;
        rotatedBits[0] = temp;
    }

    return rotatedBits;
}

// rotate all bits right by a certain amount
template <size_t N>
std::bitset<N> rotateRight(const std::bitset<N>& bits, int rotateAmount) {
    std::bitset<N> rotatedBits = bits;

    for (int i = 0; i < rotateAmount % N; i++) {
        bool temp = rotatedBits[0];
        rotatedBits >>= 1;
        rotatedBits[rotatedBits.size() - 1] = temp;

    }
    return rotatedBits;
}
