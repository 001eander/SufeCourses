#include "myqueueofint.h"
#include "strlib.h"

#include <cstdlib>
#include <ostream>
#include <string>

MyQueueOfInt::MyQueueOfInt()
{
    size_ = 0ull;
    capacity = 1ull;
    head = 0;
    end = 0;
    memory = new int[1];
}

MyQueueOfInt::MyQueueOfInt(const MyQueueOfInt &queue)
{
    size_ = queue.size_;
    capacity = queue.capacity;
    head = queue.head;
    end = queue.end;
    memory = new int[capacity];
    memcpy(memory, queue.memory, capacity * sizeof(int));
}

MyQueueOfInt::~MyQueueOfInt()
{
    delete[] memory;
}

void MyQueueOfInt::enqueue(int x)
{
    size_++;
    if (size_ >= capacity) {
        auto ptr = memory;
        memory = new int[capacity * 2];
        memcpy(memory, ptr, capacity * sizeof(int));
        capacity *= 2;
        delete[] ptr;
    }

    memory[end] = x;
    end = (end + 1) % capacity;
}

int MyQueueOfInt::dequeue()
{
    auto x = memory[head];
    head = (head + 1) % capacity;
    size_--;

    if (size_ * 2 < capacity) {
        capacity /= 2;
        auto ptr = memory;
        memory = new int[capacity];
        memcpy(memory, ptr, capacity * sizeof(int));
        delete[] ptr;
    }
    return x;
}

int MyQueueOfInt::peek()
{
    return memory[head];
}

void MyQueueOfInt::clear()
{
    size_ = 0ull;
    capacity = 1ull;
    head = 0;
    end = 0;
    delete[] memory;
    memory = new int[1];
}

size_t MyQueueOfInt::size()
{
    return size_;
}

bool MyQueueOfInt::isEmpty()
{
    return head == end;
}

std::string MyQueueOfInt::toString()
{
    std::string result = "{";
    for (size_t i = head; i != end; i = (i + 1) % capacity) {
        result += integerToString(memory[i]);
        if ((i + 1) % capacity != end)
            result += ", ";
    }
    result += "}";
    return result;
}

void MyQueueOfInt::operator=(const MyQueueOfInt &queue)
{
    if (this == &queue)
        return;

    size_ = queue.size_;
    capacity = queue.capacity;
    head = queue.head;
    end = queue.end;
    memory = new int[capacity];
    memcpy(memory, queue.memory, capacity * sizeof(int));
}

std::ostream &operator<<(std::ostream &os, const MyQueueOfInt &queue)
{
    os << "{";
    for (size_t i = queue.head; i != queue.end; i = (i + 1) % queue.capacity) {
        os << queue.memory[i];
        if ((i + 1) % queue.capacity != queue.end)
            os << ", ";
    }
    os << "}";
    return os;
}
