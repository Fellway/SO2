#include "RandomPicker.h"
#include <iostream>

using namespace std;

int main() {
    for (int i =0; i<20; i++)
     cout << RandomPicker::getRandomNumber(1, 100) << endl;
    return 0;
}