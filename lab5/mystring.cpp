#include "mystring.h"

namespace coen79_lab5 {

     string::string(const char str[ ]) {
          const char *p = str; // pointer to str argument
          current_length = 0; // reset to zero

          // count length of str with current_length
          while(*p != '\0') {
               current_length++;
               p++;
          }

          // allocate memory
          allocated = current_length + 1;
          characters = new char [allocated];

          // copy all characters from str
          for(int i = 0; i < current_length + 1; i++)
               characters[i] = str[i];
     }

     string::string(char c) {
          // set current_length to one as there is one character 
          current_length = 1;

          // allocate memory
          allocated = current_length + 1;
          characters = new char [allocated];

          // insert c and null character into characters array
          characters[0] = c;
          characters[1] = '\0';
     }

     string::string(const string& source) {
          // set current_length to the same as source
          current_length = source.current_length;

          // allocate memory
          allocated = current_length + 1;
          characters = new char [allocated];

          // copy all characters from source
          for(int i = 0; i < source.current_length + 1; i++)
               characters[i] = source.characters[i];
     }

     string::~string( ) {
          // delete dynamically allocated array characters
          delete[] characters;
     }

     void string::operator +=(const string& addend) {
          // save previous length of string
          size_t previous_length = current_length;

          // update length of string
          current_length += addend.current_length;

          // allocate more memory if needed
          if(allocated < current_length + 1) {
               // buffer for previous characters
               char *previous_characters = characters;

               // update allocated and allocate memory
               allocated = current_length + addend.current_length + 1;
               characters = new char[allocated];

               // copy previous characters into newly allocated array
               for(int i = 0; i < previous_length; i++)
                    characters[i] = previous_characters[i];

               // deallocate unused memory
               delete []previous_characters;
          }

          // copy addend.characters to the end of the array
          for(int i = previous_length; i < current_length + 1; i++)
               characters[i] = addend.characters[i - previous_length];

     }

     void string::operator +=(const char addend[ ]) {
          // turn addend into a string the utilize operator +=
          *this += string(addend);
     }

     void string::operator +=(char addend) {
          // turn addend into a string then utlize operator +=
          *this += string(addend);
     }

     void string::reserve(size_t n) {
          // ensure characters in array can fit in new one
          assert(current_length <= n);

          // no new space to reserve
          if(n == current_length)
               return;

          // save previous length of string
          size_t previous_length = current_length;

          // buffer for previous characters
          char *previous_characters = characters;

          // update allocated and allocate memory
          allocated = n + 1;
          characters = new char[allocated];

          // copy previous characters into newly allocated array
          for(int i = 0; i < previous_length; i++)
               characters[i] = previous_characters[i];

          // deallocate unused memory
          delete []previous_characters;
     }

     string& string::operator =(const string& source) {
          // allocate more memory if needed
          if(current_length < source.length())
               reserve(source.length());
          
          // update current_length
          current_length = source.length();

          // copy characters from source into characters
          for(int i = 0; i < source.length() + 1; i++)
               characters[i] = source.characters[i];

          return *this;
     }

     void string::insert(const string& source, unsigned int position) {
          // ensure position is a legal input
          assert(position <= length());

          // copy characters from index position until the end into addend
          char *addend = new char[current_length + 1 - position];
          for(int i = 0, j = position; j < current_length + 1; i++, j++)
               addend[i] = characters[j];
           
          // end string at index position
          characters[position] = '\0';

          // update current_length
          current_length = position;

          // add source to our string
          *this += source;

          // add our previous end of the string to the end
          *this += addend;
     }

     void string::dlt(unsigned int position, unsigned int num) {
          // ensure position and num are legal inputs
          assert(position + num <= length());

          // copy characters from index position until the end into addend
          char *addend = new char[current_length + 1 - (position + num)];
          for(int i = 0, j = position + num; j < current_length + 1; i++, j++)
               addend[i] = characters[j];

          // end string at index position
          characters[position] = '\0';

          // update current_length
          current_length = position;

          // add our previous end of the string to the end
          *this += addend;
     }

     void string::replace(char c, unsigned int position) {
          // ensure position and num are legal inputs
          assert(position < length());

          // assign value at index position to c
          characters[position] = c;
     }

     void string::replace(const string& source, unsigned int position) {
          // ensure position and source are legal inputs
          assert((position + source.length()) <= length());

          // delete source.length() amount of characters starting from index position
          dlt(position, source.length());

          // insert source at index position
          insert(source, position);
     }

     char string::operator [ ](size_t position) const {
          // ensure position is a legal
          assert(position < length());

          // return the value offset by position
          return characters[position];
     }

     int string::search(char c) const {
          // iterate through characters
          for(int i = 0; i < current_length; i++)
               // c was found in characters at index i
               if(characters[i] == c)
                    return i;

          // c was not found in characters
          return -1;
     }

     int string::search(const string& substring) const {
          bool found = false; // flag if the substring is found

          // iterate through characters
          for(int i = 0; i < current_length; i++) {
               // check if characters with starting index i match with substring
               for(int j = i; j < i + substring.length() && j < current_length; j++)
                    if(characters[j] == substring[j - i]) {
                         found = true;
                    } else {
                         found = false;
                         break;
                    }
               
               if(found)
                    return i;
          }

          return -1;
     }

     unsigned int string::count(char c) const {
          unsigned int res = 0; // counter initialized to zero

          // iterate through characters
          for(int i = 0; i < current_length; i++) {
               // increment if found in characters
               if(characters[i] == c)
                    res++;
          }

          return res;
     }

     std::ostream& operator <<(std::ostream& outs, const string& source) {
          // iterate through characters
          for(int i = 0; i < source.length(); i++)
               // put characters[i] in outs
               outs << source.characters[i];

          return outs;
     }

     std::istream& operator >> (std::istream& ins, string& target) {
          // buffer to receive ins
          char buf[100 + 1];

          // initialize buf with all null characters
          for(int i = 0; i < 100 + 1; i++)
               buf[i] = '\0';

          // put ins buf
          ins >> buf;
          
          // set target equal to a string constructed from buf
          target = string(buf);

          return ins;
     }

     bool operator ==(const string& s1, const string& s2) {
          // check lengths of strings
          if(s1.length() != s2.length())
               return false;

          // iterate through characters of s1 and s2
          for(int i = 0; i < s1.length(); i++)
               // compare characters
               if(s1.characters[i] != s2.characters[i])
                    return false;

          // the strings are equivalent
          return true;
     }

     bool operator !=(const string& s1, const string& s2) {
          // return opposite of equality operator
          return !(s1 == s2);
     }

     bool operator > (const string& s1, const string& s2) {
          // find the minimum length between the two
          size_t min = s1.length() < s2.length() ? s1.length() : s2.length();

          // iterate through characters 0 - min in s1 and s2
          for(int i = 0; i < min; i++) {
               // s1 has a character greater than s2 in the ith position
               if(s1.characters[i] > s2.characters[i])
                    return true;
               // s1 has a character less than s2 in the ith position
               else if(s1.characters[i] < s2.characters[i])
                    return false;
          }
          // all characters from 0 - min are equal

          // return true if s1 is longer
          return s1.length() > s2.length();

     }

     bool operator < (const string& s1, const string& s2) {
          // find the minimum length between the two
          size_t min = s1.length() < s2.length() ? s1.length() : s2.length();

          // iterate through characters 0 - min in s1 and s2
          for(int i = 0; i < min; i++) {
               // s1 has a character less than s2 in the ith position
               if(s1.characters[i] < s2.characters[i])
                    return true;
               // s1 has a character greater than s2 in the ith position
               else if(s1.characters[i] > s2.characters[i])
                    return false;
          }
          // all characters from 0 - min are equal

          // return true if s1 is shorter
          return s1.length() < s2.length();
     }

     bool operator >=(const string& s1, const string& s2) {
          return !(s1 < s2);
     }

     bool operator <=(const string& s1, const string& s2) {
          return !(s1 > s2);
     }

     string operator +(const string& s1, const string& s2) {
          // create a copy of s1
          string res = string(s1);

          // add s2
          res += s2;

          return res;
     }

     string operator +(const string& s1, const char addend[ ]) {
          // create a copy of s1
          string res = string(s1);

          // add addend
          res += addend;

          return addend;
     }

}