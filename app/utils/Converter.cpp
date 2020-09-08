#include <list>
#include <cstring>
#include <cstdlib>
#include "../headers/Converter.h"

int *Converter::convertToNumbers(char *numbersAsChars, int *targetArray) {
    std::list<int> listOfNumbers;
    static const char *const CORRECTOR = " ";
    char *cds = strtok(numbersAsChars, CORRECTOR);
    while (cds) {
        listOfNumbers.push_front(atoi(cds));
        cds = strtok(NULL, CORRECTOR);
    }
    std::copy(listOfNumbers.begin(), listOfNumbers.end(), targetArray);
    return targetArray;
}
