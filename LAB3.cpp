/**
 * @file LAB3.cpp
 * @author Mateusz Skrzypczyk
 * @date 28.06.2020
 * @brief EX 2 - Systemy operacyjne II, ćwiczenie 2 - LAB
 */

#include <iostream>
#include <Windows.h>
#include <string>

#define FILE_NAME "log.txt"
#define MONITOR_PROCESS_NAME "Monitor"
#define WRITER_PROCESS_NAME "Writer"

using namespace std;

void startProcess(char *path, const string &applicationName) {

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
}

int writer() {
    DWORD dwNumberOfByteWritten = 0;
    string userInput;
    while (true) {
        HANDLE hFile = CreateFile(FILE_NAME, FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL,
                                  nullptr);

        if (hFile == INVALID_HANDLE_VALUE) {
            printf("CreateFile failed (%lu).\n", GetLastError());
            return -1;
        }
        getline(cin, userInput);
        WriteFile(hFile, userInput.c_str(), strlen(userInput.c_str()),
                  &dwNumberOfByteWritten,
                  nullptr);
    }
}

int monitor() {
    DWORD initialSize = NULL;
    while (true) {
        if (GetFileAttributes(FILE_NAME) != INVALID_FILE_ATTRIBUTES) {
            HANDLE hFile = CreateFile(FILE_NAME, GENERIC_READ,
                                      FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
                                      FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hFile == INVALID_HANDLE_VALUE) {
                printf("CreateFile failed (%lu).\n", GetLastError());
                return -1;
            }
            DWORD size = GetFileSize(hFile, nullptr);
            if (initialSize == NULL) {
                initialSize = size;
            }
            cout << "Number of characters added to file: " << size - initialSize << endl;
        } else {
            cout << "File doesn't exist." << endl;
        }
        Sleep(5000);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        printf("Hello from %s.\n", argv[1]);
        if (strcmp(argv[1], MONITOR_PROCESS_NAME) == 0) {
            monitor();
        } else if (strcmp(argv[1], WRITER_PROCESS_NAME) == 0) {
            writer();
        }
    } else {
        startProcess(argv[0], WRITER_PROCESS_NAME);
        startProcess(argv[0], MONITOR_PROCESS_NAME);
    }
}

