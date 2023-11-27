// FILE: bag_bst.h (part of the namespace coen79_lab9)
// Behnam Dezfouli, COEN, SCU
//
// TEMPLATE CLASS PROVIDED: bag<Item>
//     (a container template class for a collection of items)
//
// TYPEDEFS for the bag<Item> class:
//   bag<Item>::value_type
//     bag<Item>::value_type is the data type of the items in the bag. It may
//     be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, a copy constructor, an assignment operator, and a
//     less-than operator forming a strict weak ordering.
//
//   bag<Item>::size_type
//     bag<Item>::size_type is the data type of any variable that keeps track
//     of how many items are in a bag.
//
// CONSTRUCTOR for the bag<Item> class:
//   bag( )
//     Postcondition: The bag is empty.
//
// MODIFICATION MEMBER FUNCTIONS for the bag<Item> class:
//   size_type erase(const Item& target)
//     Postcondition: All copies of target have been removed from the bag. The
//     return value is the number of copies removed (which could be zero).
//
//   bool erase_one(const Item& target)
//     Postcondition: If target was in the bag, then one copy of target has been
//     removed from the bag; otherwise the bag is unchanged. A true return value
//     indicates that one copy was removed; false indicates that nothing was
//     removed.
//
//   void insert(const Item& entry)
//     Postcondition: A new copy of entry has been inserted into the bag.
//
//   void operator +=(const bag& addend)
//     Postcondition: Each item in addend has been added to this bag.
//
// CONSTANT MEMBER FUNCTIONS for the bag<Item> class:
//   size_type size( ) const
//     Postcondition: Return value is the total number of items in the bag.
//
//   size_type count(const Item& target) const
//     Postcondition: Return value is number of times target is in the bag.
//
// NONMEMBER FUNCTIONS for the bag class:
//   bag operator +(const bag& b1, const bag& b2)
//     Postcondition: The bag returned is the union of b1 and b2.
//
// VALUE SEMANTICS for the bag class:
//   Assignments and the copy constructor may be used with bag objects.
//
// DYNAMIC MEMORY USAGE by the bag: 
//   If there is insufficient dynamic memory, then the following functions
//   throw bad_alloc: The constructors, insert, operator +=, operator +, and
//   the assignment operator.

#ifndef COEN79_BST_BAG
#define COEN79_BST_BAG

#include <cstdlib>     // Provides NULL and size_t
#include "bintree.h"   // Provides binary_tree_node and related functions

namespace coen79_lab9
{
    template <class Item>
    class bag
    {
    public:
        // TYPEDEFS
        typedef std::size_t size_type;
        typedef Item value_type;
        
        // CONSTRUCTORS and DESTRUCTOR
        bag( ) { root_ptr = NULL; }
        bag(const bag& source);
        ~bag( );
        
        // MODIFICATION functions
        size_type erase(const Item& target);
        bool erase_one(const Item& target);
        void insert(const Item& entry);
        void operator +=(const bag& addend);
        void operator =(const bag& source);
        
        // CONSTANT functions
        size_type size( ) const;
        size_type count(const Item& target) const;
        void debug( ) const { print(root_ptr, 0); }
        
    private:
        binary_tree_node<Item> *root_ptr; // Root pointer of binary search tree
        void insert_all(binary_tree_node<Item>* addroot_ptr);
    };
    
    // NONMEMBER functions for the bag<Item> template class
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2);
}



// -----------------------------
// *** IMPLEMENTATION ***
// -----------------------------

namespace coen79_lab9
{
    
#pragma mark - Toolkit Function Implementation
    
    
    // ---------------------------------
    // Toolkit functions for implementing bag class using BST
    // Note: These are not functions of the bag class
    // ---------------------------------
    
    template <class Item>
    void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
    // Precondition: root_ptr is a root pointer of a non-empty binary
    // search tree.
    // Postcondition: The largest item in the binary search tree has been
    // removed, and root_ptr now points to the root of the new (smaller)
    // binary search tree. The reference parameter, removed, has been set
    // to a copy of the removed item.
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        assert(root_ptr != NULL);
        
        if (root_ptr->right( ) != NULL)
            bst_remove_max(root_ptr->right( ), removed);
        else
        {
            // copy Item in root_ptr into removed
            removed = Item(root_ptr->data());

            // oldroot_ptr to delete later
            oldroot_ptr = root_ptr;

            // set root_ptr to left child to connect subtree
            root_ptr = root_ptr->left();

            // deallocate memory
            delete oldroot_ptr;
        }
    }
    
    
    template <class Item>
    bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: If target was in the tree, then one copy of target
    // has been removed, and root_ptr now points to the root of the new
    // (smaller) binary search tree. In this case the function returns true.
    // If target was not in the tree, then the tree is unchanged (and the
    // function returns false).
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            return false;
        }

        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            // return the answer from the recursive call
            return bst_remove(root_ptr->left(), target);
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
            // return the answer from the recursive call
            return bst_remove(root_ptr->right(), target);
        }
        
        // Target found

        // oldroot_ptr to delete later
        oldroot_ptr = root_ptr;

        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.
            root_ptr = root_ptr->right();
        } 
        else if (root_ptr->right( ) == NULL)
        {   // Target was found and there is no right subtree, so we can
            // remove this node, making the left child be the new root.
            root_ptr = root_ptr->left();
        } 
        else 
        {   // If code reaches this point, then we must remove the target from
            // the current node. We'll actually replace this target with the
            // maximum item of left subtree.
            
            // data from maximum of left subtree
            Item data;
            bst_remove_max(root_ptr->left(), data);

            // create binary_tree_node in place of oldroot_ptr
            root_ptr = new binary_tree_node<Item>(data, oldroot_ptr->left(), oldroot_ptr->right());
        }

        // deallocate memory
        delete oldroot_ptr;
        
        return true;
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bst_remove_all (binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: All copies of target have been removed from the tree
    // and root_ptr now points to the root of the new
    // (smaller) binary search tree. The return value tells how many copies
    // of the target were removed.
    {
        if (root_ptr == NULL)
        {   // Empty tree
            return 0;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            bst_remove_all(root_ptr->left(), target);
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
            bst_remove_all(root_ptr->right(), target);
        }

        // Target found

        // remove one instance of target
        bst_remove(root_ptr, target);
        
        // continue recursively searching for target
        return 1 + bst_remove_all(root_ptr, target);
    }
    
    
#pragma mark - Member Function Implementation

    
    // ---------------------------------
    // Member functions of the bag class
    // ---------------------------------

    
    // NOTE: The copy constructor needs to make a new copy of the source’s
    // tree, and point root_ptr to the root of this copy
    // Use the tree_copy function to do the copying
    template <class Item>
    bag<Item>::bag(const bag<Item>& source)
    // Library facilities used: bintree.h
    {
        // copy tree from source
        root_ptr = tree_copy(source.root_ptr);
    }
    
    

    template <class Item>
    bag<Item>::~bag( )
    // Header file used: bintree.h
    {
        tree_clear(root_ptr);
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::size( ) const
    // Header file used: bintree.h
    {
        return tree_size(root_ptr);
    }
    
    
    // Insert
    // Case 1: First handle this special case: When the first entry is inserted,
    //         simply call root_ptr = new binary_tree_node<Item>(entry)
    // Case 2: There are already some other entries in the tree:
    //    • We pretend to search for the exact entry that we are trying to insert
    //    • We stop the search just before the cursor falls off the bottom of the tree,
    //      and we insert the new entry at the spot where the cursor was about to fall off
    template <class Item>
    void bag<Item>::insert(const Item& entry)
    // Header file used: bintree.h
    {
        binary_tree_node<Item> *cursor = root_ptr;
        bool done = false;
        
        if (root_ptr == NULL)
        {
            root_ptr = new binary_tree_node<Item>(entry);
            return;
        }
        
        do
        {
            if (cursor->data( ) >= entry)
            {   // Check left
                if (!cursor->left())
                {   // There is no left child
                    // insert entry as the left child
                    done = true;
                    cursor->left() = new binary_tree_node<Item>(entry);
                }
                else
                {   // Go left
                    cursor = cursor->left();
                }
            }
            else
            {   // Check right
                if (!cursor->right())
                {   // There is no right child
                    // insert entry as the right child
                    done = true;
                    cursor->right() = new binary_tree_node<Item>(entry);
                }
                else
                {   // Go left
                    cursor = cursor->right();
                }
            }
        }   while (!done);
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::count(const Item& target) const
    {
        size_type answer = 0;
        binary_tree_node<Item> *cursor = root_ptr;
        
        while (cursor != NULL)
        {
            if (cursor->data( ) < target)
            {
                // Go right
                cursor = cursor->right( );
            }
            else
            {
                // increment answer when instance of target is found
                if (cursor->data( ) == target)
                    answer++;

                // Go left
                cursor = cursor->left( );
            }
        }
        return answer;
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::erase(const Item& target)
    {
        return bst_remove_all(root_ptr, target);
    }
    
    
    template <class Item>
    bool bag<Item>::erase_one(const Item& target)
    {
        return bst_remove(root_ptr, target);
    }
    
    
    // The assignment operator:
    // 1. First check if it is a self-assignment by comparing (this == &source): If yes, then return
    // 2. If there is no self-assignment, then before we copy the source tree we must release all
    //    memory used by the nodes of the current tree
    //    Use tree_clear to release memory
    template <class Item>
    void bag<Item>::operator =(const bag<Item>& source)
    // Header file used: bintree.h
    {
        // check for self-assignment
        if (this == &source)
            return;

        // release all memory of current tree
        tree_clear(root_ptr);

        // copy source tree into current tree
        root_ptr = tree_copy(source.root_ptr);
    }
    
    
    template <class Item>
    void bag<Item>::operator +=(const bag<Item>& addend)
    {
        if (root_ptr == addend.root_ptr)
        {
            // create copy of root_ptr to meet precondition of insert_all
            binary_tree_node<Item> copyroot_ptr = tree_copy(root_ptr);

            // insert all nodes from copied tree
            insert_all(copyroot_ptr);

            // delete copied tree
            tree_clear(copyroot_ptr);
        }
        else
            insert_all(addend.root_ptr);
    }
    
    
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
    {
        // create copy of b1 in res
        bag<Item> res = b1;

        // utilize operator += and return res
        return res += b2;
    }
    
    
    template <class Item>
    void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
    // Precondition: addroot_ptr is the root pointer of a binary search tree that
    // is separate for the binary search tree of the bag that activated this
    // method.
    // Postcondition: All the items from the addroot_ptr's binary search tree
    // have been added to the binary search tree of the bag that activated this
    // method.
    {
        assert(addroot_ptr != root_ptr);

        if (addroot_ptr != NULL)
        {
            // traverse addroot_ptr and insert each node
            postorder(&insert, addroot_ptr);
        }
    }

}

#endif
