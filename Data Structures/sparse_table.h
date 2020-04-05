/*
* Author: Madhur Chauhan
* Use: Static DS which requires O(N logN) preprocessing after which queries
*      can be answered very fast - O(1) for some functions.
* Time Complexity: 
*       O(NlogN) to build
*       O(1) or O(logN) for query (depends on function)
* Space Complexity: O(NlogN)
* Notes: 1. An example operation class is shown (compare_min), replace "min" with your desired operation.
*           Create a different class for each operation or use STLs function objects: plus<int>, less<int>, etc.
*        2. query_fast is O(1) and is useful when queries can be answered by two *overlapping* ranges.
*           Examples: min, max, gcd and NOT sum.
*        3. query_slow is O(logN) and is useful for rest of the functions like sum.
* Usage:
*       SparseTable<int, compare_min> st(vec);  // constructs sparse table from vec (vector<int>)
*       st.query(left, right);       // Query range: [left,right] in O(logN)
*       st.query_fast(left, right);  // Query range: [left,right] in O(1)
* Status: Tested
*/

template <typename T>
struct compare_min {
    const T constexpr operator()(const T &a, const T &b) const {
        return min(a, b);
    }
};
template <typename T, class F = plus<T>>
class sparse_table {
  public:
    sparse_table(const vector<T> &v) {
        int N = v.size();
        for (int s = 1; s < N; s <<= 1)
            K++;
        st.assign(K, vector<T>(N));
        copy(begin(v), end(v), begin(st[0]));
        for (int j = 1; j <= K; ++j)
            for (int i = 0; i + (1 << j) <= N; ++i)
                st[j][i] = _op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }

    T query_fast(int l, int r) { // 0-based interval: [l,r]
        int dep = 31 - __builtin_clz(r - l + 1);
        return _op(st[dep][l], st[dep][r - (1 << dep) + 1]);
    }

    // O(log N)/query
    T query(int l, int r) { // 0-based interval: [l,r]
        T ans = st[0][l++];
        for (int j = K; j >= 0; j--) {
            if ((1 << j) <= r - l + 1) {
                ans = op(ans, st[j][l]);
                l += 1 << j;
            }
        }
        return ans;
    }

  private:
    vector<vector<T>> st;
    int K = 1; // K = ceil(log(N))
    const F _op = F();
};
