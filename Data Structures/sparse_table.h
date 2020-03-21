/*
* Author: Madhur Chauhan
* Use: Static DS which requires O(N logN) preprocessing further which queries
*      can be answered very fast - O(1) for some functions.
* Time Complexity: 
*       O(NlogN) to build
*       O(1) or O(logN) for query (depends on function)
* Space Complexity: O(NlogN)
* Usage:
*       SparseTable<int> st(vec);  // constructs sparse table from vec (vector<int>)
*       st.query(left, right);     // Query range: [left,right] in O(logN)
*       st.query_fast(left, right);// Query range: [left,right] in O(1)
*/

template <class T = int>
struct SparseTable {
    vector<vector<T>> st;
    int K = 1; // K = ceil(log(N))

    SparseTable(const vector<T> &V) {
        int N = V.size();
        for (int s = 1; s < N; s <<= 1)
            K++;
        st.assign(K, V);
        for (int j = 1; j <= K; ++j)
            for (int i = 0; i + (1 << j) <= N; ++i)
                // using f(X,Y) = min(X, Y)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]); // CHANGE THIS FUNCTION (from min to other)
    }

    // O(1)/query: functions where duplicates does not matter
    //             f(a[x-1], a[x], a[x], a[x], a[x+1]) = f(a[x-1], a[x], a[x+1])
    // Examples: min, max, gcd and NOT: sum (duplicates matter)
    T query_fast(int l, int r) {
        assert(l <= r);
        int dep = 31 - __builtin_clz(r - l + 1);             // GCC specific
        return min(st[dep][l], st[dep][r - (1 << dep) + 1]); // CHANGE THIS FUNCTION (from min to other)
    }

    // O(log N)/query
    T query(int l, int r) {
        assert(l <= r);
        long long ans = 1e17; // CHANGE: WHAT TO RETURN ON EMPTY INTERVAL
        for (int j = K; j >= 0; j--) {
            if ((1 << j) <= r - l + 1) {
                ans = min(ans, st[j][l]); // CHANGE THIS FUNCTION (from min to other)
                l += 1 << j;
            }
        }
        return ans;
    }
};
