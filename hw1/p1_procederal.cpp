#include <iostream>
#include <math.h>

float area(float radius) {
    return 3.14 * pow(radius, 2);
}

int main() {
    float r = 1;
    float my_circle = area(r);
}