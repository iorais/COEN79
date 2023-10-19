#include <iostream>

typedef int value_type;

class bag {
    private:
        static const size_t capacity = 30;
        value_type container[capacity];
        size_t used;

    public:
        bag() { used = 0; }

        /**
         * Inserts an item into the bag provided we're not at max capacity
         * 
         * @param item the item to be inserted
         */
        void insert(value_type item);

        /**
         * Fetches the number of occurences of a given item in the bag
         * 
         * @param item the item being counted
         * @return number of occrences of item
         */
        size_t number_of_occurences(value_type item) const;

        /**
         * Erases an item from the bag
         * 
         * @param item the item to be erased
         */
        void erase_one(value_type item);

        /**
         * Erases all of a given item from the bag
         * 
         * @param item the item to be erased
         */
        void erase_all(value_type item);

        /**
         * Fetches the current number of slots being used in the bag
         * 
         * @return number of used slots
         */
        size_t current_capacity() const { return used; }

        void print();

        friend bag operator +(bag &a, bag &b);
        friend bool operator ==(bag &a, bag &b);
};