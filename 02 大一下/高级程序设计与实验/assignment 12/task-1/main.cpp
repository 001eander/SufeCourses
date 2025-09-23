/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "myqueueofint.h"
#include "simpio.h"
#include <cassert>
#include <cstdlib>

int main()
{
    // 测试默认构造函数
    MyQueueOfInt q1;
    assert(q1.isEmpty() == true);
    assert(q1.size() == 0);
    std::cout << "Test 1 (Empty Queue): Passed" << std::endl;

    // 测试 enqueue 和 peek
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    assert(q1.peek() == 10);
    assert(q1.size() == 3);
    std::cout << "Test 2 (Enqueue & Peek): Passed" << std::endl;

    // 测试 operator<<
    std::cout << "Queue q1 content: " << q1 << std::endl;

    // 测试 dequeue
    assert(q1.dequeue() == 10);
    assert(q1.peek() == 20);
    assert(q1.size() == 2);
    std::cout << "Test 3 (Dequeue): Passed" << std::endl;

    // 测试 clear
    q1.clear();
    assert(q1.isEmpty() == true);
    assert(q1.size() == 0);
    std::cout << "Test 4 (Clear): Passed" << std::endl;

    // 测试拷贝构造函数
    MyQueueOfInt q2;
    q2.enqueue(100);
    q2.enqueue(200);
    MyQueueOfInt q3(q2);
    assert(q3.dequeue() == 100);
    assert(q2.size() == 2); // 验证深拷贝
    std::cout << "Test 5 (Copy Constructor): Passed" << std::endl;

    // 测试赋值运算符
    MyQueueOfInt q4;
    q4.enqueue(500);
    q4 = q2;
    assert(q4.dequeue() == 100);
    assert(q2.size() == 2); // 验证原队列不受影响
    std::cout << "Test 6 (Assignment Operator): Passed" << std::endl;

    // 测试自赋值安全
    q4 = q4;
    assert(q4.peek() == 200);
    std::cout << "Test 7 (Self Assignment): Passed" << std::endl;

    // 测试 toString
    assert(q2.toString() == "{100, 200}");
    std::cout << "Test 8 (toString): Passed" << std::endl;

    // 综合测试
    MyQueueOfInt q5;
    q5.enqueue(1);
    q5.enqueue(2);
    q5.enqueue(3);
    assert(q5.dequeue() == 1);
    q5.enqueue(4);
    assert(q5.toString() == "{2, 3, 4}");
    std::cout << "Test 9 (Comprehensive): Passed" << std::endl;
    std::cout << std::endl;
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
