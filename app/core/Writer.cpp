#include <afxres.h>
#include <cstdio>
#include <unistd.h>
#include "../headers/Writer.h"
#include "../../Variables.h"
#include "../headers/Process.h"
#include "../headers/RandomPicker.h"

Writer::Writer(char **argv) {
    this->numberOfNumbers = atoi(argv[1]);
    this->pauseTime = atoi(argv[2]);
    this->replies = atoi(argv[3]);
}

void Writer::init(char **argv) const {
    PROCESS_INFORMATION information;
    HANDLE hFile;
    DWORD dwNumberOfByteWritten = 0;
    hFile = CreateFile(GENERATOR_FILE_NAME, FILE_WRITE_DATA, 0, nullptr, CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL,
                       nullptr);

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("CreateFile failed (%lu).\n", GetLastError());
        ExitProcess(-1);
    }
    information = Process::startProcess(argv, READER_PROCESS_NAME);
    RandomPicker randomPicker = RandomPicker();
    for (int j = 0; j < this->replies; j++) {
        sleep(this->pauseTime);
        for (int i = 0; i < this->numberOfNumbers; i++) {
            string randomNumber = std::to_string(randomPicker.getRandomNumber(1, 100)) + " ";
            printf("%s ", randomNumber.c_str());
            WriteFile(hFile, randomNumber.c_str(), strlen(randomNumber.c_str()),
                      &dwNumberOfByteWritten,
                      nullptr);
        }
        printf("\n----------------------\n");
    }
    CloseHandle(hFile);
    WaitForSingleObject(information.hProcess, INFINITE);
}

