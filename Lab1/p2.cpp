#include <stdio.h>
#include <iomanip>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

/**
 * Displays a string and its reverse in a slant 5 times.
 *
 * @param str the string to be displayed
 */
void display(string str);

/**
 * Reverses a string.
 *
 * @param str the string to be reversed
 * @return the reversed string
 */
string reverse(string str);

void display(string str) {
    for(int i = 0; i < 5; i++)//prints five lines
    {
        cout    << setw(20 + i)//incresease width by i for slant
                << str
                << "          "
                << reverse(str)
                << "\n";
    }
}

string reverse(string str) {
    //change string to a char array
    char *rev = new char[str.length() + 1];
    strcpy(rev, str.c_str());

    for(int i = 0; i < str.length() / 2; i++) {
        int j = str.length() - i - 1; //mirrored index

        //swap mirrored character
        char temp = rev[i];
        rev[i] = rev[j];
        rev[j] = temp;
    }

    return rev;
}

int main() {
    //gets input from user
    string input;
    cout << "Enter 10 digits (no whitespaces):\n";
    getline(cin, input);

    //ensures input is legal
    if(input.size() != 10) {
        cout << "Error: Illegal input size, input size must equal 10";
        return 0;
    }

    //displays input given by user
    display(input);

    return 0;
}