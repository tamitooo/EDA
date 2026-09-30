// 20 - MEX en rango (clasico): mex(a[l..r]).  Version r: last[v] = ultima posicion de v en a[1..r] (0 si no esta).
// segment tree persistente sobre VALORES [0,n] guardando el minimo de last.  mex = menor v con last[v] < l.
// Entrada: n ; a_1..a_n ; q ; q lineas "l r".
#include <bits/stdc++.h>
using namespace std;
vector<int> Lc, Rc, Mn;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Mn.push_back(Mn[from]); return (int)Lc.size() - 1; }
int setv(int p, int lo, int hi, int pos, int v) {
    int c = newNode(p);
    if (lo == hi) { Mn[c] = v; return c; }
    int m = (lo + hi) / 2;
    if (pos <= m) { int t = setv(Lc[p], lo, m, pos, v); Lc[c] = t; }
    else { int t = setv(Rc[p], m + 1, hi, pos, v); Rc[c] = t; }
    Mn[c] = min(Mn[Lc[c]], Mn[Rc[c]]);
    return c;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    Lc.push_back(0); Rc.push_back(0); Mn.push_back(0);      // nodo nulo: todo last = 0
    vector<int> root(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long a; cin >> a;
        root[i] = (a <= n) ? setv(root[i - 1], 0, n, (int)a, i) : root[i - 1];
    }
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        int u = root[r], lo = 0, hi = n;
        while (lo < hi) {
            int m = (lo + hi) / 2;
            if (Mn[Lc[u]] < l) { u = Lc[u]; hi = m; } else { u = Rc[u]; lo = m + 1; }
        }
        cout << lo << '\n';
    }
}
