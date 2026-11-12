MOBILE MONEY AGENT TRANSACTION LOG

MODULE:
BCS 2204 - DATA STRUCTURES AND ALGORITHMS

LANGUAGE:
C++17

PRIMARY DATA STRUCTURE:
Singly Linked List with Head and Tail Pointers.

ALGORITHMS:
1. Insertion Sort
2. Merge Sort
3. Iterative Binary Search

COMPILE MAIN PROGRAM:
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o mobile_money

RUN MAIN PROGRAM:
./mobile_money

COMPILE TESTS:
g++ -std=c++17 -Wall -Wextra -pedantic tests.cpp -o tests

RUN TESTS:
./tests

COMPILE ADDRESS SANITIZER:
g++ -std=c++17 -g -fsanitize=address -fno-omit-frame-pointer tests.cpp -o tests_asan

RUN ADDRESS SANITIZER:
./tests_asan

COMPILE BENCHMARK:
g++ -std=c++17 -O2 -Wall -Wextra -pedantic benchmark.cpp -o benchmark

RUN BENCHMARK:
./benchmark > timing_results.csv

The transactions.txt file must be in the same directory
as the executable when running the application.