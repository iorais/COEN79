//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    sequence::~sequence() {
        // deallocate linked list
        list_clear(head_ptr);
    }

    void sequence::start( ) {
        // no node before head
        precursor = NULL;

        // cursor points to the start of the sequencee
        cursor = head_ptr;
    }

    void sequence::end() {
        // finds the node preceding the end of the sequence
        precursor = list_locate(head_ptr, many_nodes - 1);

        // cursor points to the end of the sequence
        cursor = tail_ptr;
    }

    void sequence::advance( ) {
        // ensures a current item exists
        assert(is_item());

        // precursor moves one step
        precursor = cursor;

        // cursor moves one step
        cursor = cursor->link();
    }

    void sequence::insert(const value_type& entry) {
        if(cursor == head_ptr || cursor == NULL) {
            // insert at the head
            list_head_insert(head_ptr, entry);

            // update precursor
            precursor = NULL;

            //update cursor
            cursor = head_ptr;
        } else {
            // insert after precursor
            list_insert(precursor, entry);

            // update cursor
            cursor = precursor->link();
        }
        // update sequence size
        many_nodes++;
    
        // head and tail are the same for sequence of 1
        if(many_nodes == 1)
            tail_ptr = head_ptr;
    }
    
    void sequence::attach(const value_type& entry) {
        if(many_nodes == 0) {
            head_ptr = new node(entry);
            tail_ptr = head_ptr;
            precursor = NULL;
            cursor = head_ptr;
        } else if(cursor == tail_ptr || cursor == NULL) {
            // insert after tail_ptr
            list_insert(tail_ptr, entry);

            // update precursor
            precursor = tail_ptr;

            // update cursor
            cursor = precursor->link();

            // update tail_ptr
            tail_ptr = cursor;
        } else {
            // insert after cursor
            list_insert(cursor, entry);

            // update precurosr
            precursor = cursor;

            // update cursor
            cursor = precursor->link();
        }

        // update sequence size
        many_nodes++;
    }

    void sequence::operator =(const sequence& source) {
        // initialize member variables to NULL
        init();

        // copy list from source
        list_copy(source.head_ptr, head_ptr, tail_ptr);

        if(source.cursor)
            cursor = list_search(head_ptr, source.cursor->data());

        if(source.precursor)
            precursor = list_search(head_ptr, source.precursor->data());

        // set sequence size equivalent to source
        many_nodes = source.many_nodes;
    }

    void sequence::remove_current( ) {
        // ensure a current item exists
        assert(is_item());

        if(cursor == head_ptr) {
            // remove head
            list_head_remove(head_ptr);

            // update cursor
            cursor = head_ptr;
        } else if(cursor == tail_ptr) {
            // remove tail
            list_remove(precursor);

            // update cursor
            cursor = precursor->link();

            // update tail
            tail_ptr = cursor;
        } else {
            // remove node after precurosr
            list_remove(precursor);

            // update cursor
            cursor = precursor->link();
        }

        // update sequence size
        many_nodes--;
    }

    sequence::value_type sequence::current() const {
        // ensure a current item exists
        assert(is_item()); 
        return cursor->data(); 
    }
}
