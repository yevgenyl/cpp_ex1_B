#include <string>

using namespace std;
namespace phonetic{
    string find(string str, string word);
}

unsigned countWords(char *str);

namespace checks {
    /*
     * 1) Check if length match.
     */
    bool checkLength(string str, int desired);
    /*
     * 2) Check if two words are equal.
     */
    bool checkSameWord(string word1, string word2);
    /*
     * 3) Check if a given string is an empty word.
     */
    bool checkEmptyWord(string word);
    /*
     * 4) Check if two letters are in the same subgroup according to exercise definition.
     */
    bool checkSameGroup(char a, char b);
    /*
     * 5) Check if two letters are equal.
     */
    bool checkSameLetter(char a, char b);
    /*
     * 6) Check if two letter's are equal except one of them is upper/lower case version of the other.
     */
    bool checkUpperLower(char a, char b);
    /*
     * 7) Check if a given string contains more than one word.
     */
    bool checkMoreThanOneWord(string word);
}
