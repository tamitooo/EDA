// DSU persistente (online) y DSU con rollback (offline, para DFS sobre arbol de versiones).
//   PDSU(n): version 0 = todos separados.  unite(v,a,b) -> nueva version ; same(v,a,b).  O(log^2 n)
//   RDSU(n): unite(a,b) (true si unio), same(a,b), snapshot() / rollback(snap).  O(log n)
#include <bits/stdc++.h>
using namespace std;
struct PDSU {
    int n; vector<int> L, R, P, Z; vector<int> ver0;
    PDSU(int n, size_t reserve = 0) : n(n) { L.reserve(reserve + 2 * n + 2); R = L; P = L; Z = L; nn(0); root0 = build(1, n); }
    int root0;
    int nn(int f) {
        if (L.empty()) { L.push_back(0); R.push_back(0); P.push_back(0); Z.push_back(0); return 0; }
        L.push_back(L[f]); R.push_back(R[f]); P.push_back(P[f]); Z.push_back(Z[f]); return (int)L.size() - 1;
    }
    int build(int lo, int hi) {
        int c = nn(0);
        if (lo == hi) { P[c] = lo; Z[c] = 1; return c; }
        int m = (lo + hi) / 2, x = build(lo, m), y = build(m + 1, hi);
        L[c] = x; R[c] = y; return c;
    }
    int leaf(int u, int x) { int lo = 1, hi = n; while (lo < hi) { int m = (lo + hi) / 2; if (x <= m) { u = L[u]; hi = m; } else { u = R[u]; lo = m + 1; } } return u; }
    int setv(int p, int lo, int hi, int pos, int par, int sz) {
        int c = nn(p);
        if (lo == hi) { P[c] = par; Z[c] = sz; return c; }
        int m = (lo + hi) / 2;
        if (pos <= m) { int t = setv(L[p], lo, m, pos, par, sz); L[c] = t; } else { int t = setv(R[p], m + 1, hi, pos, par, sz); R[c] = t; }
        return c;
    }
    int find(int v, int x) { while (true) { int l = leaf(v, x); if (P[l] == x) return x; x = P[l]; } }
    // las versiones son RAICES de segment tree: la version inicial es init()
    int init() { return root0; }
    int unite(int v, int a, int b) {
        int ra = find(v, a), rb = find(v, b);
        if (ra == rb) return v;
        int sa = Z[leaf(v, ra)], sb = Z[leaf(v, rb)];
        if (sa < sb) { swap(ra, rb); swap(sa, sb); }
        v = setv(v, 1, n, rb, ra, sb);
        return setv(v, 1, n, ra, ra, sa + sb);
    }
    bool same(int v, int a, int b) { return find(v, a) == find(v, b); }
};
struct RDSU {
    vector<int> p, sz, hist;
    RDSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while (p[x] != x) x = p[x]; return x; }
    bool same(int a, int b) { return find(a) == find(b); }
    bool unite(int a, int b) {
        a = find(a); b = find(b); if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b]; hist.push_back(b); return true;
    }
    size_t snapshot() { return hist.size(); }
    void rollback(size_t snap) { while (hist.size() > snap) { int b = hist.back(); hist.pop_back(); int a = p[b]; sz[a] -= sz[b]; p[b] = b; } }
};
#ifdef DEMO
int main() {
    PDSU d(5); int v0 = d.init(), v1 = d.unite(v0, 1, 2), v2 = d.unite(v1, 2, 3), v3 = d.unite(v0, 4, 5);
    assert(d.same(v2, 1, 3) && !d.same(v1, 1, 3) && !d.same(v3, 1, 2) && d.same(v3, 4, 5));
    RDSU r(5); auto s = r.snapshot(); r.unite(1, 2); r.unite(2, 3); assert(r.same(1, 3)); r.rollback(s); assert(!r.same(1, 2));
    puts("DSU ok");
}
#endif
