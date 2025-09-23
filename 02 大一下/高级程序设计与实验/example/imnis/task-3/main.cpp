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
#include "map.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"

int main()
{
    Vector<int> p, t;
    std::cin >> p >> t;

    Queue<Vector<int>> q;
    Map<Vector<int>, Vector<int>> prev;
    q.enqueue(p);
    while (!q.isEmpty()) {
        auto x = q.dequeue();
        if (x == t)
            break;

        for (size_t i = 0; i != p.size(); ++i) {
            for (size_t j = i + 1; j != p.size(); ++j) {
                auto y = x;
                std::swap(y[i], y[j]);
                if (!prev.containsKey(y)) {
                    prev[y] = x;
                    q.enqueue(y);
                }
            }
        }
    }

    Vector<Vector<int>> res;
    for (auto i = t; i != p; i = prev[i])
        res += i;
    std::cout << p;
    for (int i = res.size() - 1; i >= 0; --i)
        std::cout << " -> " << res[i];
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
