#include <cstdint>
#include <array>

using namespace std;

array<int, 8> count_bits(const uint8_t* bytes, size_t size) {
    int freq[256] = {0};
    for (size_t i = 0; i < size; i++) {
        freq[bytes[i]]++;
    }
    array<int, 8> bit_counts = {0};
    for (int value = 0; value < 256; value++) {
        if (freq[value] & 1) {
            for (int bit = 0; bit < 8; bit++) {
                bit_counts[bit] += (value >> bit) & 1;
            }
        }
    }
    return bit_counts;
}

uint8_t bit_xor(const array<int, 8> bit_counts) {
    uint8_t result = 0;
    for (int bit = 0; bit < 8; bit++) {
        if (bit_counts[bit] & 1) {
            result |= (1 << bit);
        }
    }
    return result;
}
