// 18 - PLANTILLA: arreglo con versiones, asignacion puntual y suma en rango (segment tree persistente).
// Entrada: n ; a_1..a_n ; Q ; Q ops.  Version 0 = arreglo inicial, la op i crea la version i.
//   1 v i x   -> version i = version v con a[i] = x
//   2 v l r   -> version i = version v ; imprime suma a[l..r] en la version v
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> Lc, Rc; vector<ll> Sm;
int n;
vector<ll> init;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Sm.push_back(Sm[from]); return (int)Lc.size() - 1; }
int build(int lo, int hi) {
    int c = newNode(0);
    if (lo == hi) { Sm[c] = init[lo]; return c; }
    int m = (lo + hi) / 2;
    int l = build(lo, m); int r = build(m + 1, hi);
    Lc[c] = l; Rc[c] = r; Sm[c] = Sm[l] + Sm[r];
    return c;
}
int setv(int p, int lo, int hi, int pos, ll v) {
    int c = newNode(p);
    if (lo == hi) { Sm[c] = v; return c; }
    int m = (lo + hi) / 2;
    if (pos <= m) { int t = setv(Lc[p], lo, m, pos, v); Lc[c] = t; }
    else { int t = setv(Rc[p], m + 1, hi, pos, v); Rc[c] = t; }
    Sm[c] = Sm[Lc[c]] + Sm[Rc[c]];
    return c;
}
ll query(int u, int lo, int hi, int l, int r) {
    if (r < lo || hi < l) return 0;
    if (l <= lo && hi <= r) return Sm[u];
    int m = (lo + hi) / 2;
    return query(Lc[u], lo, m, l, r) + query(Rc[u], m + 1, hi, l, r);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n; init.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> init[i];
    int Q; cin >> Q;
    Lc.push_back(0); Rc.push_back(0); Sm.push_back(0);
    vector<int> ver(Q + 1, 0);
    ver[0] = build(1, n);
    for (int i = 1; i <= Q; i++) {
        int t, v; cin >> t >> v;
        if (t == 1) { int p; ll x; cin >> p >> x; ver[i] = setv(ver[v], 1, n, p, x); }
        else { int l, r; cin >> l >> r; ver[i] = ver[v]; cout << query(ver[v], 1, n, l, r) << '\n'; }
    }
}
