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
#include "grid.h"
#include "simpio.h"

struct Table
{
    Grid<int> table;
    Table()
        : table(3, 3)
    {}
    Table(const Table &t)
        : table(t.table)
    {}

    bool full() const
    {
        for (int i : table)
            if (i == 0)
                return false;
        return true;
    }

    int imperfict() const
    {
        if (!full())
            return 999;

        int min_s = 999, max_s = -1;

        for (size_t i = 0; i != 3; ++i) {
            int sr = 0, sc = 0;
            for (size_t j = 0; j != 3; ++j) {
                sr += table[i][j];
                sc += table[j][i];
            }

            min_s = std::min(min_s, std::min(sr, sc));
            max_s = std::max(max_s, std::max(sr, sc));
        }

        int s1 = 0, s2 = 0;
        for (size_t i = 0; i != 3; ++i) {
            s1 += table[i][i];
            s2 += table[i][2 - i];
        }

        min_s = std::min(min_s, std::min(s1, s2));
        max_s = std::max(max_s, std::max(s1, s2));

        return max_s - min_s;
    }

    void operator=(const Table &t) { table = t.table; }
};

std::istream &operator>>(std::istream &in, Table &t)
{
    for (auto &i : t.table)
        in >> i;
    return in;
}

std::ostream &operator<<(std::ostream &os, const Table &t)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            std::cout << t.table[i][j] << " ";
        std::cout << std::endl;
    }
    return os;
}

void dfs(const Table &t, Table &res)
{
    if (t.full()) {
        if (t.imperfict() < res.imperfict())
            res = t;
        return;
    }

    auto p = t;
    for (int &i : p.table) {
        if (i != 0)
            continue;
        for (int x = 1; x <= 9; ++x) {
            bool used = false;
            for (int j : p.table)
                if (x == j)
                    used = true;
            if (used)
                continue;

            i = x;
            dfs(p, res);
        }
        break;
    }
}

Table solve(const Table &table)
{
    Table res;
    dfs(table, res);
    return res;
}

int main()
{
    Table t;
    std::cin >> t;
    auto res = solve(t);
    std::cout << res << res.imperfict();
    return EXIT_SUCCESS;
}
