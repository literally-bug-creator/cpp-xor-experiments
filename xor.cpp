#include <chrono>
#include <cstdint>
#include <algorithm>
#include <random>
#include <string>
#include <iostream>
#include <memory>

using namespace std;
using TimePoint = chrono::high_resolution_clock::time_point;

void generateByteArray(uint8_t* array, size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 255);

    for (size_t i = 0; i < size; ++i) {
        array[i] = static_cast<uint8_t>(dist(gen));
    }
}

void copyByteArray(const uint8_t* source, uint8_t* destination, size_t size) {
    std::copy(source, source + size, destination);
}

double countDuration(TimePoint start, TimePoint end) {
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration_ns.count() / 1000000.0;
}

void printMeasure(string name, double duration, uint8_t result) {
    cout << name << " duration is - " << duration << " ms, result = " << static_cast<int>(result) << endl;
}

uint8_t simple_xor(const uint8_t* bytes, size_t size) {
    uint8_t result = 0;
    for (size_t i = 0; i < size; i++) {
        result ^= bytes[i];
    }
    return result;
}

void measure_simple_xor(const uint8_t* source, size_t size) {
    std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);
    copyByteArray(source, bytes.get(), size);

    auto start = std::chrono::high_resolution_clock::now();
    uint8_t result = simple_xor(bytes.get(), size);
    auto end = std::chrono::high_resolution_clock::now();

    double duration = countDuration(start, end);
    printMeasure("SimpleXOR", duration, result);
}

uint8_t chunked_xor(const uint8_t* bytes, size_t count) {
    uint8_t result = 0;
    const size_t chunk_size = 16;
    size_t chunks = count / chunk_size;

    for (size_t chunk = 0; chunk < chunks; chunk++) {
        const uint8_t* chunk_start = bytes + chunk * chunk_size;
        for (size_t i = 0; i < chunk_size; i++) {
            result ^= chunk_start[i];
        }
    }

    for (size_t i = chunks * chunk_size; i < count; i++) {
        result ^= bytes[i];
    }

    return result;
}

void measure_chunked_xor(const uint8_t* source, size_t size) {
    std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);
    copyByteArray(source, bytes.get(), size);

    auto start = std::chrono::high_resolution_clock::now();
    uint8_t result = chunked_xor(bytes.get(), size);
    auto end = std::chrono::high_resolution_clock::now();

    double duration = countDuration(start, end);
    printMeasure("ChunkedXOR", duration, result);
}

uint8_t compact_xor(const int freq[256]) {
    uint8_t result = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] & 1) result ^= i;
    }
    return result;
}

void measure_compact_xor(const uint8_t* source, size_t size) {
    std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);
    copyByteArray(source, bytes.get(), size);

    int freq[256] = {0};
    for (size_t i = 0; i < size; i++) freq[bytes[i]]++;
    auto start = std::chrono::high_resolution_clock::now();
    uint8_t result = compact_xor(freq);
    auto end = std::chrono::high_resolution_clock::now();

    double duration = countDuration(start, end);
    printMeasure("CompactXOR", duration, result);
}

uint8_t bit_parallel_xor(const int bit_counts[8]) {
    uint8_t result = 0;
    for (int bit = 0; bit < 8; bit++) {
        if (bit_counts[bit] & 1) {
            result |= (1 << bit);
        }
    }
    return result;
}

void measure_bit_parallel_xor(const uint8_t* source, size_t size) {
    std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);
    copyByteArray(source, bytes.get(), size);

    int freq[256] = {0};
    for (size_t i = 0; i < size; i++) {
        freq[bytes[i]]++;
    }
    int bit_counts[8] = {0};
    for (int value = 0; value < 256; value++) {
        if (freq[value] & 1) {
            for (int bit = 0; bit < 8; bit++) {
                bit_counts[bit] += (value >> bit) & 1;
            }
        }
    }
    auto start = std::chrono::high_resolution_clock::now();
    uint8_t result = bit_parallel_xor(bit_counts);
    auto end = std::chrono::high_resolution_clock::now();

    double duration = countDuration(start, end);
    printMeasure("BitParallelXOR", duration, result);
}

int main() {
    const size_t size = 10000000;
    std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);

    cout << "Generating " << size << " bytes..." << endl;
    generateByteArray(bytes.get(), size);

    cout << "Measuring XOR performance..." << endl;
    measure_simple_xor(bytes.get(), size);
    measure_chunked_xor(bytes.get(), size);
    measure_compact_xor(bytes.get(), size);
    measure_bit_parallel_xor(bytes.get(), size);

    return 0;
}
