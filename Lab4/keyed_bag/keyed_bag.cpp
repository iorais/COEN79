#include "keyed_bag.h"

namespace coen79_lab4 {

    bool keyed_bag::erase(const key_type& key) {
        // iterate through keys
        for(int i = 0; i < used; i++)
            // key was found in the bag
            if(keys[i] == key) {
                // replace key and value to be deleted with last key and value  
                keys[i] = keys[used - 1];
                data[i] = data[used - 1];

                // update size of bag
                used--;

                return true;
            }
        
        // key was not found in the bag
        return false;
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert(size() < CAPACITY);  // ensure inserting will not exceed CAPACITY

        // add entry and key to end of arrays
        data[used] = entry;
        keys[used] = key;

        // update size of bag
        used++;
    }

    bool keyed_bag::has_key(const key_type& key) const {
        // iterate through keys
        for(int i = 0; i < used; i++)
            // return true if key is found in bag
            if(keys[i] == key)
                return true;
        
        // key was not found in the bag
        return false;
    }

    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key));   // ensure key is in bag

        // iterate through keys
        for(int i = 0; i < used; i++)
            // return value 
            if(keys[i] == key)
                return data[i];

        return 0;
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        int res = 0; // variable to track occurences

        // iterate through values
        for(int i = 0; i < used; i++)
            //increment res if value matches target
            if(data[i] == target)
                res++;

        return res;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        // iterate through keys in this bag
        for(int i = 0; i < used; i++)
            // return true if otherBag contains current key
            if(otherBag.has_key(keys[i]))
                return true;

        // no duplicates found
        return false;
    }

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
        assert(b1.used + b2.used < b1.CAPACITY);    // ensure b1 and b2 are of legal size
        assert(!b1.hasDuplicateKey(b2));            // ensure b1 and b2 have no duplicate keys

        keyed_bag b3; // keyed_bag to be returned

        // insert all keys and values from b1 to b3
        for(int i = 0; i < b1.used; i++)
            b3.insert(b1.data[i], b1.keys[i]);

        // insert all keys and values from b1 to b3
        for(int i = 0; i < b2.used; i++)
            b3.insert(b2.data[i], b2.keys[i]);

        return b3;
    }

}