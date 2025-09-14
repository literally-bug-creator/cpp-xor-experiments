#include <cstdint>

using namespace std;

uint8_t simple_xor(const uint8_t* bytes, size_t size) {
    uint8_t result = 0;
    for (size_t i = 0; i < size; i++) {
        result ^= bytes[i];
    }
    return result;
}
