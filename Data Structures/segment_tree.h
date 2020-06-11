// https://codeforces.com/blog/entry/18051 by AI.Cash

template <typename T>
struct op {
    constexpr T operator()(const T &a, const T &b) const {
        return a + b;
    }
};
template <typename T, class F = op<T>>
struct segment_tree {
    segment_tree(int32_t sz, T init) : N{sz}, t(2 * N, init) {} // initialze a segment tree with value -- init
    segment_tree(const vector<T> &v) : N{(int32_t)v.size()}, t(2 * N) {
        copy(begin(v), end(v), begin(t) + N);
        for (int32_t i = N - 1; i > 0; --i)
            t[i] = op(t[i << 1], t[i << 1 | 1]);
    }
    void update(int p, T value) { // set value at position p
        for (t[p += N] = value; p > 1; p >>= 1)
            t[p >> 1] = op(t[p], t[p ^ 1]);
    }
    T query(int l, int r) { // sum on interval [l, r)
        T res = t[N + l];
        for (l += N + 1, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = op(res, t[l++]);
            if (r & 1) res = op(res, t[--r]);
        }
        return res;
    }

    int32_t N;
    vector<T> t;
    F op = F();
};
