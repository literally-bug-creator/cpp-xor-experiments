#include "data.h"
#include <cstddef>
#include <cstdint>
#include <random>

using namespace std;

void generateByteArray(uint8_t* array, size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    for (size_t i = 0; i < size; ++i) {
        array[i] = static_cast<uint8_t>(dist(gen));
    }
}

void copyByteArray(const uint8_t* source, uint8_t* destination, size_t size) {
    std::copy(source, source + size, destination);
}
