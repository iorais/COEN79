#include "sequence.h"


namespace coen79_lab3 {
    sequence::sequence() {
        length = 0;
        sum = 0;
        start();
    }

    void sequence::insert(const value_type& entry) {
        assert(length + 1 < CAPACITY);

        value_type prv = entry;
        length++;

        sum += entry;

        for(int i = current_index; i < length; i++) {
            //shifting elements to the right
            value_type temp = data[i];
            data[i] = prv;
            prv = temp;
        }
    }

    void sequence::attach(const value_type& entry) {
        //increment current_index to insert behind
        current_index++;
        insert(entry);
    }

    void sequence::remove_current() {
        assert(length > 0);

        sum -= data[current_index];

        for(int i = current_index; i < length; i++) {
            //shifting elements to the left
            data[i] = data[i + 1];
        }

        length--;
    }

    void sequence::insert_front(const value_type& entry) {
        int temp = current_index;//save current_index value

        //set the current_index to the first position and insert
        current_index = 0;
        insert(entry);

        //restore current_index to its original value
        current_index = temp;
    }

    void sequence::attach_back(const value_type& entry) {
        int temp = current_index;//save current_index value

        //set the current_index to the last position and attatch
        current_index = length - 1;
        attach(entry);

        //restore current_index to its original value
        current_index = temp;
    }

    void sequence::remove_front() {
        int temp = current_index;//save current_index value

        //set the current_index to the first position and remove
        current_index = 0;
        remove_current();

        //restore current_index to its original value
        current_index = temp;
    }

    double sequence::standard_deviation() const {
        double my_sum = 0;
        for(int i = 0; i < length; i++) {//summation
            my_sum += pow(data[i] - mean(), 2);
        }

        return sqrt(my_sum/length);
    }

    sequence operator +(const sequence& lhs, const sequence& rhs) {
        sequence res;
        assert(lhs.length + rhs.length < res.CAPACITY);

        for(int i = 0; i < lhs.length; i++)
            res.insert(lhs[i]);

        for(int i = 0; i < rhs.length; i++)
            res.insert(rhs[i]);

        return res;
    }

    sequence operator +=(sequence& lhs, sequence& rhs) {
        assert(lhs.length + rhs.length < lhs.CAPACITY);

        for(int i = 0; i < rhs.size(); i++)
            lhs.insert(rhs[i]);

        return lhs;
    }

    sequence::value_type summation(const sequence &s) {
        return s.sum;
    }
}