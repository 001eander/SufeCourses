#include "myqueueofint.h"
#include "strlib.h"

#include <cstdlib>
#include <ostream>
#include <string>

MyQueueOfInt::MyQueueOfInt()
{
    size_ = 0ull;
    head = nullptr;
    end = nullptr;
}

MyQueueOfInt::MyQueueOfInt(const MyQueueOfInt &queue)
{
    size_ = queue.size_;
    head = new MyQueueOfIntNode;
    auto p = head;
    for (auto ptr = queue.head; ptr != queue.end; ptr = ptr->next) {
        p->value = ptr->value;
        p->next = new MyQueueOfIntNode;
        p = p->next;
    }
    p->value = queue.end->value;
    end = p;
}

MyQueueOfInt::~MyQueueOfInt()
{
    auto ptr = head;
    while (ptr != nullptr) {
        auto next_ = ptr->next;
        delete ptr;
        ptr = next_;
    }
}

void MyQueueOfInt::enqueue(int x)
{
    size_++;
    if (end == nullptr) {
        head = new MyQueueOfIntNode(x);
        end = head;
        return;
    }

    auto ptr = new MyQueueOfIntNode(x);
    end->next = ptr;
    end = ptr;
}

int MyQueueOfInt::dequeue()
{
    size_--;
    auto x = head->value;
    auto ptr = head;
    if (head == end) {
        head = nullptr;
        end = nullptr;
    } else {
        head = head->next;
    }
    delete ptr;
    return x;
}

int MyQueueOfInt::peek()
{
    return head->value;
}

void MyQueueOfInt::clear()
{
    size_ = 0;
    auto ptr = head;
    while (ptr != nullptr) {
        auto next_ = ptr->next;
        delete ptr;
        ptr = next_;
    }
    head = nullptr;
    end = nullptr;
}

size_t MyQueueOfInt::size()
{
    return size_;
}

bool MyQueueOfInt::isEmpty()
{
    return size_ == 0;
}

std::string MyQueueOfInt::toString()
{
    std::string result = "{";
    for (auto ptr = head; ptr != nullptr; ptr = ptr->next) {
        result += integerToString(ptr->value);
        if (ptr != end)
            result += ", ";
    }
    result += "}";
    return result;
}

void MyQueueOfInt::operator=(const MyQueueOfInt &queue)
{
    if (this == &queue)
        return;

    auto ptr = head;
    while (ptr != nullptr) {
        auto next_ = ptr->next;
        delete ptr;
        ptr = next_;
    }

    size_ = queue.size_;
    head = new MyQueueOfIntNode;
    auto p = head;
    for (auto ptr = queue.head; ptr != queue.end; ptr = ptr->next) {
        p->value = ptr->value;
        p->next = new MyQueueOfIntNode;
        p = p->next;
    }
    p->value = queue.end->value;
    end = p;
}

std::ostream &operator<<(std::ostream &os, const MyQueueOfInt &queue)
{
    os << "{";
    for (auto ptr = queue.head; ptr != nullptr; ptr = ptr->next) {
        os << ptr->value;
        if (ptr != queue.end)
            os << ", ";
    }
    os << "}";
    return os;
}
