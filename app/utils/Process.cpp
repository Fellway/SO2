#include "../headers/Process.h"
#include <windows.h>
#include <string>
using namespace std;

PROCESS_INFORMATION Process::startProcess(char *argv[], const string &applicationName) {
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInformation;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&processInformation, sizeof(processInformation));

    startupInfo.cb = sizeof(startupInfo);
    string appPath(argv[0]);
    string pathWithParam = appPath + " " + argv[1] + " " + argv[2] + " " + argv[3] + " " + applicationName;

    if (!CreateProcessA(appPath.c_str(),
                        const_cast<char *>(pathWithParam.c_str()),
                        nullptr,
                        nullptr,
                        TRUE,
                        CREATE_NEW_CONSOLE,
                        nullptr,
                        nullptr,
                        &startupInfo,
                        &processInformation)
            ) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
    }
    return processInformation;
}
