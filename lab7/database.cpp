// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
        *this = src;
    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
        std::cout << "copying elements of database..." ;
        
        // update used_slots
        used_slots = rhs.used_slots;
        
        if(aloc_slots < used_slots) {
            // allocate more memory and delete old_company_array
            aloc_slots = rhs.aloc_slots;
            company* old_company_array = company_array;
            company_array = new company[aloc_slots];
            delete[] old_company_array;
        }
        
        for(size_t i = 0; i < used_slots; i++)
            // copy contents of rhs.company_array
            company_array[i] = rhs.company_array[i];

        return *this;
    }
    
    
    database::~database() {
        // delete company objects in company_array
        delete[] company_array;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        // create new_company_array with new_capacity
        company* new_company_array = new company[new_capacity];
        
        for(size_t i = 0; i < used_slots; i++)
            // copy contents into new_company_array
            new_company_array[i] = company_array[i];
        
        // delete company objects in company_array
        delete[] company_array;
        
        // update company_array and aloc_slots to new_company_array and new_capacity
        company_array = new_company_array;
        aloc_slots = new_capacity;
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        if(used_slots == aloc_slots)
            // reserve memory if needed
            reserve(2 * aloc_slots);

        // add new company to end of array
        company_array[used_slots++] = company(entry);


        // company was not in the database
        return true;
    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        size_type pos = search_company(company);

        if (pos == COMPANY_NOT_FOUND) {
            // add company to the database at the end of the array
            insert_company(company);

            // insert the item into company
            company_array[used_slots - 1].insert(product_name, price);
            
            // company was not in the database
            return true;
        } else {
            // insert the item into company
            company_array[pos].insert(product_name, price);

            // company was already in the database
            return false;
        }
    }
    
    
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);

        if(company_index == COMPANY_NOT_FOUND)
            // company was not found
            return false;
        
        // update used_slots
        used_slots--;

        // delete company and shift all elements right of company to the left
        for(size_type i = company_index; i < used_slots; i++)
            company_array[i] = company_array[i + 1];

        // company was found
        return true;
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        size_t company_index = search_company(cName);

        if(company_index == COMPANY_NOT_FOUND)
            // company was not found in the database
            return false;
        
        // return false if pName was not found in company, otherwise erase pName and return true
        return company_array[company_index].erase(pName);
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        for(size_t i = 0; i < used_slots; i++)
            if(company_array[i].get_name() == company)
                // returns index of company
                return i;

        // company was not found in the database
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
