#ifndef HELPERS_CPP
#define HELPERS_CPP

#include <iostream>

using namespace std;

//Function to convert a string to entirely lowercase letters
string lowercase(string word) {
    string wordOut = word;
    for (int i = 0; i < int(word.length()); ++i) {
        wordOut[0] = tolower(word[0]);
    }
    return wordOut;
}

#endif //HELPERS_CPP