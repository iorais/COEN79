#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

int addTwoCharacters(const char firstDigit, const char secondDigit) {
    assert(isdigit(firstDigit) && isdigit(secondDigit));
    return int(firstDigit) + int(secondDigit) - 96;   
}

int main() {
    char x, y;

    std::cout << "type a digit: ";
    std::cin >> x;

    std::cout << "type a second digit: ";
    std::cin >> y;

    std::cout   << "Your sum is: "
                << addTwoCharacters(x, y) 
                << std::endl;

    return 0;
}