#include <stdio.h>
#include <ctype.h>
#include <iostream>

using namespace std;

/**
 * Compute the number of alphanumeric characters in a string.
 * 
 * @param str the string to be analyzed
 * @return number of alphanumeric characters in 'str'
 */
int alphanumeric(string str);

/**
 * Counts the number of characters in a string excluding whitespaces ' '.
 *
 * @param str the string to be analyzed
 * @return the number of characters
 */
int len(string str);

int alphanumeric(string str) {
    int count = 0;

    //iterates over string
    for(int i = 0; i < str.length(); i++)
        if(isalnum(str[i]))//increment count if character is alphanumeric
            count++;

    return count;
}

int len(string str) {
    int count = 0;

    //iterates over string
    for(int i = 0; i < str.length(); i++)
        if(str[i] != ' ')//increment count if character is not a whitespace
            count++;

    return count;
}

int main() {
    //gets input from user
    string input;
    cout << "Enter a sentence:\n";
    getline(cin, input);

    //gets count of alphanumeric characters
    int count = alphanumeric(input);

    //prints output
    string output = "\"" + input + "\" has ";
    output += to_string(count);
    output += " alphanumeric character(s) and ";
    output += to_string(len(input) - count);
    output += " non-alphanumeric character(s).";

    cout << output;

    return 0;
}