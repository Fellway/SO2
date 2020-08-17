#include <iostream>
#include <Windows.h>
#include <string>
#include <unistd.h>
#include "../utils/Process.h"
#include "RandomPicker.h"

#define READER_PROCESS_NAME "Reader"
#define FILE_NAME "File.txt"

using namespace std;

void monitor() {
    DWORD initialSize = 0;
    HANDLE hFile;
    bool lock = true;
    while (lock) {
        if (GetFileAttributes(FILE_NAME) != INVALID_FILE_ATTRIBUTES) {
            hFile = CreateFile(FILE_NAME, GENERIC_READ,
                               0, nullptr, OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hFile != INVALID_HANDLE_VALUE) {
                lock = false;
                DWORD size = GetFileSize(hFile, nullptr);
                if (initialSize == 0) {
                    initialSize = size;
                }
                cout << "Number of characters added to file: " << size - initialSize << endl;
                CloseHandle(hFile);
            }
        } else {
            cout << "File doesn't exist." << endl;
        }
    }
    CloseHandle(hFile);
    system("pause");
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], READER_PROCESS_NAME) == 0) {
        printf("Hello from %s.\n", argv[1]);
        if (strcmp(argv[1], READER_PROCESS_NAME) == 0) {
            monitor();
        }
    } else {
        PROCESS_INFORMATION information;
        HANDLE hFile;
        DWORD dwNumberOfByteWritten = 0;
        hFile = CreateFile(FILE_NAME, FILE_WRITE_DATA, 0, nullptr, OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           nullptr);

        if (hFile == INVALID_HANDLE_VALUE) {
            printf("CreateFile failed (%lu).\n", GetLastError());
            return -1;
        }
        information = Process::startProcess(argv[0], READER_PROCESS_NAME);
        RandomPicker randomPicker = RandomPicker();
        for (int i = 0; i < atoi(argv[1]); i++) {
            string randomNumber = std::to_string(randomPicker.getRandomNumber(1, 100)) + "\n";
            cout << randomNumber << endl;
            WriteFile(hFile, randomNumber.c_str(), strlen(randomNumber.c_str()),
                      &dwNumberOfByteWritten,
                      nullptr);
        }
        CloseHandle(hFile);
        WaitForSingleObject(information.hProcess, INFINITE);
    }
}