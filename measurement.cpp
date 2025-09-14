#include "measurement.h"
#include <cstdint>
#include <chrono>
#include <string>
#include <iostream>

using namespace std;

double countDuration(TimePoint start, TimePoint end) {
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration_ns.count() / 1000000.0;
}

void printMeasure(string name, double duration, uint8_t result) {
    cout << name << " duration is - " << duration << " ms, result = " << static_cast<int>(result) << endl;
}
