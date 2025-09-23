#ifndef MYQUEUEOFINT_H
#define MYQUEUEOFINT_H
#include <cstddef>
#include <string>
class MyQueueOfInt
{
private:
    size_t size_;
    size_t capacity;
    size_t head;
    size_t end;
    int *memory;

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
