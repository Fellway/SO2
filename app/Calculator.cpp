#include <iostream>
#include "Calculator.h"

using namespace std;

Calculator::Calculator() = default;

void Calculator::avg(const int *numbers, const int arraySize) {
    double sum = 0;
    for (int i = 0; i < arraySize; i++) {
        sum += *(numbers + i);
    }
    printf("Avg of given numbers is: %.2f\n", sum / arraySize);
}

void Calculator::min(const int *numbers, const int arraySize) {
    int min = *(numbers);
    int number;
    for (int i = 1; i < arraySize; i++) {
        number = *(numbers + i);
        if (min > number) {
            min = number;
        }
    }
    printf("Min of given numbers is: %d\n", min);
}

void Calculator::max(const int *numbers, const int arraySize) {
    int max = *(numbers);
    int number;
    for (int i = 1; i < arraySize; i++) {
        number = *(numbers + i);
        if (max < number) {
            max = number;
        }
    }
    printf("Max of given numbers is: %d\n", max);
}