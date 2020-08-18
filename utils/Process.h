#ifndef SO2_PROCESS_H
#define SO2_PROCESS_H
#include <string>
#include <Windows.h>

using namespace std;

class Process {
public:
    static PROCESS_INFORMATION startProcess(char *path, char *N, const string &applicationName);
};


#endif //SO2_PROCESS_H
