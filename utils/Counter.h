#include <windows.h>

#ifndef SO2_COUNTER_H
#define SO2_COUNTER_H


class Counter {
private:
    double PCFreq = 0.0;
    __int64 counterStart = 0;
public:
    void startCounter();
    double getCounter();
};


#endif //SO2_COUNTER_H
