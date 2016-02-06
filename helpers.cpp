#include <iostream>
#include <string>

using namespace std;

//Function to convert a string to entirely lowercase letters
string lowercase(string word) {
    string wordOut = word;
    for (int i = 0; i < word.length(); i++) {
        wordOut[0] = tolower(word[0]);
    }
    return wordOut;
}

int main() {
    
    return 0;
}