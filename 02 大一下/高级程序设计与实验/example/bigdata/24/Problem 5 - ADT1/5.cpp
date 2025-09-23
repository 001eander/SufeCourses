/*
 * File: 5.cpp for ADT-1&Recursion Problem
 * ----------------------------------------------
 * This program generates all permutations of a given vector 
   of integers using recursion and stores each permutation in 
   a map with an auto-incremented integer as the key.
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "map.h"

using namespace std;

void generatePermutations(Vector<int>& nums, int index, Map<int, Vector<int>>& permutations, int& permIndex);
void printPermutations(const Map<int, Vector<int>>& permutations);

int main() {

    cout << "Problem 5 - ADT1 & Recursion Test" << endl <<endl;
    Vector<int> nums = {1, 2, 3};
    Map<int, Vector<int>> permutations;
    int permIndex = 0;

    cout << "Generating permutations of the vector {1, 2, 3} and storing in a map:" << endl;
    generatePermutations(nums, 0, permutations, permIndex);

    cout << "All stored permutations are:" << endl;
    printPermutations(permutations);

    return 0;
}

void generatePermutations(Vector<int>& nums, int index, Map<int, Vector<int>>& permutations, int& permIndex) {
    if (index == nums.size()) {
        permutations[permIndex++] = nums;
        return;
    }

    generatePermutations(nums, index + 1, permutations, permIndex);
    for (int i = index + 1; i != nums.size(); ++i) {
        std::swap(nums[index], nums[i]);
        generatePermutations(nums, index + 1, permutations, permIndex);
        std::swap(nums[index], nums[i]);
    }
}

void printPermutations(const Map<int, Vector<int>>& permutations) {
    for (int i = 0; i < permutations.size(); ++i) {
        cout << i << ": ";
        for (int x : permutations[i])
            cout << x << " ";
        cout << endl;
    }
}
