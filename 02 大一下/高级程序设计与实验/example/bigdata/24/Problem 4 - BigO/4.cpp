/*
 * File: 4.cpp for BigO Problem
 * -----------------------------
 * This program outputs runtime complexity of 4
 * code fragments in Big-O notation of Problem 4.
 */
#include <iostream>
#include "console.h"
using namespace std;

const int MAXLENGTH = 4;

// Please fill all 4 answers into BigO string array.
static string BigO[] = {"O(N*N)", "O(1)", "O(N)", "O(logN)"};

int main() {
    cout<<"Problem 4 - Runtime Complexity Evaluation:" << endl<<endl;
    for (unsigned int i =0 ; i < MAXLENGTH; i++) {
        cout<<" Code Fragment #"<<i+1<<": " << BigO[i];
        cout<<endl;
    }
    cout<<endl;
    return 0;
}
