/*
 * Author: Madhur Chauhan, Ankur Dua
 * Use: Easy and expressive matrix operations
 * Features: Highly optimized for modular arithmetic and matrix multiplication, matrix exponentiation
 * Time Complexity: O(N^3) cache-efficient matrix multiplication
 * Notes: 1. Use Modular class from modular.h to take advantage of optimized modular arithmetic
 *        2. There are helper member functions like transpose, mexp (modular exponentiation)
 * Status: Tested: Modular exponentiation, Rest of the operations are pending
 */

template <typename T>
struct matrix_base : public vector<vector<T>> {
    matrix_base(int r, int c, T init = 0) : vector<vector<T>>(r, vector<T>(c, init)), rows{r}, columns{c} {}

    matrix_base constexpr operator+(const matrix_base &o) const {
        matrix_base ret(rows, columns);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                ret[i][j] = (*this)[i][j] + o[i][j];
        return ret;
    }
    matrix_base constexpr operator-(const matrix_base &o) const {
        matrix_base ret(rows, columns);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                ret[i][j] = (*this)[i][j] - o[i][j];
        return ret;
    }
    matrix_base constexpr &operator+=(const matrix_base &o) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                (*this)[i][j] += o[i][j];
        return *this;
    }
    matrix_base constexpr &operator-=(const matrix_base &o) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                (*this)[i][j] -= o[i][j];
        return *this;
    }
    matrix_base transpose() const {
        const int BLOCKSIZE = 32;
        matrix_base ret(columns, rows);
        for (int i = 0; i < rows; i += BLOCKSIZE)
            for (int j = 0; j < columns; j += BLOCKSIZE)
                for (int k = i, lim_k = min(rows, i + BLOCKSIZE); k < lim_k; ++k)
                    for (int l = j, lim_l = min(columns, j + BLOCKSIZE); l < lim_l; ++l)
                        ret[l][k] = (*this)[k][l];
        return ret;
    }

  public: // Data Members
    int rows, columns;
};

template <typename T>
struct matrix : public matrix_base<T> {
    using base_type = matrix_base<T>;

    matrix(int r, int c, T init = 0) : base_type(r, c, init) {}

    matrix const operator*(const matrix &o) const {
        base_type tp = o.transpose();
        int x = this->rows, y = this->columns, z = o.rows;
        matrix ret(x, z);
        for (int i = 0; i < x; ++i)
            for (int j = 0; j < z; ++j)
                for (int k = 0; k < y; ++k)
                    ret[i][j] += (*this)[i][k] * tp[j][k];

        return ret;
    }

    matrix &operator*=(const matrix &o) {
        (*this) = (*this) * o;
        return *this;
    }
};

template <int MOD>
struct matrix<Modular<MOD>> : matrix_base<Modular<MOD>> {
    using base_type = matrix_base<Modular<MOD>>;

    matrix(int r, int c, Modular<MOD> init = 0) : base_type(r, c, init) {}

    matrix constexpr operator*(const matrix &o) const {
        // Don't change this if you don't know how this works
        base_type tp = o.transpose();
        int x = this->rows, y = this->columns, z = o.rows;
        matrix ret(x, z);
        const int64_t base = mexp(Modular<MOD>(2), 64).value;
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < z; ++j) {
                uint64_t s = 0;
                uint32_t carry = 0;
                for (int k = 0; k < y; ++k) {
                    auto cur = s;
                    s += static_cast<uint64_t>((*this)[i][k].value) * static_cast<uint64_t>(tp[j][k].value);
                    carry += cur > s;
                }
                ret[i][j] = ((s % MOD) + base * carry) % MOD;
            }
        }
        return ret;
    }

    matrix &operator*=(const matrix &o) {
        (*this) = (*this) * o;
        return *this;
    }
};
template <typename T>
matrix<T> mexp(matrix<T> a, long long e) {
    assert(a.rows == a.columns);
    int n = a.rows;
    matrix<T> ret(n, n, 0);
    for (int i = 0; i < n; ++i)
        ret[i][i] = 1;
    while (e) {
        if (e % 2) ret *= a;
        a *= a;
        e >>= 1;
    }
    return ret;
}
