// 11 - Rollback (online): minimo r tal que [l,r] tiene >= k valores distintos.
// Versiones de DERECHA a IZQUIERDA: version l marca con 1 la PRIMERA aparicion de cada valor en a[l..n].
// Entonces el r buscado = posicion del k-esimo "1" en la version l.   (Misma idea se usa en 15 y 14.)
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
int kth(int u, int lo, int hi, int k) {
    while (lo < hi) {
        int m = (lo + hi) / 2;
        if (Cn[Lc[u]] >= k) { u = Lc[u]; hi = m; } else { k -= Cn[Lc[u]]; u = Rc[u]; lo = m + 1; }
    }
    return lo;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> a(n + 2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    Lc.reserve((size_t)n * 40 + 10); Rc.reserve(Lc.capacity()); Cn.reserve(Lc.capacity());
    Lc.push_back(0); Rc.push_back(0); Cn.push_back(0);
    vector<int> root(n + 2, 0), nextPos(m + 1, 0);       // nextPos[v] = proxima aparicion de v a la derecha
    for (int l = n; l >= 1; l--) {
        root[l] = upd(root[l + 1], 1, n, l, +1);
        if (nextPos[a[l]]) root[l] = upd(root[l], 1, n, nextPos[a[l]], -1);
        nextPos[a[l]] = l;
    }
    int q; cin >> q; long long p = 0;
    while (q--) {
        long long x, y; cin >> x >> y;
        int l = (int)((x + p) % n) + 1, k = (int)((y + p) % m) + 1;
        int ans = (Cn[root[l]] < k) ? 0 : kth(root[l], 1, n, k);
        cout << ans << '\n'; p = ans;
    }
}
