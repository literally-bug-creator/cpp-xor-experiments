#include <chrono>
#include <cstdint>
#include <string>

using namespace std;
using TimePoint = chrono::high_resolution_clock::time_point;

double countDuration(TimePoint start, TimePoint end);

void printMeasure(string name, double duration, uint8_t result);
