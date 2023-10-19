// FILE: sequence1.h
//  Sequence Class
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
// TYPEDEF and MEMBER CONSTANTS for the sequence class:
//   static const size_t CAPACITY = ____
//     sequence::CAPACITY is the maximum number of items that a sequence can hold.
//
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It may be any of
//     the C++ built-in types (int, char, etc.), or a class with a default
//     constructor, an assignment operator, and a copy constructor.
//
//
// CONSTRUCTOR for the sequence class:
//   sequence( )
//     Postcondition: The sequence has been initialized as an empty sequence.
//
//
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//
//  void start();
//      Poscondition: The iterator is reset to position 0;
//
//  void end();
//      Poscondition: The iterator points to the last item in the sequence;
//
//  void last();
//      Poscondition: The iterator is reset to CAPACITY - 1, regardless of the numebr of items in the sequence;
//
// void advance();
//      Precondtion: isitem() returns true
//      Postcondition: The iterator's value is increased by 1, unless it is already at the end of the sequence.
//
// void retreat();
//      Postcondition: The iterator's value is reduced by 1, unless it is already at the beginning of the sequence.
//
//
// void insert(const value_type& entry);
//      Precondition: size() < CAPACITY
//      Postcondition: A new copy of entry has been inserted in the sequence
//      before the current item. If there was no current item, the new entry
//      has been inserted at the front. In either case, the new item is now the
//      current item of the sequence.
//
//  void attach(const value_type& entry);
//      Precondition: size() < CAPACITY
//      Postcondition: A new copy of entry has been inserted in the sequence
//      after the current item. If there was no current item, the new entry
//      has been attached to the end. In either case, the new item is now the
//      current item of the sequence.
//
// void remove_current();
//      Precondtion: isitem() returns true
//      Postcondition: The current item has been removed from the sequence,
//      and the item after this (if there is one) is now the current item.
//
//
// void insert_front(const value_type& entry);
//      Precondition: size() < CAPACITY
//      Postcondition: A new copy of entry has been inserted in the sequence
//      at the front. The new item is now the current item of the sequence.
//
// void attach_back(const value_type& entry);
//      Precondition: size() < CAPACITY
//      Postcondition: A new copy of entry has been inserted in the sequence
//      at the back. The new item is now the current item of the sequence.
//
// void remove_front();
//      Precondtion: isitem() returns true
//      Postcondition: The item at the front of the sequence has been removed from the sequence,
//      and the current item points at the front of the sequence.
//
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//
//  size_type size() const;
//      Postcondition: The return value is the number of items in the ssequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current() const;
//      Precondtion: isitem() returns true
//      Poscondition: Returns the item in the sequence at the current position of the iterator.
//
//   value_type operator[](int index) const
//     Precondition: index < used
//     Postcondition: The item returned is the item stored at "index"
//
//   double mean() const
//     Postcondition: The value returned is the mean of the values stored in the sequence.
//
//   double standardDeviation() const
//     Postcondition: The value returned is the stadard deviation of the values stored in the sequence.
//
//
//
//
// NON-MEMBER functions for the statistician class:
//
//   sequence operator +(const sequence& lhs, const sequence& rhs)
//     Postcondition: The sequence that is returned contains all the
//     numbers of the sequences of lsh and rhs.
//
//   sequence operator+=(sequence& lhs, sequence& rhs)
//     Postcondition: Adds the items of rhs to the lhs. Also returns a copy of lhs.
//
//
//   value_type summation(const sequence &s)
//     Postcondition: The value returned is the summation of the values stored in the sequence s.
//
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
//

#ifndef COEN79_SEQUENCE1_H
#define COEN79_SEQUENCE1_H

#include <iostream>
#include <assert.h>
#include <cmath>

namespace coen79_lab3 {
    
    class sequence {

    private:
        // TYPEDEF and MEMBER CONSTANTS
        typedef double value_type;
        typedef std::size_t size_type;
        static const size_type CAPACITY = 30;
        value_type data[CAPACITY];
        size_type length;
        size_type current_index;
        value_type sum;
        
    public:
        sequence();

        //MODIFICATION MEMBER FUNCTIONS

        void start() {current_index = 0; }

        void end() {current_index = length - 1; }

        void last() {current_index = CAPACITY - 1; }

        void advance() {assert(is_item()); current_index += current_index < length ? 1 : 0; }

        void retreat() {current_index -= current_index > 0 ? 1 : 0; }

        void insert(const value_type& entry);

        void attach(const value_type& entry);

        void remove_current();

        void insert_front(const value_type& entry);

        void attach_back(const value_type& entry);

        void remove_front();

        //CONSTANT MEMBER FUNCTIONS

        size_type size() const { return length; }

        bool is_item() const { return current_index < length; }

        value_type current() const { assert(is_item()); return data[current_index]; }

        value_type operator[](int index) const { assert(index >= 0 && index < length); return data[index]; }

        double mean() const { return length > 0 ? sum/length : sum; }

        double standard_deviation() const;

        //NON-MEMBER FUNCTIONS

        friend sequence operator +(const sequence& lhs, const sequence& rhs);

        friend sequence operator +=(sequence& lhs, sequence& rhs);

        friend value_type summation(const sequence &s);

    };
}

#endif