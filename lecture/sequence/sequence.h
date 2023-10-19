#include <iostream>
#include <assert.h>

typedef int value_type;

class sequence {
    private:
        static const size_t capacity = 30;
        value_type container[capacity];
        size_t used;
        size_t current_index;

    public:
        void start() { current_index = 0; }
        value_type get_current() { return container[current_index]; }
        bool can_advance() { return current_index < used; }
        void advance() {assert(current_index < used); current_index++;};
        
        void insert(value_type item);
        void attatch(value_type item);
        void remove_current();
};