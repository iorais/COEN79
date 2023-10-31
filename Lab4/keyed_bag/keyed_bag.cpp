#include "keyed_bag.h"

/*
Invariant:
[1] The number of elements in the bag is stored in the variable used. The arrays keys and data will
    always have the same number of elements. The ith element of keys and the ith element of data are
    key-value pairs. All elements in keys must be unique but elements in data do nothave to be unique.
    
[2] For an empty bag, we don't care what is stored in keys nor data. For a non-empty bag, the key-value
    pairs are stored in keys[0] to keys[used - 1] and data[0] to data[used - 1] respectively, and we
    don't care what is stored inthe rest of the arrays. The order does not matter as long as the ith
    element of key is paired with the ith element of data.
*/

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

    void keyed_bag::operator +=(const keyed_bag& addend) {
        assert(size() + addend.size() < CAPACITY);    // ensure addend is of legal size
        assert(!hasDuplicateKey(addend));            // ensure addend has no duplicate keys

        // insert all keys and values from addend
        for(int i = 0; i < addend.size(); i++)
            insert(addend.data[i], addend.keys[i]);
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