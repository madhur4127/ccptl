# CCPTL
CodeISM Competitve Programming Template Library

## Aim
The aim of this repository is to provide copy-pastable code snippets. Focus is more on efficiency/performance as opposed to readability.

## Usage
Code snippets in a file is meant to be self sufficient so no addtional requirements.

Note: A modern C++ compiler with support of `c++14` or later is required although most the files might work with lower versions too. 

Desired version of C++ standard can be enabled by passing `-std=c++14` to most of the compilers.

## Directory
### Data Structures
- [Binary Indexed Tree (BIT) / Fenwick Tree](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/BIT.h): Supports prefix queries and point update in O(log N) after taking O(N) time to build with O(N) space.
- [Min Deque](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/min_deque.h): Finding minimum element out of current element in the deque. Overhead of one integer per element, but is quite space efficient in practice.
- [Ordered set](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/ordered_set.h): Dyanmic Order statistics in O(log N). Uses GNU's policy based data structure (pbds).
- [Sparse Table](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/sparse_table.h): Static data structure that can answer queries in O(1) after O(NlogN) preprocessing (for some functions).

### Graph
- [2-SAT](https://github.com/CodeISM/ccptl/blob/master/Graph/2SAT.h): solves 2-SAT problem in O(#boolean variables + #clauses) with CNF based formulation.
### Math
#### Number Theory
- [Wheel Factorization](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/wheel_factorization.h): 25% faster than sqrt(n) trial division
- [GCD (Greatest Common Divisor)](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/gcd.h): Iterative/Compile time constant
- [Extended Euclid](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/extended_euclid.h): iterative version, much faster than recursive.
- [Modular Exponentiation](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/modular_exponentiation.h): constexpr version.
#### Combinatorics
- Combinations (nCr)
#### Linear Algebra
- [Matrix](https://github.com/CodeISM/ccptl/blob/master/Linear%20Algebra/matrix.h): highly optimized: multiplication, exponentiation, transpose including versions with modular arithmetic.

### Dynamic Programming
### String Algorithms
### Misc
- [Ska Sort](https://github.com/CodeISM/ccptl/blob/master/Misc/ska_sort.h): A much faster (2x w.r.t. std::sort) sorting algorithm.
- [All Permutations](https://github.com/CodeISM/ccptl/blob/master/Misc/all_permutations.h): Generate all permutations of a sequence (iterative) in some order (not lexicographic).

## Contribution
Feel free to open an issue or fire a pull request!

## TODO
- Update this readme with new (updated) content
- Test the implementation for bugs

## License

## Authorship
Many of the implementations are common in folklore of competitive programming and the authour is unknown. Whenever possible author of the code is added. Kindly contact us in case of any issues.

