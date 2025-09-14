#include <cstdint>

using namespace std;

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
