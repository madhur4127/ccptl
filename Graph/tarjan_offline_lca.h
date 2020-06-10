// Name: Tarjan offline LCA algorithm
// Author: Madhur Chauhan, Wikipedia
// Usage: Offline LCA algorithm based on DSU and is linear in number of queries
// Time Complexity: O(DFS + Q), where O(DFS) is the DFS time complexity (O(V+E))
// Space Complexity: O(DFS + Q)
// Notes: 1. For every query {u,v}:
//              queries[u].push_back({v,index});
//				queries[v].push_back({u,index});
//        2. Answer to query {u,v} will be in "index" of the vector returned

#include "Data Structures/DSU.h"
struct query {
    int32_t v, index;
};
vector<int32_t> tarjan_lca(const vector<vector<int32_t>> &adj,
                           const vector<vector<query>> queries, // for {u,v} do: queries[u].push_back({v, index}), queries[v].push_back({u,index});
                           int nq) {                            // nq is number of queries
    int n = adj.size();
    vector<int32_t> ret(nq), par(n);
    DSU d(n);
    iota(begin(par), end(par), 0);
    vector<bool> vis(n, false);
    function<void(int, int)> dfs = [&](int u, int p = -1) {
        for (auto &v : adj[u]) {
            if (v == p) continue;
            dfs(v, u), d.join(u, v), par[d.find(u)] = u;
        }
        vis[u] = true;
        for (auto &qu : queries[u]) {
            if (vis[qu.v]) ret[qu.index] = par[d.find(qu.v)];
        }
    };
    dfs(0, -1); // ASSUMES 0 AS THE ROOT OF THE TREE
    return ret;
}
