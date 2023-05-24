// Calculate the maj(a, b, c) for three bitsets
template <size_t N>
std::bitset<N> maj(const std::bitset<N>& a, const std::bitset<N>& b, const std::bitset<N>& c) {
    std::bitset<N> answer;
    for (int i = 0; i < N; i ++){
        if (a[i] + b[i] + c[i] > 1) {
            answer[i] = 1;
        }
    }
    return answer;
}

// Calculate Choose(e, f, g)
template <size_t N>
std::bitset<N> choose(const std::bitset<N>& e, const std::bitset<N>& f, const std::bitset<N>& g) {
    std::bitset<N> answer;
    for (int i = 0; i < N; i ++){
        if (e[i]) {
            answer[i] = f[i];
        } else {
            answer[i] = g[i];
        }
    }
    return answer;
}

// 4 functions defined to shift around bits then addition mod 2 them
std::bitset<32> smallSigma0 (std::bitset<32> w) {
    std::bitset<32> x = rotateRight(w, 7);
    std::bitset<32> y = rotateRight(w, 18);
    std::bitset<32> z = w >> 3;
    std::bitset<32> answer;

    for (int i = 0; i < 32; i++){
        answer[i] = (x[i] + y[i] + z[i]) % 2;
    }

    return answer;
}

std::bitset<32> smallSigma1 (std::bitset<32> w) {
    std::bitset<32> x = rotateRight(w, 17);
    std::bitset<32> y = rotateRight(w, 19);
    std::bitset<32> z = w >> 10;
    std::bitset<32> answer;

    for (int i = 0; i < 32; i++){
        answer[i] = (x[i] + y[i] + z[i]) % 2;
    }

    return answer;
}

std::bitset<32> bigSigma0 (std::bitset<32> w) {
    std::bitset<32> x = rotateRight(w, 2);
    std::bitset<32> y = rotateRight(w, 13);
    std::bitset<32> z = rotateRight(w, 22);
    std::bitset<32> answer;

    for (int i = 0; i < 32; i++){
        answer[i] = (x[i] + y[i] + z[i]) % 2;
    }

    return answer;
}

std::bitset<32> bigSigma1 (std::bitset<32> w) {
    std::bitset<32> x = rotateRight(w, 6);
    std::bitset<32> y = rotateRight(w, 11);
    std::bitset<32> z = rotateRight(w, 25);
    std::bitset<32> answer;

    for (int i = 0; i < 32; i++){
        answer[i] = (x[i] + y[i] + z[i]) % 2;
    }

    return answer;
}
