#ifndef SO2_CALCULATOR_H
#define SO2_CALCULATOR_H

class Calculator {
public:
    Calculator();

    static double avg(const int numbers[], const int arraySize);
    static int max(const int numbers[], const int arraySize);
    static int min(const int numbers[], const int arraySize);
};

#endif
