#include <stdio.h>
#include <iomanip>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

/**
 * Reads the file and prints all words of length at least 10, 
 * not including non-alphabetic numbers, in all uppercase.
 *
 * @param filename the file to be read
 *
 */ 
void readFile(string filename);

/**
 * Prints a string if it is of length at least 10,
 * not including non-alphabetic numbers, in all uppercase.
 *
 * @param str the string to be printed
 */
void alphaUpper(string str);

void readFile(string filename) {
    ifstream file (filename);

    if(!file.is_open()) {
        cout    << "Error: Issues opening file "
                << filename
                << endl;
        return;
    }

    string str;
    while(file.good()) { //traverses the file 
        file >> str;
        alphaUpper(str);
    }
}

void alphaUpper(string str) {
    if(str.length() < 10)
        return;

    int i = 0, len = 0;
    while(str[i]) { //counts the alphabetic characters
        len += isalpha(str[i]) ? 1:0;
        i++;
    }

    if(len < 10)
        return;

    i = 0;
    while(str[i]) { //prints the uppercase version of alphabetic characters
        if(isalpha(str[i]))
            cout << char(toupper(str[i]));
        i++;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    if(argc != 2) { //checks if the format is valid
        cout    << "Error: Incorrect number of arguments.\n"
                << "./p3 <filename>\n";
        return 0;
    }

    readFile(argv[1]);

    return 0;
}