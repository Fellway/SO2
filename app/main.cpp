#include <iostream>
#include <Windows.h>
#include <string>
#include <unistd.h>
#include "../utils/Process.h"
#include "RandomPicker.h"
#include "Calculator.h"
#include <list>
#include <strsafe.h>

#define BUFFER_SIZE 1000
#define READER_PROCESS_NAME "Reader"
#define FILE_NAME "File.txt"
#define MAX_THREADS 3

static const char *const CORRECTOR = " ";

using namespace std;

typedef struct CalcData {
    int operation;
    int arrSize;
    int *numbers;
} CalcData, *PCalcData;


DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    PCalcData pDataArray;

    pDataArray = (PCalcData) lpParam;
    switch (pDataArray->operation) {
        case 0:
            Calculator::avg(pDataArray->numbers, pDataArray->arrSize);
            break;
        case 1:
            Calculator::max(pDataArray->numbers, pDataArray->arrSize);
            break;
        case 2:
            Calculator::min(pDataArray->numbers, pDataArray->arrSize);
            break;
        default:
            return -1;
    }
    return 0;
}

int *convertToNumbers(char *numbersAsChars, int *targetArray) {
    std::list<int> listOfNumbers;

    char *cds = strtok(numbersAsChars, CORRECTOR);
    while (cds) {
        listOfNumbers.push_front(atoi(cds));
        cds = strtok(NULL, CORRECTOR);
    }
    std::copy(listOfNumbers.begin(), listOfNumbers.end(), targetArray);
    return targetArray;
}

char *readFile(HANDLE fileHandle, char *buffer) {
    DWORD dwNumberOfByteWritten = 0;
    ReadFile(fileHandle, buffer, BUFFER_SIZE - 1, &dwNumberOfByteWritten, nullptr);
    return buffer;
}

void monitor(int N) {
    HANDLE hThreadArray[MAX_THREADS];
    DWORD dwThreadIdArray[MAX_THREADS];
    PCalcData pDataArray[MAX_THREADS];

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

                for (int i = 0; i < MAX_THREADS; i++) {
                    pDataArray[i] = (PCalcData) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                                                          sizeof(CalcData));
                    pDataArray[i]->numbers = numbers;
                    pDataArray[i]->arrSize = N;
                    pDataArray[i]->operation = i;
                    hThreadArray[i] = CreateThread(NULL, 0, ThreadFunction, pDataArray[i], 0, &dwThreadIdArray[i]);

                    if (hThreadArray[i] == NULL) {
                        ExitProcess(3);
                    }
                }

                WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

                for (int i = 0; i < MAX_THREADS; i++) {
                    CloseHandle(hThreadArray[i]);
                    if (pDataArray[i] != NULL) {
                        HeapFree(GetProcessHeap(), 0, pDataArray[i]);
                        pDataArray[i] = NULL;
                    }
                }
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

int writer(char *argv[]) {
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

int main(int argc, char *argv[]) {
    if (argc == 3 && strcmp(argv[2], READER_PROCESS_NAME) == 0) {
        printf("Hello from %s.\n", argv[2]);
        if (strcmp(argv[2], READER_PROCESS_NAME) == 0) {
            monitor(atoi(argv[1]));
        }
    } else {
        writer(argv);
    }
}
