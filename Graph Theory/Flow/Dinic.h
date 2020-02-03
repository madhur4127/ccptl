/*
 * Author : cp-algorithms.com
 * Use : Finding maximum flow in a graph
 * Time Complexity : O((V^2)*E) for general graphs, O(E*sqrt(V)) for graphs with unit edge capacties
 * Space Complexity: O(V+E)
 * Usage Notes: For adding unidirectional edge from u to v with capacity c use add_edge(u, v, c)
 *              For adding bidirectional edge from u to v with capacity c use add_edge(u, v, c, c)
 *              Flow along an edge is stored in the 'flow' member variable after flow() has been called
 *		When using for min cut, left half of the cut is formed by nodes whoose level != -1 after flow()
 */

struct Dinic {

    struct FlowEdge {
        int v, u;
        long long cap, flow = 0;

        FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
    };

    const long long flow_inf = 1e18;
    vector <FlowEdge> edges;
    vector <vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap, long long rcap = 0) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, rcap);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int &cid = ptr[v]; cid < (int) adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
