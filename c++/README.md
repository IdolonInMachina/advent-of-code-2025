# Advent of Code 2025 - C++

Solutions for Advent of Code 2025 challenges implemented in C++20.

Program structure written with the help of AI, but solutions are all my own work.

## Compilation

```bash
c++ -std=c++20 -O2 -Wall -Wextra -Iinclude main.cpp src/day01.cpp src/day02.cpp src/day03.cpp -o aoc
```
Extend this command with additional source files as written. A Makefile or CMakeLists.txt might be added in the future for easier compilation.

## Usage

Run a specific day's solution:

```bash
./aoc --day 3 --input inputs/day03.txt
```

Run with timing:

```bash
./aoc --day 3 --input inputs/day03_sanity_check.txt --time
```

Run a specific part only:

```bash
./aoc --day 3 --part 1 --input inputs/day03.txt
```
