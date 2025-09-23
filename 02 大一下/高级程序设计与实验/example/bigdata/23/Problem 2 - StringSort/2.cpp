#include <iostream>
#include <string>
#include "map.h"
#include "console.h"
#include <cctype>
using namespace std;

void wordAccount(string line, Map <string, int> & wordAcc);
string Capitalize(string word);
void printMap(Map <string, int> & wordAcc);

// The function wordAccount recognizes the words in the string line one by one
// Then calls the Captalize function to convert these words into standard format
// Finally writes each word and its occurrence times into wordAcc.
void wordAccount(string line, Map <string, int> & wordAcc)
{
    string word;
    for (size_t i = 0; i < line.size(); ++i) {
        if (isblank(line[i])) {
            word = Capitalize(word);
            if (wordAcc.containsKey(word))
                wordAcc[word]++;
            else
                wordAcc[word] = 1;
            word = "";
        } else {
            word += line[i];
        }
    }
}

//Convert words to standard format with the first letter capitalized
string Capitalize(string word){
    string result=word;
    result[0]=toupper(word[0]);
    for(int i=1;i<word.length();i++)
        result[i]=tolower(word[i]);
    return result;
}

//Output the result
void printMap(Map <string, int> & wordAcc){
    for(const string &x: wordAcc)
    {
        cout <<x << ":" << wordAcc[x]<< endl;
    }
}

int main() {
    string result;
    Map <string, int> wordAcc;

    string input_str = "Dog apple App App dog";
    cout << "Input String:" << input_str << endl;
    wordAccount(input_str, wordAcc);
    cout << "Result: " << endl;
    printMap(wordAcc);
    return 0;
}





