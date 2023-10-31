#include "poly.h"

/*
Invariant:
[1] An element from the array coefficients, coefficients[i] represents the coefficient of the ith term.
    The array coefficients will be zero by default and contain MAXIMUM_DEGREE + 1 elements.
    
[2] The variable deg is the highest index containing a nonzero element. Anytime the coefficients array
    is modified, the variable deg must be updated.
*/

namespace coen79_lab4 {
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE); // ensures degree does not exceed max

        clear();                    // sets all coeffecients to zero
        assign_coef(c, exponent);   // sets coeffecient of x ^ exponent to c
    }

    void polynomial::update_current_degree() {
        deg = 0;

        // iterates through coefficients left to right
        for(int i = 0; i < MAXIMUM_DEGREE + 1; i++)
            // updates deg if coefficients[i] is nonzero
            if(coefficients[i] != 0)
                deg = i;
    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE); // ensures degree does not exceed max

        coefficients[exponent] = coefficient;   // assigns coefficient to corresponding positon in array
        update_current_degree();                // updates degree
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE); // ensures degree does not exceed max

        coefficients[exponent] += amount;   // adds amount to coefficeints[exponent]
        update_current_degree();            // updates degree
    }

    void polynomial::clear() {
        // iterates through coefficients
        for(int i = 0; i < MAXIMUM_DEGREE + 1; i++)
            // assigns coeffecient[i] to zero
            coefficients[i] = 0;
        
        update_current_degree();  // updates degree
    }

    polynomial polynomial::antiderivative( ) const {
        assert(degree() < MAXIMUM_DEGREE); // ensures degree does not exceed max

        polynomial res; // resulting polynomial object

        // iterate through current polynomial
        for(int i = 0; i < MAXIMUM_DEGREE + 1; i++)
            // c * x^i = d/dx[ c / (i + 1) * x^(i + 1) ]
            res.assign_coef(coefficients[i] / (i + 1), i + 1);

        return res;
    }

    double polynomial::definite_integral(double x0, double x1) const {
        polynomial integral = antiderivative(); // indefinite integral

        // integral at x=x1 subtracted by integral at x=x0
        return integral(x1) - integral(x0);
    }

    polynomial polynomial::derivative( ) const {
        polynomial res; // resulting polynomial object

        // iterate from second term through current polynomial
        // first term is constant which derives to zero
        for(int i = 1; i < MAXIMUM_DEGREE + 1; i++)
            // d/dx[ c * x^i ] = i * c * x^(i - 1)
            res.assign_coef(i * coefficients[i], i - 1);

        return res;
    }

    double polynomial::eval(double x) const {
        int res = 0; // resulting evaluation of polynomial

        // iterate through coefficients
        for(int i = 0; i < MAXIMUM_DEGREE + 1; i++)
            // summation of each term
            res += coefficients[i] * pow(x, i);

        return res;
    }

    bool polynomial::is_zero( ) const {
        // iterates through coefficients
        for(int i = 0; i < MAXIMUM_DEGREE + 1; i++)
            // nonzero coefficient returns false
            if(coefficients[i] != 0)
                return false;

        // all coefficients are zero
        return true;
    }

    unsigned int polynomial::next_term(unsigned int e) const {
        // iterate from one degree higher than e to end of coefficients
        for(int i = e + 1; i < MAXIMUM_DEGREE + 1; i++)
            // return degree of closest nonzero term of higher degree
            if(coefficients[i] != 0)
                return i;

        // no nonzero term of higher degree
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
        // iterate from one degree smaller than e to start of coefficients
        for(int i = e - 1; i >= 0; i--)
            // return degree of closest nonzero term of lower degree
            if(coefficients[i] != 0)
                return i;

        // no nonzero term of lower degree
        return UINT_MAX;
    }

    double polynomial::operator( ) (double x) const {
        return eval(x);
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        polynomial res; // resulting polynomial object
        int max_degree = p1.degree() > p2.degree() ? p1.degree() : p2.degree(); // highest degree between p1 and p2

        // iterates through coefficients of p1 and p2
        for(int i = 0; i < max_degree + 1; i++)
            //add coefficients of p1 and p2 and store in corresponding position in res
            res.assign_coef(p1.coefficients[i] + p2.coefficients[i], i);

        return res;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial res; // resulting polynomial object
        int max_degree = p1.degree() > p2.degree() ? p1.degree() : p2.degree(); // highest degree between p1 and p2

        // iterates through coefficients of p1 and p2
        for(int i = 0; i < max_degree + 1; i++)
            //subtracts coefficients of p1 and p2 and store in corresponding position in res
            res.assign_coef(p1.coefficients[i] - p2.coefficients[i], i);

        return res;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        polynomial res; // resulting polynomial object

        assert(p1.degree() + p2.degree() < res.MAXIMUM_DEGREE); // ensures resulting degree is legal

        // iterate through all coefficients of p1
        for(int i = 0; i < p1.degree() + 1; i++)
            // iterate through all coefficients of p2
            for(int j = 0; j < p2.degree() + 1; j++) {
                // multiply each term of p1 to p2 and add terms of same degree
                int a = p1.coefficients[i]; // coefficient of ith term in p1
                int b = p2.coefficients[j]; // coefficient of jth term in p2

                // (a * x^i) * (b * x^j) = (a * b) * x^(i + j)
                res.add_to_coef(a * b, i + j);
            }

        return res;
    }

    std::ostream& operator << (std::ostream& out, const polynomial& p) {
        bool precede = false; // flag to check preceeding nozero terms

        // prints the last term, only nonzero terms
        int i = p.MAXIMUM_DEGREE;
        if(p.coefficients[i] != 0) {
            if(p.coefficients[i] == 1)
                // 1x^i = x^i
                out << "x^" << i;
            else
                // cx^i
                out << p.coefficients[i] << "x^" << i;
            
            precede = true;
        }
        // iterates and prints (MAX_DEGREE-1)th term through 2nd term
        for(int i = (p.MAXIMUM_DEGREE - 1); i >= 2; i--) {
            // prints only nonzero terms
            if(p.coefficients[i] != 0) {
                // adds " + " to seperate preceding term
                if(precede)
                    out << " + ";

                if(p.coefficients[i] == 1)
                    // 1x^i = x^i
                    out << "x^" << i;
                else
                    // cx^i
                    out << p.coefficients[i] << "x^" << i;

                precede = true;
            }
        }

        // prints 1st term (1x = x), only nonzero terms
        if(p.coefficients[1] != 0) {
            // adds " + " to seperate preceding term
            if(precede)
                out << " + ";
            
            if(p.coefficients[1] == 1)
                // 1x = x
                out << "x";
            else
                // cx
                out << p.coefficients[1] << "x";

            precede = true;
        }
        // prints 0th term (just the coefficient as x^0 = 1), only nonzero terms
        if(p.coefficients[0] != 0) {
            // adds " + " to seperate preceding term
            if(precede)
                out << " + ";
            
            out << p.coefficients[0];
        }

        return out;
    }
}