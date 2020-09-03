#include <iostream>
#include "Calculator.h"

using namespace std;

Calculator::Calculator() = default;

void Calculator::avg(const int *numbers, const int arraySize) {
    double sum = 0;
    for (int i =0; i<arraySize; i++) {
        sum += *(numbers + i);
    }
    printf("Avg of given numbers is: %.2f\n", sum/arraySize);
}
