#ifndef SO2_CALCULATOR_H
#define SO2_CALCULATOR_H

class Calculator {
public:
    Calculator();

    static void avg(const int numbers[], const int arraySize);
    static void max(const int numbers[], const int arraySize);
    static void min(const int numbers[], const int arraySize);
};

#endif