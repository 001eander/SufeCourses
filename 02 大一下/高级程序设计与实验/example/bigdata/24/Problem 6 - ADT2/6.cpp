/*
 * File: 6.cpp for ADT-2&Recursion Problem
 * ----------------------------------------------
 * This program determines whether it is possible to 
 * transform vector a into vector b using at most k swaps.
 */

#include "console.h"
#include <iostream>
#include "vector.h"
using namespace std;

void dfs(Vector<int> &a, const Vector<int> &b, int p, const int k, bool &res)
{
    if (a == b)
        res = true;
    if (res || p >= k)
        return;

    for (size_t i = 0; i != a.size(); ++i) {
        for (size_t j = i + 1; j != a.size(); ++j) {
            std::swap(a[i], a[j]);
            dfs(a, b, p + 1, k, res);
            std::swap(a[i], a[j]);
        }
    }
}

bool canTransform(Vector<int> a, Vector<int> b, int k)
{
    bool res;
    dfs(a, b, 0, k, res);
    return res;
}

int main()
{
    cout << "Problem 6 - ADT2 & Recursion Test" << endl <<endl;
    int k = 2;
    Vector<int> a = {3, 2, 5, 4, 1}, b = {1, 2, 3, 4, 5};
    cout << (canTransform(a, b, k) ? "Yes" : "No") << endl;
    return 0;
}

