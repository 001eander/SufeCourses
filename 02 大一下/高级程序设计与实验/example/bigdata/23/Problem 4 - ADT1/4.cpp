/*
 * File: 4.pp
 * ----------------------------------------------
 * This program judges whether a subset of given integers has sum equal to a given target.
 */
#include <iostream>
#include "vector.h"
#include "console.h"
using namespace std;

void subsetSumHelper(const Vector<bool> &p, const Vector<int> &a, const int W, bool &res)
{
    if (p.size() == a.size()) {
        int s = 0;
        for (size_t i = 0; i != p.size(); ++i)
            s += (p[i] ? a[i] : 0);

        if (s == W)
            res = true;
        return;
    }

    if (!res) {
        subsetSumHelper(p + false, a, W, res);
        subsetSumHelper(p + true, a, W, res);
    }
}

bool subsetSum(const Vector<int> & a, int W)
{
    bool res = false;
    subsetSumHelper({}, a, W, res);
    return res;
}

int main()
{
    Vector<int> a = {1, 3, 5, 9, 20};
    int W = 28;
    cout << "There is ";
    if (!subsetSum(a, W))
        cout << "not ";
    cout << "a subset of a whose sum equals " << W << "." << endl;

    W = 7;
    cout << "There is ";
    if (!subsetSum(a, W))
        cout << "not ";
    cout << "a subset of a whose sum equals " << W << "." << endl;
  return 0;
}
