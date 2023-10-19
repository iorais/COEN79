#include "polynomial.h"

polynomial::output_type polynomial::evaluate(int x) {
    if(used == 0)
        return 0;
    
    //intitialize result to first element in data
    double res = data[0];

    //add following degrees
    for(int i = 1; i < used; i++)
        res += data[i] * pow(x, i);

    return res;
}

void polynomial::insert(int c) {
    assert(used < CAPACITY);
    data[used++] = c;
}

void polynomial::remove() {
    assert(used > 0);
    used--;
}

bool operator ==(polynomial &p1, polynomial &p2) {
    //set max to the greater degree polynomial
    polynomial::size_type max = p1.used > p2.used ? p1.used : p2.used;

    for(int i = 0; i < max; i++) {
        if(i < p1.used && i < p2.used) {
        //compares constants of same degree
            if(p1.data[i] != p2.data[i])
                return false;
        } else if(i < p1.used) {//p1.used > p2.used
        //checks if constant is zero
            if(p1.data[i] != 0)
                return false;
        } else if(i < p2.used) {//p2.used > p1.used
        //checks if constant is zero
            if(p2.data[i] != 0)
                return false;
        }
    }

    return true;
}