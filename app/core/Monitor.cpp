#include <windef.h>
#include <cstdio>
#include "../headers/Monitor.h"
#include "../headers/Counter.h"
#include "../../Variables.h"
#include "../headers/FileText.h"
#include "../headers/Calculator.h"
#include "../headers/Converter.h"
#include <unistd.h>

Monitor::Monitor(char **argv) {
    this->numberOfNumbers = atoi(argv[1]);
    this->pauseTime = atoi(argv[2]);
    this->replies = atoi(argv[3]);
}

typedef struct CalcResult {
    double avg;
    int max;
    int min;
} CalcResult, *PCalcResult;

typedef struct CalcData {
    int operation;
    int arrSize;
    int *numbers;
    PCalcResult calcResult;
} CalcData, *PCalcData;

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    PCalcData pDataArray;
    pDataArray = (PCalcData) lpParam;
    switch (pDataArray->operation) {
        case 0:
            pDataArray->calcResult->avg = Calculator::avg(pDataArray->numbers, pDataArray->arrSize);
            break;
        case 1:
            pDataArray->calcResult->max = Calculator::max(pDataArray->numbers, pDataArray->arrSize);
            break;
        case 2:
            pDataArray->calcResult->min = Calculator::min(pDataArray->numbers, pDataArray->arrSize);
            break;
        default:
            return -1;
    }
    return 0;
}

void Monitor::init() {
    DWORD dwNumberOfByteWrittenSave = 0;
    DWORD dwNumberOfByteWrittenRead = 0;
    HANDLE hThreadArray[MAX_THREADS];
    DWORD dwThreadIdArray[MAX_THREADS];
    PCalcData pDataArray[MAX_THREADS];
    int numbers[BUFFER_SIZE] = {0};
    char readBuffer[BUFFER_SIZE] = {0};
    int rangedNumbers[BUFFER_SIZE] = {0};
    Counter counter;
    CalcResult calcResult;
    HANDLE hGeneratorFile;
    HANDLE hMonitorFile;
    bool lock = true;

    printf("Waiting for access to file... Please wait!\n");
    counter.startCounter();
    while (lock) {
        if (GetFileAttributes(GENERATOR_FILE_NAME) != INVALID_FILE_ATTRIBUTES) {
            hGeneratorFile = CreateFile(GENERATOR_FILE_NAME, GENERIC_READ,
                                        0, nullptr, OPEN_EXISTING,
                                        FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hGeneratorFile != INVALID_HANDLE_VALUE) {
                lock = false;
                hMonitorFile = CreateFile(MONITOR_FILE_NAME, FILE_APPEND_DATA, 0, nullptr, CREATE_ALWAYS,
                                          FILE_ATTRIBUTE_NORMAL,
                                          nullptr);

                std::string header = FileText::getHeader(this->numberOfNumbers, this->pauseTime, this->replies);
                std::string tableHeader = FileText::getTableHeader();

                WriteFile(hMonitorFile, header.c_str(), strlen(header.c_str()), nullptr, nullptr);
                WriteFile(hMonitorFile, tableHeader.c_str(), strlen(tableHeader.c_str()), &dwNumberOfByteWrittenSave,
                          nullptr);
                ReadFile(hGeneratorFile, readBuffer, BUFFER_SIZE - 1, &dwNumberOfByteWrittenRead, nullptr);

                Converter::convertToNumbers(readBuffer, numbers);

                for (int j = 0; j < this->replies; j++) {
                    for (int k = 0; k < this->numberOfNumbers; k++) {
                        rangedNumbers[k] = numbers[j * this->numberOfNumbers + k];
                    }
                    for (int i = 0; i < MAX_THREADS; i++) {
                        pDataArray[i] = (PCalcData) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                                                              sizeof(CalcData));
                        pDataArray[i]->numbers = rangedNumbers;
                        pDataArray[i]->arrSize = this->numberOfNumbers;
                        pDataArray[i]->operation = i;
                        pDataArray[i]->calcResult = &calcResult;
                        hThreadArray[i] = CreateThread(NULL, 0, ThreadFunction, pDataArray[i], 0, &dwThreadIdArray[i]);

                        if (hThreadArray[i] == NULL) {
                            ExitProcess(3);
                        }
                    }

                    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

                    std::string tableRow = FileText::getTableRow(j, calcResult.min, calcResult.max, calcResult.avg);
                    WriteFile(hMonitorFile, tableRow.c_str(), strlen(tableRow.c_str()), &dwNumberOfByteWrittenSave, nullptr);

                    for (int i = 0; i < MAX_THREADS; i++) {
                        CloseHandle(hThreadArray[i]);
                        if (pDataArray[i] != NULL) {
                            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
                            pDataArray[i] = NULL;
                        }
                    }
                }
                CloseHandle(hMonitorFile);
            }
        } else {
            printf("File doesn't exist.\n");
        }
    }
    printf("Execution time: %f,\n", counter.getCounter());
    sleep(10);
    CloseHandle(hGeneratorFile);
}


