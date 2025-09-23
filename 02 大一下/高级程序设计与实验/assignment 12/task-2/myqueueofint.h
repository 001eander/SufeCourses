#ifndef MYQUEUEOFINT_H
#define MYQUEUEOFINT_H

#include <cstddef>
#include <string>

struct MyQueueOfIntNode
{
    int value;
    MyQueueOfIntNode *next;

    MyQueueOfIntNode()
    {
        value = 0;
        next = nullptr;
    }

    MyQueueOfIntNode(int x)
    {
        value = x;
        next = nullptr;
    }
};

class MyQueueOfInt
{
private:
    size_t size_;
    MyQueueOfIntNode *head;
    MyQueueOfIntNode *end;

public:
    MyQueueOfInt();
    MyQueueOfInt(const MyQueueOfInt &queue);
    ~MyQueueOfInt();

    void enqueue(int x);
    int dequeue();
    int peek();
    void clear();
    size_t size();
    bool isEmpty();
    std::string toString();

    void operator=(const MyQueueOfInt &queue);

    friend std::ostream &operator<<(std::ostream &os, const MyQueueOfInt &queue);
};

#endif // MYQUEUEOFINT_H
