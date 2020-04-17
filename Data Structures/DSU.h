//DSU with union by rank heuristics
class DSU {
  public:
    int *p, *r;
    DSU(int n) {
        p = new int[n + 50];
        r = new int[n + 50];
        for (int i = 0; i < n + 50; i++) {
            p[i] = i;
            r[i] = 0;
        }
    }
    ~DSU() {
        delete[] p;
        delete[] r;
    }
    int find(int x) {
        if (p[x] == x)
            return x;
        return p[x] = find(p[x]);
    }
    bool Unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (r[a] < r[b])
            p[a] = b;
        else
            p[b] = a;
        if (r[a] == r[b])
            r[a]++;
        return true;
    }
};
