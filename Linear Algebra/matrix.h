/*
 * Author: Madhur Chauhan, Ankur Dua
 * Use: Easy and expressive matrix operations
 * Features: Highly optimized for modular arithmetic and matrix multiplication, matrix exponentiation
 * Time Complexity: O(N^3) cache-efficient matrix multiplication
 * Notes: 1. Use Modular class from modular.h to take advantage of optimized modular arithmetic
 *        2. There are helper functions like transpose, mexp (modular exponentiation)
 *        3. To access element from ith row and jth column use syntax: mat(i,j)
 *        4. Initialize with R rows and C columns: matrix mat(R, C [, init]); 
 *           Passing of init is optional, if provided all elements are initialized with init.
 *        5. cout<<mat; prints the matrix in row-major form
 * Status: Tested: Modular exponentiation, Matrix multiplication
 */

#include "Data Structures/dynamic_matrix.h"
template <typename T>
using matrix = dynamic_matrix<T>;

template <typename T>
matrix<T> operator+(const matrix<T> &a, const matrix<T> &b) {
    matrix<T> ret(a.R, a.C);
    scan(ret, a, b, plus<T>());
    return ret;
}
template <typename T>
matrix<T> operator+=(matrix<T> &a, const matrix<T> &b) {
    scan(a, a, b, plus<T>());
    return a;
}
template <typename T>
matrix<T> operator-(const matrix<T> &a, const matrix<T> &b) {
    matrix<T> ret(a.R, a.C);
    scan(ret, a, b, minus<T>());
    return ret;
}
template <typename T>
matrix<T> operator-=(matrix<T> &a, const matrix<T> &b) {
    scan(a, a, b, minus<T>());
    return a;
}
template <typename T>
matrix<T> transpose(const matrix<T> &a) {
    const int32_t BLOCKSIZE = 64 / sizeof(T);
    matrix<T> ret(a.C, a.R);
    for (int32_t i = 0; i < a.R; i += BLOCKSIZE)
        for (int32_t j = 0; j < a.C; j += BLOCKSIZE)
            for (int32_t k = i, lim_k = min(a.R, i + BLOCKSIZE); k < lim_k; ++k)
                for (int32_t l = j, lim_l = min(a.C, j + BLOCKSIZE); l < lim_l; ++l)
                    ret(l, k) = a(k, l);
    return ret;
}
template <typename T, typename F> // F must be a callable type, used as universal/forwaring reference
void scan(matrix<T> &lhs, const matrix<T> &op1, const matrix<T> &op2, F &&f) {
    for (int32_t i = 0; i < lhs.R; ++i)
        for (int32_t j = 0; j < lhs.C; ++j)
            lhs(i, j) = f(op1(i, j), op2(i, j));
}
template <typename T>
matrix<T> operator*(const matrix<T> &a, const matrix<T> &b) {
    matrix<T> tp = transpose(b);
    int32_t x = a.R, y = a.C, z = b.C;
    matrix<T> ret(x, z);
    for (int32_t i = 0; i < x; ++i)
        for (int32_t j = 0; j < z; ++j)
            for (int32_t k = 0; k < y; ++k)
                ret(i, j) += a(i, k) * tp(j, k);
    return ret;
}

template <typename T>
matrix<T> &operator*=(matrix<T> &a, const matrix<T> &b) { return a = a * b; }

template <typename T>
matrix<T> mexp(matrix<T> a, int64_t e) {
    int32_t n = a.R; // assert(a.R == a.C);
    matrix<T> ret(n, n, 0);
    for (int i = 0; i < n; ++i)
        ret(i, i) = 1;
    while (e) {
        if (e % 2) ret *= a;
        a *= a, e >>= 1;
    }
    return ret;
}
// If you're not using matrix of "modular" int, this is not needed
#include "Misc/modular.h"
template <int MOD>
matrix<Modular<MOD>> operator*(const matrix<Modular<MOD>> &a, const matrix<Modular<MOD>> &b) {
    auto tp = transpose(b);
    int32_t x = a.R, y = a.C, z = b.R;
    matrix<Modular<MOD>> ret(x, z);
    const uint64_t base = mexp(Modular<MOD>(2), 64).value;
    for (int32_t i = 0; i < x; ++i) {
        for (int32_t j = 0; j < z; ++j) {
            uint64_t s = 0;
            uint32_t carry = 0;
            for (int32_t k = 0; k < y; ++k) {
                auto cur = s;
                s += a(i, k).value * static_cast<uint64_t>(tp(j, k).value);
                carry += s < cur;
            }
            ret(i, j) = ((s % MOD) + base * carry) % MOD;
        }
    }
    return ret;
}
