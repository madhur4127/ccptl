/*
 * Author: Madhur Chauhan
 * Use: Finding GCD and solving a, b, d for m, n:
 *                         a * m + b * n = d = gcd(m,n) [return value]
 * Time Complexity: O(log N) with very small constant
 * Features: 50% faster than recursive implementation
 * Notes: 1. gcd_fast is iterative
 *        2. gcd_slow is recursive
 *        3. Based on Knuth's TAOPC, Vol 1, Section 1.2.1, Algorithm E
 */

//
// Iterative, Faster version
//
#include <tuple>
int gcd_fast(int m, int n, int &a, int &b) {
    if (!n) {
        a = 1, b = 0;
        return m;
    }
    int a_ = 1, b_ = 0, c = m, d = n, q = m / n, r = m % n;
    for (a = 0, b = 1; r; q = c / d, r = c % d) {
        c = d;
        d = r;
        std::tie(a, a_) = std::make_tuple(a_ - q * a, a);
        std::tie(b, b_) = std::make_tuple(b_ - q * b, b);
    }
    return d;
}

//
// Recursive, Slower version
//
int gcd_slow(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd_slow(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
