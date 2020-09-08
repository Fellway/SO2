#ifndef SO2_FILETEXT_H
#define SO2_FILETEXT_H


#include <string>

class FileText {
public:
    static std::string getHeader(int numberOfNumbers, int pauseTime, int replies);
    static std::string getTableHeader();
    static std::string getTableRow(int rowN, int min, int max, double avg);
};


#endif
