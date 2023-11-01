// FILE: mystring.h
// CLASS PROVIDED: string
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//
// CONSTRUCTOR for the string class:

//   Precondition: str is an ordinary null-terminated string.
//   Postcondition: The string contains the sequence of chars from str.
//   string(const char str[ ] = "") -- default argument is the empty string.

//   Postcondition: The string contains c and then the null character.
//   string(char c)

//   Postcondition: The string becomes a copy of the source string.
//   string(const string& source) -- Copy Constructor.

// MODIFICATION MEMBER FUNCTIONS for the string class:

//   Postcondition: addend has been catenated to the end of the string.
//   void operator +=(const string& addend)

//   Precondition: addend is an ordinary null-terminated string.
//   Postcondition: addend has been catenated to the end of the string.
//   void operator +=(const char addend[ ])

//   Postcondition: The single character addend has been catenated to the
//   end of the string.
//   void operator +=(char addend)

//   Postcondition: All functions will now work efficiently (without
//   allocating new memory) until n characters are in the string.
//   void reserve(size_t n)

//   Precondtion: position <= length()
//   Postcondition: The source string is inserted into this string before
//   the character at the given index.
//   void insert(const string& source, unsigned int position)

//   Precondition: (position + num) <= length( ).
//   Postcondition: num characters are deleted from the sequence, starting
//   at index position.
//   void dlt(unsigned int position, unsigned int num)

//   Precondition: position < length()
//   Postcondtion: the character at the given position in the string is
//   replaced with c.
//   void replace(char c, unsigned int position)

//   Precondition: (position + source.length()) <= length()
//   Postcondtion: the characters in this string starting at position are
//   replaced with those in the source srting.
//   void replace(const string& source, unsigned int position)


// CONSTANT MEMBER FUNCTIONS for the string class:

//   Postcondition: The return value is the number of characters in the
//   string.
//   size_t length( ) const

//   Precondition: position < length( ).
//   Postcondition: The value returned is the character at the specified
//   position of the string. A string's positions start from 0 at the start
//   of the sequence and go up to length( )-1 at the right end.
//   char operator [ ](size_t position) const

//   Postcondition: The location of the first occurence of the character c
//   within this string is returned. If the string does not contain c, -1 is
//   is returned.
//   int search(char c) const

//   Postcondition: Returns the index of the start of the first instance of
//   the given substring inside of this string. If the substring is not found,
//   this function returns -1.
//   int search(const string& substring) const

//   Postcondition: The count of the occurence of the character c within this
//   string is returned.
//   unsigned int cout(char c) const

// NON-MEMBER FUNCTIONS for the string class:

//   Postcondition: The string returned is the catenation of s1 and s2.
//   string operator +(const string& s1, const string& s2)

//   Postcondition: A string has been read from the istream ins, and the
//   istream ins is then returned by the function. The reading operation
//   skips white space (i.e., blanks, newlines, tabs) at the start of ins.
//   Then the string is read up to the next white space or the end of the
//   file. The white space character that terminates the string has not
//   been read.
//   istream& operator >>(istream& ins, string& target)

//   Postcondition: The sequence of characters in source has been written
//   to outs. The return value is the ostream outs.
//   ostream& operator <<(ostream& outs, const string& source)


//  VALUE SEMANTICS for the string class:
//    Assignments and the copy constructor may be used with string objects.
//
//  TOTAL ORDER SEMANTICS for the string class:
//    The six comparison operators (==, !=, >=, <=, >, and <) are implemented
//    for the string class, forming a total order semantics, using the usual
//    lexicographic order on strings.
//
// DYNAMIC MEMORY usage by the string class:
//   If there is insufficient dynamic memory then the following functions call
//   new_handler: The constructors, resize, operator +=, operator +, and the
//   assignment operator.


#ifndef COEN79_LAB5_STRING_H
#define COEN79_LAB5_STRING_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <assert.h>

namespace coen79_lab5 {

    class string {
    
    public:

        // CONSTRUCTOR:

        // Precondition: str is an ordinary null-terminated string.
        // Postcondition: The string contains the sequence of chars from str.
        // -- default argument is the empty string.
        string(const char str[ ] = "");

        // Postcondition: The string contains c and then the null character.
        string(char c);

        // Postcondition: The string becomes a copy of the source string.
        // -- Copy Constructor.
        string(const string& source);

        // DESTRUCTOR
        ~string( );
        
        // MODIFICATION MEMBER FUNCTIONS

        // Postcondition: addend has been catenated to the end of the string.
        void operator +=(const string& addend);

        // Precondition: addend is an ordinary null-terminated string.
        // Postcondition: addend has been catenated to the end of the string.
        void operator +=(const char addend[ ]);

        // Postcondition: The single character addend has been catenated to the
        // end of the string.
        void operator +=(char addend);

        // Postcondition: All functions will now work efficiently (without
        // allocating new memory) until n characters are in the string.
        void reserve(size_t n);


        string& operator =(const string& source);

        // Precondtion: position <= length()
        // Postcondition: The source string is inserted into this string before
        // the character at the given index.
        void insert(const string& source, unsigned int position);

        // Precondition: (position + num) <= length( ).
        // Postcondition: num characters are deleted from the sequence, starting
        // at index position.
        void dlt(unsigned int position, unsigned int num);

        // Precondition: position < length()
        // Postcondtion: the character at the given position in the string is
        // replaced with c.
        void replace(char c, unsigned int position);

        // Precondition: (position + source.length()) <= length()
        // Postcondtion: the characters in this string starting at position are
        // replaced with those in the source srting.
        void replace(const string& source, unsigned int position);

        
        // CONSTANT MEMBER FUNCTIONS

        // Postcondition: The return value is the number of characters in the
        // string.
        size_t length( ) const { return current_length; }

        // Precondition: position < length( ).
        // Postcondition: The value returned is the character at the specified
        // position of the string. A string's positions start from 0 at the start
        // of the sequence and go up to length( )-1 at the right end.
        char operator [ ](size_t position) const;
                
        // Postcondition: The location of the first occurence of the character c
        // within this string is returned. If the string does not contain c, -1 is
        // is returned.
        int search(char c) const;

        // Postcondition: Returns the index of the start of the first instance of
        // the given substring inside of this string. If the substring is not found,
        // this function returns -1.
        int search(const string& substring) const;

        // Postcondition: The count of the occurence of the character c within this
        // string is returned.
        unsigned int count(char c) const;
        
        // FRIEND FUNCTIONS

        // Postcondition: puts the string in the ostream
        friend std::ostream& operator <<(std::ostream& outs, const string& source);

        // Precondition: the instream is of size at most 100
        // Postcondition: puts the instream into the string target
        friend std::istream& operator >> (std::istream& ins, string& target);

        // Postcondition: returns true if the strings are the same otherwise false
        friend bool operator ==(const string& s1, const string& s2);

        // Postcondition: returns true if the strings are not the same otherwise false
        friend bool operator !=(const string& s1, const string& s2);

        // Postcondition: returns true if s1 preceeds s2 alphabetically otherwise false
        friend bool operator > (const string& s1, const string& s2);

        // Postcondition: returns true if s1 follows s2 alphabetically otherwise false
        friend bool operator < (const string& s1, const string& s2);

        // Postcondition: returns true if s1 preceeds or is equal to s2 alphabetically otherwise false
        friend bool operator >=(const string& s1, const string& s2);

        // Postcondition: returns true if s1 follows or is equal to s2 alphabetically otherwise false
        friend bool operator <=(const string& s1, const string& s2);

        // Postcondition: returns a string with characters from s1 in front and s2 at the end
        friend string operator +(const string& s1, const string& s2);

        // Postcondition: returns a string with characters from s1 in front and addend at the end
        friend string operator +(const string& s1, const char addend[ ]);
        
    private:
        char *characters;
        size_t allocated;
        size_t current_length;
    };

}

#endif
