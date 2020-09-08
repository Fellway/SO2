#ifndef SO2_MONITOR_H
#define SO2_MONITOR_H


#include <cstdlib>

class Monitor {
private:
    int numberOfNumbers;
    int pauseTime;
    int replies;
public:
    explicit Monitor(char *argv[]);
    void init();
};


#endif
