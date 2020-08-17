//
// Created by mateu on 17.08.2020.
//

#ifndef SO2_PROCESS_H
#define SO2_PROCESS_H
#include <string>
#include <Windows.h>

using namespace std;

class Process {
public:
    static PROCESS_INFORMATION startProcess(char *path, const string &applicationName);
};


#endif //SO2_PROCESS_H
