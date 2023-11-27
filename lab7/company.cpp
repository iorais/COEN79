// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        *this = src;
    }

    
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        // set company_name to src
        company_name = src.company_name;

        // delete old list
        list_clear(head_ptr);
        
        // copy list from src and assign head_ptr and tail_ptr to copied list
        list_copy(src.head_ptr, head_ptr, tail_ptr);

        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            // initializes list
            list_init(head_ptr, tail_ptr, product_name, price);
        }
        else {
            // adds to the end of list
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        
        // find node to be erased del
        node* del = list_search(head_ptr, product_name);
        
        if(!del) {
            // node was not found
            return false;
        } else if(del->getLink()){
            // find pre cursor if list is greater than one
            node* pre = head_ptr;
            while(pre != del && pre->getLink() != del)
                pre = pre->getLink();
            
            // connect pre to successor of del
            pre->setLink(del->getLink());
        }
        
        // erase node
        delete del;
        
        return true;
    }
    
    
}
