#include <cmath>
#include "../headers/Calculator.h"

using namespace std;

Calculator::Calculator() = default;

double Calculator::avg(const int *numbers, const int arraySize) {
    double sum = 0;
    for (int i = 0; i < arraySize; i++) {
        sum += *(numbers + i);
    }
    return std::ceil(sum / arraySize * 100.0) / 100.0;
}

int Calculator::min(const int *numbers, const int arraySize) {
    int min = *(numbers);
    int number;
    for (int i = 1; i < arraySize; i++) {
        number = *(numbers + i);
        if (min > number) {
            min = number;
        }
    }
    return min;
}

int Calculator::max(const int *numbers, const int arraySize) {
    int max = *(numbers);
    int number;
    for (int i = 1; i < arraySize; i++) {
        number = *(numbers + i);
        if (max < number) {
            max = number;
        }
    }
    return max;
}