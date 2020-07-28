#include "RandomPicker.h"
#include <random>

RandomPicker::RandomPicker() = default;

int RandomPicker::getRandomNumber(int min, int max) {
    std::random_device rdev{};
    static std::default_random_engine engine{rdev()};
    static std::uniform_int_distribution<int> range{min, max};
    return range(engine);
}