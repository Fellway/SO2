//
// Created by mateu on 17.08.2020.
//

#include "Process.h"
#include <Windows.h>
#include <string>

using namespace std;

PROCESS_INFORMATION Process::startProcess(char *path, const string &applicationName) {
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInformation;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&processInformation, sizeof(processInformation));

    startupInfo.cb = sizeof(startupInfo);
    string appPath(path);
    string pathWithParam = appPath + " " + applicationName;

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
