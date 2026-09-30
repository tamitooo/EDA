// 19 - PLANTILLA: suma en rango + update en rango CON VERSIONES (lazy sin propagar = "permanencia de marcas").
// La marca add[] se queda en el nodo (no se empuja a los hijos, asi no se modifican nodos viejos).
// Entrada: n ; a_1..a_n ; Q ; ops.  Version 0 = inicial, op i crea version i.
//   1 v l r x -> version i = version v con a[l..r] += x
//   2 v l r   -> version i = version v ; imprime suma a[l..r] en la version v
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> Lc, Rc; vector<ll> Sm, Ad;
int n;
vector<ll> init;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Sm.push_back(Sm[from]); Ad.push_back(Ad[from]); return (int)Lc.size() - 1; }
int build(int lo, int hi) {
    int c = newNode(0);
    if (lo == hi) { Sm[c] = init[lo]; return c; }
    int m = (lo + hi) / 2;
    int l = build(lo, m); int r = build(m + 1, hi);
    Lc[c] = l; Rc[c] = r; Sm[c] = Sm[l] + Sm[r];
    return c;
}
int add(int p, int lo, int hi, int l, int r, ll x) {
    int c = newNode(p);
    Sm[c] += x * (min(r, hi) - max(l, lo) + 1);
    if (l <= lo && hi <= r) { Ad[c] += x; return c; }
    int m = (lo + hi) / 2;
    if (l <= m) { int t = add(Lc[p], lo, m, l, r, x); Lc[c] = t; }
    if (r > m) { int t = add(Rc[p], m + 1, hi, l, r, x); Rc[c] = t; }
    return c;
}
ll query(int u, int lo, int hi, int l, int r) {
    if (r < lo || hi < l) return 0;
    if (l <= lo && hi <= r) return Sm[u];
    int m = (lo + hi) / 2;
    ll res = Ad[u] * (min(r, hi) - max(l, lo) + 1);        // marcas de este nodo que no bajaron
    return res + query(Lc[u], lo, m, l, r) + query(Rc[u], m + 1, hi, l, r);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n; init.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> init[i];
    int Q; cin >> Q;
    Lc.push_back(0); Rc.push_back(0); Sm.push_back(0); Ad.push_back(0);
    vector<int> ver(Q + 1, 0);
    ver[0] = build(1, n);
    for (int i = 1; i <= Q; i++) {
        int t, v, l, r; cin >> t >> v >> l >> r;
        if (t == 1) { ll x; cin >> x; ver[i] = add(ver[v], 1, n, l, r, x); }
        else { ver[i] = ver[v]; cout << query(ver[v], 1, n, l, r) << '\n'; }
    }
}
