#include "mystring.h"

namespace coen79_lab5 {

     string::string(const char str[ ] = "") {
        
        allocated = 
        current_length = allocated - 1;
        characters = new char [allocated];

        for(int i = 0; i < allocated; i++)
            characters[i] = str[i];
     }

}