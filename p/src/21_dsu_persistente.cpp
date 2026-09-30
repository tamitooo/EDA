// 21 - DSU PERSISTENTE (online): arreglos parent/size persistentes (segment tree persistente), union por tamano, sin compresion.
// Entrada: n Q ; Q ops (version 0 = cada uno solo; la op i crea la version i):
//   1 v a b -> version i = version v + union(a,b)
//   2 v a b -> version i = version v ; imprime 1 si a y b estan conectados en v, 0 si no
// Misma entrada que 22 (que lo resuelve offline con rollback).
#include <bits/stdc++.h>
using namespace std;
vector<int> Lc, Rc, Par, Sz;
int n;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Par.push_back(Par[from]); Sz.push_back(Sz[from]); return (int)Lc.size() - 1; }
int build(int lo, int hi) {
    int c = newNode(0);
    if (lo == hi) { Par[c] = lo; Sz[c] = 1; return c; }
    int m = (lo + hi) / 2;
    int l = build(lo, m); int r = build(m + 1, hi);
    Lc[c] = l; Rc[c] = r;
    return c;
}
int leaf(int u, int x) {
    int lo = 1, hi = n;
    while (lo < hi) { int m = (lo + hi) / 2; if (x <= m) { u = Lc[u]; hi = m; } else { u = Rc[u]; lo = m + 1; } }
    return u;
}
int setv(int p, int lo, int hi, int pos, int par, int sz) {
    int c = newNode(p);
    if (lo == hi) { Par[c] = par; Sz[c] = sz; return c; }
    int m = (lo + hi) / 2;
    if (pos <= m) { int t = setv(Lc[p], lo, m, pos, par, sz); Lc[c] = t; }
    else { int t = setv(Rc[p], m + 1, hi, pos, par, sz); Rc[c] = t; }
    return c;
}
int findRoot(int root, int x) { while (true) { int l = leaf(root, x); if (Par[l] == x) return x; x = Par[l]; } }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int Q; cin >> n >> Q;
    size_t cap = 2 * (size_t)n + (size_t)Q * 2 * 20 + 10;
    Lc.reserve(cap); Rc.reserve(cap); Par.reserve(cap); Sz.reserve(cap);
    Lc.push_back(0); Rc.push_back(0); Par.push_back(0); Sz.push_back(0);
    vector<int> ver(Q + 1, 0);
    ver[0] = build(1, n);
    for (int i = 1; i <= Q; i++) {
        int t, v, a, b; cin >> t >> v >> a >> b;
        int root = ver[v];
        if (t == 1) {
            int ra = findRoot(root, a), rb = findRoot(root, b);
            if (ra != rb) {
                int sa = Sz[leaf(root, ra)], sb = Sz[leaf(root, rb)];
                if (sa < sb) { swap(ra, rb); swap(sa, sb); }       // ra = raiz grande
                root = setv(root, 1, n, rb, ra, sb);
                root = setv(root, 1, n, ra, ra, sa + sb);
            }
            ver[i] = root;
        } else {
            ver[i] = root;
            cout << (findRoot(root, a) == findRoot(root, b) ? 1 : 0) << '\n';
        }
    }
}
