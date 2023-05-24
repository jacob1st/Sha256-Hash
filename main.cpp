#include <iostream>

#include "sha256Hash.h"

int main() {
    std::string msg = "Hello World";

    std::vector<std::bitset<32>> hashed = sha256Hash(msg);
    std::cout << "The final Hash value of: '" << msg << "' is..." << std::endl;
    logAnswer(hashed);
}
