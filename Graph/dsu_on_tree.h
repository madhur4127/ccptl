/*
 * Optimized version of DSU on tree.
 * Based on tutorial by Arpa: https://codeforces.com/blog/entry/44351
 * Can be used inside - main() and requires adjacency list of vertex u in: adj[u]
 */

//
// pre-processing
//
vector<int> subtree_size(n), // size of subtree rooted at i'th node
    start(n), finish(n),     // start[i] + subtree_size[i] = finish[i]
    at_time(n);              // node visited at time i

function<int(int, int)> preprocess = [&](int u, int par) {
    static int time = 0;
    subtree_size[u] = 1;
    at_time[time] = u;
    start[u] = time++;
    for (auto v : adj[u]) {
        if (v != par) subtree_size[u] += preprocess(v, u);
    }
    finish[u] = time;
    return subtree_size[u];
};

preprocess(root, -1);

vector<int> cnt(number_of_colors, 0); // cnt[i]: number of vertices of i'th color
function<void(int, int)> dsu_on_tree = [&](int u, int par) {
    int big_ch = -1, mx = -1;
    for (auto v : adj[u])
        if (v != par && subtree_size[v] > mx) mx = subtree_size[v], big_ch = v;
    for (auto v : adj[u]) {
        if (v == par || v == big_ch) continue;
        dsu_on_tree(v, u);
        // remove child's subtree from cnt
        for (int time = start[v]; time < finish[v]; ++time) {
            cnt[color[at_time[time]]]--; // CHANGE
        }
    }

    // Union step: make big_ch to be the root (instead of u) of subtree rooted at u
    if (big_ch != -1)
        dsu_on_tree(big_ch, u);

    // make children of u as children of big_ch
    for (auto v : adj[u]) {
        if (v == par || v == big_ch) continue;
        for (int time = start[v]; time < finish[v]; ++time) {
            cnt[color[at_time[time]]]++; // CHANGE
        }
    }
    cnt[color[u]]++; // CHANGE

    // Answer queries here for subtree (previously) of u, cnt[c]: #vertices with color c
    for (auto &[req, idx] : queries) {
        ans[idx] = cnt[req]; // #vertices with color 'req' in subtree of u
    }
};
dsu_on_tree(root, -1);
