#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

void dfs(const string &str, const Vector<string> &vec, Set<Vector<string>> &res)
{
    if (str.size() == 0)
        res += vec;
    else
        for (int i = 1; i <= str.size(); ++i)
            dfs(str.substr(i), vec + str.substr(0, i), res);
}

Set<Vector<string>> splitsOf(const string &str)
{
    Set<Vector<string>> res;
    dfs(str, {}, res);
    return res;
}

//Output the result
void printResult(Set<Vector<string>> & result){
    cout << "Splitted Result: " << endl;
    for(const Vector<string> &vec: result)
    {
        cout <<"  " << vec << endl;
    }
}

int main() {

    string input_str = "RUBY";
    auto result = splitsOf(input_str);
    printResult(result);
    return 0;

}





