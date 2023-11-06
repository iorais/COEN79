// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
		// reset head_ptr and tail_ptr to NULL
		head_ptr = NULL;
		tail_ptr = NULL;

		node* itr; // pointer to iterate from start_ptr to end_ptr
		node* cur; // pointer to current node in new list

		// iterate from start_ptr to end_ptr
		for(itr = start_ptr; itr != end_ptr; itr = itr->link()) {
			if(head_ptr == NULL) {
				// point head_ptr to copy of start_ptr and point cur to head_ptr
				head_ptr = new node(itr->data());
				cur = head_ptr;
			} else {
				// add new node to link and increment cur
				cur->set_link(new node(itr->data()));
				cur = cur->link();
			}

			// assign tail_ptr to node preceding end_ptr
			if(itr->link() == end_ptr)
				tail_ptr = cur;
		}
	}

	size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		size_t count = 0; // counter for target initialized to zero

		// iterate through list
		for(node* itr = head_ptr; itr != NULL; itr = itr->link()) {
			// increment if count if data in node is equal to target
			if(itr->data() == target)
				count++;
		}

		return count;
	}

	void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		// ensures position is legal input
		assert(0 < position && position <= list_length(head_ptr) + 1);

		// insert at head
		if(position == 1) {
			list_head_insert(head_ptr, entry);
			return;
		}

		// pointer preceding node at position
		node *pre = list_locate(head_ptr, position - 1);

		// insert entry after pre
		list_insert(pre, entry);
	}

	node::value_type list_remove_at(node*& head_ptr, size_t position) {
		// ensures position is legal input
		assert(0 < position && position <= list_length(head_ptr));

		// data from node to be removed
		node::value_type data;

		// remove at head
		if(position == 1) {
			data = head_ptr->data();
			list_head_remove(head_ptr);
		} else {

			// pointer preceding node at position
			node* pre = list_locate(head_ptr, position - 1);

			data = pre->link()->data();

			// remove node after pre
			list_remove(pre);
		}

		return data;
	}

	node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		// ensures start and finish are legal inputs
		assert(	
			0 < start && 
			start <= finish && 
			finish <= list_length(head_ptr)
		);

		// pointers for nenw list
		node *new_head_ptr, *new_tail_ptr;

		// pointer to node a position start
		node *start_ptr = list_locate(head_ptr, start);

		// pointer to node at position finish
		node *end_ptr = list_locate(head_ptr, finish + 1);

		// creates a new piece of the list specified by start_ptr and end_ptr
		list_piece(start_ptr, end_ptr, new_head_ptr, new_tail_ptr);

		return new_head_ptr;
	}

	void list_print (const node* head_ptr) {
		// iterate through list
		const node* itr = NULL;
		for(itr = head_ptr; itr != NULL && itr->link() != NULL; itr = itr->link())
			cout << itr->data() << ", ";
		
		if(itr != NULL)
			cout << itr->data() << endl;
		else
			cout << "The list is empty" << endl;
	}

	void list_remove_dups(node* head_ptr) {
		// pointer to traverse list
		node *cur = head_ptr;

		// traverse list
		while(cur != NULL) {
			// find previous node of duplicate of cur
			node *pre = cur, *dup = cur->link();
			while (dup != NULL) {
				if(dup->data() == cur->data()) {
					// remove if duplicate
					list_remove(pre);
					dup = pre->link();
				} else {
					// continue traversing
					pre = dup;
					dup = dup->link();
				}
			}
			// traverse the list
			cur = cur->link();
		}
	}

	node* list_detect_loop (node* head_ptr) {
		node *sp, *fp;

		// slow and fast pointers
		sp = head_ptr;
		fp = head_ptr;

		while(fp != NULL && fp->link() != NULL) {
			// sp moves once each iterations
			sp = sp->link();

			// fp moves twice each iteration
			fp = fp->link()->link();

			// sp and fp meet and there is a cycle
			if(sp == fp)
				break;
		}

		// reset sp to the head
		sp = head_ptr;

		// fp and sp will meet at start of the cycle if any
		while(fp != NULL && fp != sp) {
			sp = sp->link();
			fp = fp->link();
		}

		// if there is no cycle fp will be NULL
		return fp;
		
	}

}
