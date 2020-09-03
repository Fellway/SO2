#include "RandomPicker.h"
#include <random>
#include <ctime>

RandomPicker::RandomPicker() {
    srand(time(NULL));
};

int RandomPicker::getRandomNumber(int min, int max) {
    return rand() % max + min;
}