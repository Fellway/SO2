#include <iostream>
#include <Windows.h>

#define FILE_PATH "C:\\Users\\Public\\params.txt"

using namespace std;

string getString(char *argv[]);

HANDLE createFile();

bool writeToFile(const string &textToSave, HANDLE hFile);

bool openFileInNotepad();

/**
 * @file LAB1.cpp
 * @author Mateusz Skrzypczyk
 * @date 24.06.2020
 * @brief EX 1 - Systemy operacyjne II, ćwiczenie 1 - LAB
 */
int main(int argc, char *argv[]) {

    string text = getString(argv);
    HANDLE hFile = createFile();

    if (!hFile) {
        cout << "Error creating file" << endl;
        return 1;
    }

    if (!writeToFile(text, hFile)) {
        cout << "Error writing data to file" << endl;
        return 2;
    }

    if (getenv("NOTEPAD")) {
        if (!openFileInNotepad()) {
            cout << "Error creating process" << endl;
            return 3;
        }
    }

    return 0;
}

HANDLE createFile() {
    HANDLE hFile = CreateFile(FILE_PATH, FILE_APPEND_DATA, FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
                              NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    return hFile;
}

bool writeToFile(const string &textToSave, HANDLE hFile) {
    DWORD dwNumberOfByteWritten = 0;

    BOOL bFile = WriteFile(hFile, textToSave.c_str(), strlen(textToSave.c_str()),
                           &dwNumberOfByteWritten,
                           NULL);
    if (!bFile) {
        return FALSE;
    }

    CloseHandle(hFile);
    return TRUE;
}

bool openFileInNotepad() {
    STARTUPINFO startupinfo;
    PROCESS_INFORMATION processInformation;

    ZeroMemory(&startupinfo, sizeof(startupinfo));
    ZeroMemory(&processInformation, sizeof(processInformation));

    startupinfo.cb = sizeof(startupinfo);
    string runCommand = "\"notepad\" ";
    return CreateProcess(0, const_cast<char *>((runCommand + FILE_PATH).c_str()),
                         0, 0, TRUE,
                         CREATE_NEW_PROCESS_GROUP, 0, 0,
                         &startupinfo, &processInformation);
}

string getString(char *argv[]) {
    string text;
    while (*++argv) {
        string s(*argv);
        text += s + "\r\n";
    }
    return text;
}