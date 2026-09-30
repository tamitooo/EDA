// 12 - K-Query (offline o no, da igual): # de elementos > k en a[i..j].
// Persistente sobre valores comprimidos, versiones por prefijo.  #(>k) = (j-i+1) - #(<= k).
#include <bits/stdc++.h>
using namespace std;
vector<int> Lc, Rc, Cn;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Cn.push_back(Cn[from]); return (int)Lc.size() - 1; }
int upd(int p, int lo, int hi, int pos) {
    int c = newNode(p); Cn[c]++;
    if (lo == hi) return c;
    int m = (lo + hi) / 2;
    if (pos <= m) { int t = upd(Lc[p], lo, m, pos); Lc[c] = t; }
    else { int t = upd(Rc[p], m + 1, hi, pos); Rc[c] = t; }
    return c;
}
int cntLess(int u, int v, int lo, int hi, int idx) {   // #indices de valor < idx en (u - v)
    if (idx <= lo) return 0;
    if (hi < idx) return Cn[u] - Cn[v];
    int m = (lo + hi) / 2;
    return cntLess(Lc[u], Lc[v], lo, m, idx) + cntLess(Rc[u], Rc[v], m + 1, hi, idx);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> vals(a.begin() + 1, a.end());
    sort(vals.begin(), vals.end()); vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int M = vals.size();
    Lc.push_back(0); Rc.push_back(0); Cn.push_back(0);
    vector<int> root(n + 1, 0);
    for (int i = 1; i <= n; i++) root[i] = upd(root[i - 1], 0, M - 1, lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());
    int q; cin >> q;
    while (q--) {
        int i, j, k; cin >> i >> j >> k;
        int idx = upper_bound(vals.begin(), vals.end(), k) - vals.begin();   // indices >= idx son > k
        cout << (j - i + 1) - cntLess(root[j], root[i - 1], 0, M - 1, idx) << '\n';
    }
}
