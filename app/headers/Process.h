#ifndef SO2_PROCESS_H
#define SO2_PROCESS_H
#include <string>
#include <windows.h>

using namespace std;

class Process {
public:
    static PROCESS_INFORMATION startProcess(char *argv[], const string &applicationName);
};


#endif
