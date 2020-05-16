/*
 * Author: Madhur Chauhan, Ankur Dua
 * Use: Easy and expressive matrix operations
 * Features: Highly optimized for modular arithmetic and matrix multiplication, matrix exponentiation
 * Time Complexity: O(N^3) cache-efficient matrix multiplication
 * Notes: 1. Use Modular class from modular.h to take advantage of optimized modular arithmetic
 *        2. There are helper member functions like transpose, mexp (modular exponentiation)
 *        3. To access element from ith row and jth column use syntax: mat(i,j)
 *        4. Initialize with R rows and C columns: matrix mat(R, C [, init]); 
 *           Passing of init is optional, if provided all elements are initialized with init.
 * Status: Tested: Modular exponentiation, Matrix multiplication
 */

template <typename T>
struct matrix_base : public dynamic_matrix<T> {
    using base_type = dynamic_matrix<T>;
    using base_type::C;
    using base_type::R;

    constexpr matrix_base
    operator+(const matrix_base &other) const {
        matrix_base ret(R, C);
        scan(ret, *this, other, plus<T>());
        return ret;
    }
    constexpr matrix_base &operator+=(const matrix_base &other) {
        scan(*this, *this, other, plus<T>());
        return *this;
    }
    constexpr matrix_base operator-(const matrix_base &other) const {
        matrix_base ret(R, C);
        scan(ret, *this, other, minus<T>());
        return ret;
    }
    constexpr matrix_base &operator-=(const matrix_base &other) {
        scan(*this, *this, other, minus<T>());
        return *this;
    }

    constexpr matrix_base transpose() const {
        const int32_t BLOCKSIZE = 64 / sizeof(T);
        matrix_base ret(C, R);
        for (int32_t i = 0; i < R; i += BLOCKSIZE)
            for (int32_t j = 0; j < C; j += BLOCKSIZE)
                for (int32_t k = i, lim_k = min(R, i + BLOCKSIZE); k < lim_k; ++k)
                    for (int32_t l = j, lim_l = min(C, j + BLOCKSIZE); l < lim_l; ++l)
                        ret(l, k) = (*this)(k, l);
        return ret;
    }

    template <typename F> // F must be a callable type, used as universal/forwaring reference
    constexpr void scan(matrix_base &lhs, const matrix_base &op1, const matrix_base &op2, F &&f) const {
        for (int32_t i = 0; i < R; ++i)
            for (int32_t j = 0; j < C; ++j)
                lhs(i, j) = f(op1(i, j), op2(i, j));
    }
};

template <typename T>
struct matrix : public matrix_base<T> {
    using base_type = matrix_base<T>;
    matrix(const int32_t r, const int32_t c, T init = 0) : base_type(r, c, init) {}
    matrix(base_type &&other) : base_type(other) {}

    constexpr matrix operator*(const matrix &o) const {
        base_type tp = o.transpose();
        int32_t x = base_type::R, y = base_type::C, z = o.R;
        matrix ret(x, z);
        for (int32_t i = 0; i < x; ++i)
            for (int32_t j = 0; j < z; ++j)
                for (int32_t k = 0; k < y; ++k)
                    ret(i, j) += (*this)(i, k) * tp(j, k);
        return ret;
    }

    constexpr matrix &operator*=(const matrix &o) {
        (*this) = (*this) * o;
        return *this;
    }
};

template <int MOD> // template specialization
struct matrix<Modular<MOD>> : matrix_base<Modular<MOD>> {
    using base_type = matrix_base<Modular<MOD>>;
    matrix(int32_t r, int32_t c, Modular<MOD> init = 0) : base_type(r, c, init) {}
    matrix(base_type &&other) : base_type(other) {}

    constexpr matrix operator*(const matrix &o) const {
        // Don't change this if you don't know how this works
        base_type tp = o.transpose();
        int32_t x = base_type::R, y = base_type::C, z = o.R;
        matrix ret(x, z);
        const uint64_t base = mexp(Modular<MOD>(2), 64).value;
        for (int32_t i = 0; i < x; ++i) {
            for (int32_t j = 0; j < z; ++j) {
                uint64_t s = 0;
                uint32_t carry = 0;
                for (int32_t k = 0; k < y; ++k) {
                    auto cur = s;
                    s += (*this)(i, k).value * static_cast<uint64_t>(tp(j, k).value);
                    carry += s < cur;
                }
                ret(i, j) = ((s % MOD) + base * carry) % MOD;
            }
        }
        return ret;
    }

    constexpr matrix &operator*=(const matrix &o) {
        (*this) = (*this) * o;
        return *this;
    }
};
template <typename T>
matrix<T> mexp(matrix<T> a, int64_t e) {
    // assert(a.R == a.C);
    int32_t n = a.R;
    matrix<T> ret(n, n, 0);
    for (int32_t i = 0; i < n; ++i)
        ret(i, i) = 1;
    while (e) {
        if (e % 2) ret *= a;
        a *= a, e >>= 1;
    }
    return ret;
}
