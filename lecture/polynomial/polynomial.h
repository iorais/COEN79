#include <iostream>
#include <assert.h>
#include <math.h>

class polynomial {
    private:
        typedef int value_type;
        typedef double output_type;
        typedef std::size_t size_type;

        static const size_type CAPACITY = 30;
        value_type data[CAPACITY];
        size_type used;

    public:
        polynomial() {used = 0; }

        output_type evaluate(int x);

        void insert(int c);

        void remove();

        friend bool operator ==(polynomial &p1, polynomial &p2);

};