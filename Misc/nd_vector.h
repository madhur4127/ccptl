/*
 * Create a N-D vector with given dimensions
 * Source: https://codeforces.com/blog/entry/76149
 */

// C++17 version (short)
template <class T, class... Args>
auto create(int n, Args &&... args) {
    if constexpr (sizeof...(args) == 1)
        return vector<T>(n, args...);
    else
        return vector(n, create<T>(args...));
}
/*
 * Usage:
 *   auto nd_vector = create<int>(D1, D2, ... , init);
 */

// --------------------------------------------------------------

// C++14 version
template <int D, typename T>
struct Vec : public vector<Vec<D - 1, T>> {
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template <typename... Args>
    Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {
    }
};
template <typename T>
struct Vec<1, T> : public vector<T> {
    Vec(int n = 0, const T &val = T()) : vector<T>(n, val) {
    }
};

/* 
 * Usage: 
 *   Vec<2, int> a(10, 50); // int a[10][50] initialized with zero
 *   Vec<3, double> b(n, m, k, 3.14); // double b[n][m][k] initialized with 3.14
 *   Vec<3, long long> c(5, 5); // the third dimension has no value yet
 *   c[0][0].push_back(100); // now c[0][0][0] has a value (100) but others don't
 *   Vec<4, int> d(10, 10);
 *   d[2][3].push_back(Vec<1, int>(100, 12345)); // now d[2][3][0] is a vector with 100 values of 12345
 *   Vec<1, string> e; // just blank vector of strings
 */
