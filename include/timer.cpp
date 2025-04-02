#include "timer.h"
#include <iostream>

Timer::Timer() {
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    end = std::chrono::high_resolution_clock::now();
    const chrono::duration<double> duration = end-start;
    std::cout << "Elapsed Time: " << duration.count() << "s\n";
}