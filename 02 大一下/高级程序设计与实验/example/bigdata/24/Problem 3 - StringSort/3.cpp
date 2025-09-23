
/*
 * File: 3.cpp for String or Sorting Problem
 * ----------------------------------------------
 * This program can read a list of students with their scores, 
 * sort the students by their scores using merge sort, and then
 * print the sorted list of students. 
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include <string>

using namespace std;

struct Student {
    string name;
    int score;
};

void mergeSort(Vector<Student>& students, int left, int right);
void merge(Vector<Student>& students, int left, int middle, int right);

int main() {

    cout << "Problem 3 - String or Sorting Test" << endl <<endl;   
    Vector<Student> students = {
        {"Alice", 85},
        {"Bob", 95},
        {"Charlie", 75},
        {"David", 90},
        {"Eva", 80}
    };

    mergeSort(students, 0, students.size() - 1);

    cout << "Sorted students by scores:" << endl;
    for (const auto& student : students) {
        cout << student.name << ": " << student.score << endl;
    }

    return 0;
}

void mergeSort(Vector<Student>& students, int left, int right) {
    if (left == right)
        return;

    auto mid = (left + right) / 2;
    mergeSort(students, left, mid);
    mergeSort(students, mid + 1, right);
    merge(students, left, mid, right);
}

void merge(Vector<Student>& students, int left, int middle, int right) {
    int i = left, j = middle + 1;
    Vector<Student> tmp;
    while (i <= middle && j <= right) {
        while (i <= middle && students[i].score > students[j].score)
            tmp += students[i++];
        while (j <= right && students[j].score > students[i].score)
            tmp += students[j++];
    }
    while (i <= middle)
        tmp += students[i++];
    while (j <= right)
        tmp += students[j++];
    for (int p = 0; p < tmp.size(); ++p)
        students[left + p] = tmp[p];
}
