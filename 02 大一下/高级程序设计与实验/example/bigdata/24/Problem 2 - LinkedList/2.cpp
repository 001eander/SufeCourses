/*
 * File: 2.cpp for LinkedList Problem
 * ----------------------------------------------
 * This program finds up to n successive elements starting with
   the first element greater than or equal to x, building 
   a new Linked List that contains these elements and 
   returning the pointer of its heading node.
 */

#include "console.h"
#include "vector.h"
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* subList(Node* list, int x, int n)
{
    if (list->data < x)
        return subList(list->next, x, n);
    if (n == 0)
        return nullptr;
    return new Node{list->data, subList(list->next, x, n - 1)};
}

Node* build(Vector<int> a)
{
    if (a.size() == 0)
    {
        return nullptr;
    }
    else
    {
        return new Node{a[0], build(a.subList(1))};
    }
}

void print(Node* list)
{
    cout << "{";
    while (list != nullptr)
    {
        cout << list->data;
        if (list->next != nullptr)
        {
            cout << " -> ";
        }
        list = list->next;
    }
    cout << "}" << endl;
}

int main()
{
    cout << "Problem 2 - LinkedList Test" << endl <<endl;

    Vector<int> a = {1, 3, 5, 7, 9};

    Node* list = build(a);

    print(list);

    Node * sub = subList(list, 2, 3);

    print(sub);

    return 0;
}
