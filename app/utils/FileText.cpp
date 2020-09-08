#include <windows.h>
#include <sstream>
#include "../headers/FileText.h"

std::string FileText::getHeader(const int numberOfNumbers, const int pauseTime, const int replies) {
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    std::ostringstream oss;
    oss << "Total numbers: " << numberOfNumbers << " | Version: Multithreads \nMachine: "
        << "\n\tNumber of processors: " << siSysInfo.dwNumberOfProcessors
        << "\n\tPage size: " << siSysInfo.dwPageSize
        << "\n\tProcessor type: " << siSysInfo.dwProcessorType
        << "\n\tMinimum app address: " << siSysInfo.lpMinimumApplicationAddress
        << "\n\tMaximum app address: " << siSysInfo.lpMaximumApplicationAddress
        << "\nReplies: " << replies << " | Pause: " << pauseTime << "\n";

    return oss.str();
}

std::string FileText::getTableHeader() {
    return "Nr.\t\tMin\t\tMax\t\tAvg\n";
}

std::string FileText::getTableRow(int rowN, int min, int max, double avg) {
    std::ostringstream oss;
    oss << rowN << ".\t\t" << min << "\t\t" << max << "\t\t" << avg <<"\n";
    return oss.str();
}