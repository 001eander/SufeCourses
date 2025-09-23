@echo off

g++ task1.cpp -o task1 -std=c++20 -O2 -Wall -Wshadow
echo --- Task 1 ---
task1

pause

g++ task2.cpp -o task2 -std=c++20 -O2 -Wall -Wshadow
echo --- Task 2 ---
task2

pause

g++ task3.cpp -o task3 -std=c++20 -O2 -Wall -Wshadow
echo --- Task 3 ---
task3

pause

g++ task4.cpp -o task4 -std=c++20 -O2 -Wall -Wshadow
task4

echo --- Task 4 Results ---
echo -- ints.txt --
type ints.txt
echo -- string.txt --
type string.txt
echo -- doubles.txt --
type doubles.txt

pause

del task*.exe