#include <iostream>
#include <assert.h>
#include "bag.h"

int main() {
    bag my_bag, your_bag;

    for(int i = 0; i < 5; i++) {
        my_bag.insert(i);
        your_bag.insert(i * 2);
    }
    my_bag.insert(1);
    std::cout << "my_bag - before erase" << std::endl;
    my_bag.print();

    my_bag.erase_all(1);

    std::cout << "my_bag" << std::endl;
    my_bag.print();

    std::cout << "your_bag" << std::endl;
    your_bag.print();

    bag this_bag = my_bag + your_bag;

    std::cout << "this_bag" << std::endl;
    this_bag.print();

    if (this_bag == my_bag)
        std::cout << "equal" << std::endl;
    else
        std::cout << "not equal" << std::endl;

    return 0;
}