#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std;

struct Timer {
    chrono::time_point<chrono::system_clock> start, end;

    Timer();
    ~Timer();
};



#endif //TIMER_H
