#include <iostream>
#include <Windows.h>
#include <string>
#include <unistd.h>
#include "../utils/Process.h"
#include "RandomPicker.h"
#include "Calculator.h"
#include <list>

#define BUFFER_SIZE 1000
#define READER_PROCESS_NAME "Reader"
#define FILE_NAME "File.txt"

static const char *const CORRECTOR = " ";

using namespace std;

int* convertToNumbers(char *numbersAsChars, int *targetArray) {
    std::list<int> listOfNumbers;

    char *cds = strtok(numbersAsChars, CORRECTOR);
    while (cds) {
        listOfNumbers.push_front(atoi(cds));
        cds = strtok(NULL, CORRECTOR);
    }
    std::copy(listOfNumbers.begin(), listOfNumbers.end(), targetArray);
    cout << targetArray[0] <<endl;
    return targetArray;
}

char *readFile(HANDLE fileHandle, char *buffer) {
    DWORD dwNumberOfByteWritten = 0;
    ReadFile(fileHandle, buffer, BUFFER_SIZE - 1, &dwNumberOfByteWritten, nullptr);
    return buffer;
}

void monitor(int N) {
    char readBuffer[BUFFER_SIZE] = {0};
    int numbers[BUFFER_SIZE] = {0};
    HANDLE hFile;
    bool lock = true;
    while (lock) {
        if (GetFileAttributes(FILE_NAME) != INVALID_FILE_ATTRIBUTES) {
            hFile = CreateFile(FILE_NAME, GENERIC_READ,
                               0, nullptr, OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hFile != INVALID_HANDLE_VALUE) {
                lock = false;
                readFile(hFile, readBuffer);
                convertToNumbers(readBuffer, numbers);
                Calculator::avg(numbers, N);
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
    if (argc == 3 && strcmp(argv[2], READER_PROCESS_NAME) == 0) {
        printf("Hello from %s.\n", argv[2]);
        if (strcmp(argv[2], READER_PROCESS_NAME) == 0) {
            monitor(atoi(argv[1]));
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
        information = Process::startProcess(argv[0], argv[1], READER_PROCESS_NAME);
        RandomPicker randomPicker = RandomPicker();
        for (int i = 0; i < atoi(argv[1]); i++) {
            string randomNumber = std::to_string(randomPicker.getRandomNumber(1, 100)) + CORRECTOR;
            WriteFile(hFile, randomNumber.c_str(), strlen(randomNumber.c_str()),
                      &dwNumberOfByteWritten,
                      nullptr);
        }
        CloseHandle(hFile);
        WaitForSingleObject(information.hProcess, INFINITE);
    }
}
