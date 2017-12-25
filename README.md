# Advent of Code 2017
My solutions for AoC 2017. I did not aim to compete on the leaderboards
(i.e. my solutions tend to be a lot more verbose than what you would
write when trying to finish as quickly as possible), I simply used this
as an opportunity to write some (modern) C++ again.

## Prerequisites

- CMake (3.8 or newer should work)
- Compiler supporting C++17 (I used GCC 7.2 myself and also tested with
  Visual Studio 2017).
- All code is solely based on the STL, no additional libraries needed.

## Overview

- Running the executable without any arguments will simply execute the
  solution for each and every day.
- `1` to `25` can be used as command line arguments to only execute the
  solution(s) of the respective day(s).
- The argument `b` can be used to invoke a small 'benchmark'. This will
  execute each solution 100 times and determine minimum, maximum, and
  average run time.

### Benchmark Results
When running the benchmark function on my machine (Intel i7-7500U @
2.7GHz, Windows 10 64-bit), I got the following results:

```
+----------+---------------+---------------+---------------+
| Solution | Min Time (ms) | Avg Time (ms) | Max Time (ms) |
+----------+---------------+---------------+---------------+
|  Day01   |       0.00000 |       0.00000 |       0.00000 |
|  Day02   |       0.00000 |       0.15628 |      15.62760 |
|  Day03   |       0.00000 |       0.00000 |       0.00000 |
|  Day04   |       0.00000 |       1.87573 |      15.69390 |
|  Day05   |      62.45930 |      72.81952 |      78.18150 |
|  Day06   |       0.00000 |       3.28161 |      15.66570 |
|  Day07   |       0.00000 |       1.71826 |      15.62900 |
|  Day08   |       0.00000 |       0.93794 |      15.66080 |
|  Day09   |       0.00000 |       0.31219 |      15.61490 |
|  Day10   |       0.00000 |       0.15632 |      15.63180 |
|  Day11   |       0.00000 |       0.46873 |      15.62730 |
|  Day12   |       0.00000 |       2.50027 |      15.63190 |
|  Day13   |      15.58430 |      26.87823 |      31.29580 |
|  Day14   |       0.00000 |       7.65717 |      15.68930 |
|  Day15   |     296.85920 |     314.57023 |     328.20760 |
|  Day16   |      15.59310 |      24.69076 |      31.29510 |
|  Day17   |     421.91730 |     428.48279 |     453.17420 |
|  Day18   |       0.00000 |       2.34440 |      15.67140 |
|  Day19   |       0.00000 |       0.62470 |      15.62830 |
|  Day20   |      78.06510 |      78.60206 |      93.76080 |
|  Day21   |      93.72020 |     101.88577 |     109.42580 |
|  Day22   |     281.20980 |     284.24885 |     312.53520 |
|  Day23   |      78.09190 |      87.04042 |      93.80140 |
|  Day24   |     124.96810 |     136.88948 |     140.70860 |
|  Day25   |       0.00000 |      14.68867 |      15.69710 |
+----------+---------------+---------------+---------------+
```

This was when compiling with GCC v7.2 (-O3 -march=native).

With Visual Studio 2017 I got the following results (worse run times
across the board):

```
+----------+---------------+---------------+---------------+
| Solution | Min Time (ms) | Avg Time (ms) | Max Time (ms) |
+----------+---------------+---------------+---------------+
|  Day01   |       0.04549 |       0.04961 |       0.10261 |
|  Day02   |       0.19041 |       0.19748 |       0.27998 |
|  Day03   |       0.02010 |       0.02240 |       0.03773 |
|  Day04   |       2.66614 |       2.76332 |       3.71235 |
|  Day05   |     135.06879 |     135.44820 |     137.94192 |
|  Day06   |       4.11045 |       4.28127 |       4.68628 |
|  Day07   |       2.72925 |       2.80057 |       3.32130 |
|  Day08   |       2.35372 |       2.39939 |       2.62276 |
|  Day09   |       1.64178 |       1.68478 |       2.47678 |
|  Day10   |       0.11742 |       0.13666 |       0.21862 |
|  Day11   |       0.56419 |       0.59471 |       0.75354 |
|  Day12   |       3.77582 |       3.89276 |       5.49060 |
|  Day13   |      31.23091 |      32.45589 |      33.03455 |
|  Day14   |       7.30728 |       7.56851 |      10.66207 |
|  Day15   |    1177.58838 |    1187.67891 |    1201.74299 |
|  Day16   |      40.54493 |      40.99844 |      42.49103 |
|  Day17   |     427.00692 |     428.06277 |     431.79581 |
|  Day18   |       1.83502 |       1.90281 |       2.15378 |
|  Day19   |       0.45417 |       0.46845 |       0.60403 |
|  Day20   |      95.03903 |      95.52701 |      97.40932 |
|  Day21   |     246.97525 |     248.19577 |     250.69360 |
|  Day22   |     423.09111 |     426.62988 |     460.46708 |
|  Day23   |      72.14081 |      72.61846 |      75.22197 |
|  Day24   |     155.45110 |     155.88400 |     158.97445 |
|  Day25   |      56.45007 |      56.69644 |      57.29106 |
+----------+---------------+---------------+---------------+
```

## Missing / Alternative Solutions

### Day 3
Initially I wrote a small C program for part 1. I did not bother to make
a C++ version of this (it's trivial once you figure out that you can
simply count up from the bottom right square).

### Day 4
I wrote a solution for both parts in C++. But my first solution of part
1 was this bash one-liner:

```shell
sed -re "/\<(\w+)\>.*\<\1\>/d" input.txt | wc -l
```

### Day 7 (Part 1)
I did not write any code for part 1. I solved it just by searching in my
text editor. The following key sequence (vim) will most likely solve the
part 1 for most input files of this day:

```
qq0*q100@q
```
