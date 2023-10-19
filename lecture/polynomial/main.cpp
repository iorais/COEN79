#include <iostream>
#include "polynomial.h"

int main() {
    double res;
    polynomial p1, p2;

    // p1 = 1
    p1.insert(1);
    res = p1.evaluate(100); // 1
    std::cout << res << std::endl;

    // p1 = 2x + 1
    p1.insert(2);
    res = p1.evaluate(2); // 5
    std::cout << res << std::endl;

    // p2 = 1
    p2.insert(1);
    res = p2.evaluate(100); // 1
    std::cout << res << std::endl;

    // p2 = 2x + 1
    p2.insert(2);
    res = p2.evaluate(2); // 5
    std::cout << res << std::endl;

    // p1 = 2x + 1
    // p2 = 2x + 1
    bool isEqual1 = p1 == p2; // true
    std::cout << "isEqual1: "<< isEqual1 << std::endl;

    // p2 = 4x^2 + 2x + 1
    p2.insert(4);
    res = p2.evaluate(2); // 21
    std::cout << res << std::endl;

    // p1 = 2x + 1
    // p2 = 4x^2 + 2x + 1
    bool isEqual2 = p1 == p2; // false
    std::cout << "isEqual2: " << isEqual2 << std::endl;

    // p1 = 4x^2 + 2x + 1
    p1.insert(4);
    res = p1.evaluate(2); // 21
    std::cout << res << std::endl;

    // p1 = 4x^2 + 2x + 1
    // p2 = 4x^2 + 2x + 1
    bool isEqual3 = p1 == p2; // true
    std::cout << "isEqual3: " << isEqual3 << std::endl;

    // p2 = 0x^3 + 4x^2 + 2x + 1
    p2.insert(0);
    res = p2.evaluate(2); // 21
    std::cout << res << std::endl;

    // p1 = 4x^2 + 2x + 1
    // p2 = 0x^3 + 4x^2 + 2x + 1
    bool isEqual4 = p1 == p2; // true
    std::cout << "isEqual4: " << isEqual4 << std::endl;

    return 0;
}