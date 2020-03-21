/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (~x).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.solve(); // Returns pair<return status, solution> where return status is true if the constraints are satisfiable.
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 */

#include <vector>
struct TwoSat {
    TwoSat(int n = 0) : N(n), gr(2 * n), fixed(2 * n) {}

    int add_var() { // (optional)
        gr.emplace_back();
        gr.emplace_back();
        fixed.emplace_back();
        fixed.emplace_back();
        return N++;
    }
    void addOr(int f, int j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].push_back(j ^ 1);
        gr[j].push_back(f ^ 1);
    }
    void addImplication(int f, int j) {
        addOr(~f, j);
    }
    void setTrue(int x) {
        addOr(x, x);
        fixed[max(2 * x, -1 - 2 * x)] = 1;
    }

    void atMostOneTrue(const std::vector<int> &li) { // (optional)
        if ((li.size()) <= 1) return;
        int cur = ~li[0];
        for (int i = 2; i < li.size(); i++) {
            int next = add_var();
            addOr(cur, ~li[i]);
            addOr(cur, next);
            addOr(~li[i], next);
            cur = ~next;
        }
        addOr(cur, ~li[1]);
    }

    int dfs(int i) {
        int low = val[i] = ++time, x;
        z.push_back(i);
        for (auto e : gr[i])
            if (!comp[e])
                low = min(low, val[e] ?: dfs(e));
        if (low == val[i]) {
            bool ans = false;
            for (auto x = z.end() - 1; (*x) != i; x--) {
                int v = ((*x) >> 1) << 1;
                if (fixed[v] || fixed[v ^ 1]) {
                    ans = true;
                    break;
                }
            }
            do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if (values[x >> 1] == -1)
                    values[x >> 1] = (x & 1) ^ ans;
            } while (x != i);
        }
        return val[i] = low;
    }

    pair<bool, std::vector<int>> solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        for (int i = 0; i < 2 * N; i++)
            if (!comp[i]) dfs(i);
        for (int i = 0; i < N; i++)
            if (comp[2 * i] == comp[2 * i + 1])
                return {0, {}};
        return {1, values};
    }

  private:
    std::vector<int> val, comp, z, fixed;
    int time = 0, N;
    std::vector<std::vector<int>> gr;
    std::vector<int> values; // 0 = false, 1 = true
};
