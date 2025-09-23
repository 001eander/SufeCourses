/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "simpio.h"

struct Node
{
    int data;
    Node *next;

    Node(int x)
        : data(x)
        , next(nullptr)
    {}
    Node(int x, Node *n)
        : data(x)
        , next(n)
    {}
    ~Node() { delete next; }
};

void print_list(Node *l)
{
    for (auto p = l; p != nullptr; p = p->next)
        std::cout << p->data << " ";
    std::cout << std::endl;
}

Node *subList(Node *list, int x, int n)
{
    if (list->data < x)
        return subList(list->next, x, n);

    Node *res = nullptr, *pre = nullptr;
    for (auto p = list; p != nullptr && n > 0; p = p->next, n--) {
        auto x = new Node(p->data);
        if (res == nullptr)
            res = x;
        if (pre != nullptr)
            pre->next = x;
        pre = x;
    }
    return res;
}

int main()
{
    Node *l = new Node(10);
    for (int i = 9; i >= 1; --i)
        l = new Node(i, l);

    print_list(l);
    print_list(subList(l, 5, 3));
    print_list(subList(l, 5, 10));
    delete l;
    return EXIT_SUCCESS;
}
