#include <iostream>
#include <assert.h>
#include "bag.h"

typedef int value_type;


void bag::insert(value_type item) {
    assert(used < capacity);
    container[used++] = item;
}

size_t bag::number_of_occurences(value_type item) const{
    int count = 0;

    for(int i = 0; i < used; i++) {
        if(container[i] == item)
            count++;
    }

    return count;
}

void bag::erase_one(value_type item) {
    for(int i = 0; i < used; i++)
        if(container[i] == item) {
            container[i] = container[--used];
            break;
        }
}

void bag::erase_all(value_type item) {
    for(int i = used - 1; i >= 0; i--)
        if(container[i] == item)
            container[i] = container[--used];
}

void bag::print() {
    std::cout << '[';
    for(int i = 0; i < used; i++) {
        std::cout << container[i];
        if(i < used - 1)
            std::cout << ", ";
    }

    std::cout << ']' << std::endl;
}

bag operator +(bag &a, bag &b) {
    bag res;

    assert(a.used + b.used <= a.capacity);

    for(int i = 0; i < a.used; i++)
        res.insert(a.container[i]);

    for(int i = 0; i < a.used; i++)
        res.insert(b.container[i]);

    return res;
}

bool operator ==(bag &a, bag &b) {
    if(a.used != b.used)
        return false;

    value_type table[sizeof(value_type)];

    for(int i = 0; i < a.used; i++)
        if(a.container[i] != b.container[i])
            return false;

    return true;
}