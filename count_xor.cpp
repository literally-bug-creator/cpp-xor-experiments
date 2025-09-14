#include <cstdint>
#include <array>

using namespace std;

array<int, 256> count_freq(const uint8_t* bytes, size_t size) {
    array<int, 256> freq = {0};
    for (size_t i = 0; i < size; i++) freq[bytes[i]]++;
    return freq;
}

uint8_t count_xor(const int freq[256]) {
    uint8_t result = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] & 1) result ^= i;
    }
    return result;
}
