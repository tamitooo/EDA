// 14 - D-Query: # de distintos en a[l..r].  Version r: 1 en la ULTIMA aparicion de cada valor en a[1..r].
// Respuesta = # de unos en posiciones >= l en root[r].  (online gratis)
#include <bits/stdc++.h>
using namespace std;
vector<int> Lc, Rc, Cn;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Cn.push_back(Cn[from]); return (int)Lc.size() - 1; }
int upd(int p, int lo, int hi, int pos, int d) {
    int c = newNode(p); Cn[c] += d;
    if (lo == hi) return c;
    int m = (lo + hi) / 2;
    if (pos <= m) { int t = upd(Lc[p], lo, m, pos, d); Lc[c] = t; }
    else { int t = upd(Rc[p], m + 1, hi, pos, d); Rc[c] = t; }
    return c;
}
int cntLess(int u, int lo, int hi, int idx) {          // # unos en posiciones < idx
    if (idx <= lo) return 0;
    if (hi < idx) return Cn[u];
    int m = (lo + hi) / 2;
    return cntLess(Lc[u], lo, m, idx) + cntLess(Rc[u], m + 1, hi, idx);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    Lc.push_back(0); Rc.push_back(0); Cn.push_back(0);
    vector<int> root(n + 1, 0);
    unordered_map<int, int> last;
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        root[i] = upd(root[i - 1], 1, n, i, +1);
        auto it = last.find(a);
        if (it != last.end()) root[i] = upd(root[i], 1, n, it->second, -1);
        last[a] = i;
    }
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << Cn[root[r]] - cntLess(root[r], 1, n, l) << '\n';
    }
}
