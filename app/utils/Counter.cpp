#include <iostream>
#include "../headers/Counter.h"

using namespace std;

void Counter::startCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li)) {
        cout << "QueryPerformanceFrequency failed!\n";
        return;
    }

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    counterStart = li.QuadPart;
}

double Counter::getCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - counterStart) / PCFreq;
}

