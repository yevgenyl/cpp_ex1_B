#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include <string.h>

using namespace std;

/*
 * Possible Exceptions:
 * 1) wordNotFoundException - occurs when no matching at all.
 * 2) emptyWordException - occurs when user inputs an empty string.
 * 3) moreThanOneWordException - occurs when user inputs more than one word.
 */
class wordNotFoundException: public exception
{
    virtual const char* what() const throw()
    {
        return "Word not found!";
    }
} wordNotFoundException;

class emptyWordException: public exception
{
    virtual const char* what() const throw()
    {
        return "Empty word!";
    }
} emptyWordException;

class moreThanOneWordException: public exception
{
    virtual const char* what() const throw()
    {
        return "You should not search for more than one word at a time!";
    }
} moreThanOneWordException;

/* Helper function - returns number of words in a given string.
 * taken from: https://www.geeksforgeeks.org/count-words-in-a-given-string/
 * Contains minor changes made by me.
*/
unsigned countWords(char *str) {
    bool state = true;
    unsigned wc = 0; // word count
    // Scan all characters one by one
    while (*str) {
        // If next character is a separator, set the
        // state as true
        if (*str == ' ' || *str == '\n' || *str == '\t')
            state = true;
            // If next character is not a word separator and
            // state is true, thant means the previous character was a separator or beginning of sentence,
            // so we have a new word to count.
        else if (state == true) {
            state = false; // No need to count until next word separator.
            ++wc;
        }
        // Move to next character
        ++str;
    }
    return wc;
}

/*
 * namespace checks - contains all necessary type of check methods.
 */
namespace checks {
    /*
     * 1) Check if length match.
     */
    bool checkLength(string str, int desired) {
        return str.length() == desired;
    }
    /*
     * 2) Check if two words are equal.
     */
    bool checkSameWord(string word1, string word2) {
        return word1.compare(word2) == 0;
    }
    /*
     * 3) Check if a given string is an empty word.
     */
    bool checkEmptyWord(string word) {
        if (word.find_first_not_of(' ') != string::npos)
            return false;
        return true;
    }
    /*
     * 4) Check if two letters are in the same subgroup according to exercise definition.
     */
    bool checkSameGroup(char a, char b) {
        string groups[8] = {"vVwW", "bBfFpP", "gGjJ", "cCkKqQ", "sSzZ", "dDtT", "oOuU", "iIyY"};
        for (int i = 0; i < 8; i++) {
            string group = groups[i];
            string::size_type n;
            if (((n = group.find(a)) != string::npos) && ((n = group.find(b)) != string::npos)) { // If two letters are in the same subgroup.
                return true;
            }
        }
        return false;
    }

    /*
     * 5) Check if two letters are equal.
     */
    bool checkSameLetter(char a, char b){
        return (a == b);
    }
    /*
     * 6) Check if two letter's are equal except one of them is upper/lower case version of the other.
     */
    bool checkUpperLower(char a, char b) {
        int diff = 'a' - 'A';
        return ((a - b) == diff) || ((b - a) == diff);
    }
    /*
     * 7) Check if a given string contains more than one word.
     */
    bool checkMoreThanOneWord(string word) {
        char cstr[word.size() + 1];
        strcpy(cstr, word.c_str());
        return countWords(cstr) > 1;
    }
}

using namespace checks;

namespace phonetic {
    string find(string str, string word) {
        if (checkEmptyWord(word)) {
            //Need to throw exception
            throw emptyWordException;
        }
        if (checkMoreThanOneWord(word)) {
            //Need to throw exception
            throw moreThanOneWordException;
        }
        word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end()); // Remove whitespaces
        istringstream stream(str);
        do { // Check word by word until end of text.
            string currentWord;
            stream >> currentWord; // Initialize 'currentString' with the current word.
            if (checkLength(currentWord,word.length())) { // If current word has the same length then we need to check it.
                if (checkSameWord(currentWord, word)) { // If it's the same word then we found it.
                    return currentWord; // Return the word we found.
                }
                // In case it's not the same word, we need to check if there's spelling issues or upper/lower case replacement options.
                string::iterator iterator1; // Iterator for currentWord.
                string::iterator iterator2;// Iterator for user's chosen word.
                int count = word.length();
                for (iterator1 = currentWord.begin(), iterator2 = word.begin();
                     iterator1 < currentWord.end(); iterator1++, iterator2++) {
                    // Check if some letters may be misspelled, or if there's upper/lower case replacement options.
                    if (checkSameGroup(*iterator1, *iterator2) || checkUpperLower(*iterator1, *iterator2) || checkSameLetter(*iterator1, *iterator2)) {
                        count--;
                    }
                }
                if(count == 0){ // That means all compared characters are misspelled or upper/lower case replaced. so we found a word.
                    return currentWord; // Return the word we found.
                }
            }
        } while (stream);
        //If we reached the end of string without returning any value then word doesn't exist. Need to throw an exception.
        throw wordNotFoundException;
    }
}
