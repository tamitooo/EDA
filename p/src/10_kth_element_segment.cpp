// 10 - K-th Element on a Segment: segment tree persistente sobre valores comprimidos, versiones por prefijo.
// k-esimo en [i,j] = descenso simultaneo en root[j] y root[i-1].  Entrada generada con LCG (ver enunciado).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
int kth(int u, int v, int lo, int hi, int k) {   // u = root[j], v = root[i-1]
    while (lo < hi) {
        int m = (lo + hi) / 2, s = Cn[Lc[u]] - Cn[Lc[v]];
        if (k <= s) { u = Lc[u]; v = Lc[v]; hi = m; }
        else { k -= s; u = Rc[u]; v = Rc[v]; lo = m + 1; }
    }
    return lo;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const ll MOD = 1000000000;
    int N; ll a1, l, m; cin >> N >> a1 >> l >> m;
    vector<ll> a(N + 1); a[1] = a1;
    for (int i = 2; i <= N; i++) a[i] = (a[i - 1] * l + m) % MOD;
    vector<ll> vals(a.begin() + 1, a.end());
    sort(vals.begin(), vals.end()); vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int M = vals.size();
    Lc.reserve((size_t)N * 21 + 10); Rc.reserve(Lc.capacity()); Cn.reserve(Lc.capacity());
    Lc.push_back(0); Rc.push_back(0); Cn.push_back(0);
    vector<int> root(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        int id = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        root[i] = upd(root[i - 1], 0, M - 1, id);
    }
    int B; cin >> B; ll total = 0;
    while (B--) {
        ll G, x1, lx, mx, y1, ly, my, k1, lk, mk;
        cin >> G >> x1 >> lx >> mx >> y1 >> ly >> my >> k1 >> lk >> mk;
        ll x = x1, y = y1, k = k1;
        for (ll g = 1; g <= G; g++) {
            if (g > 1) { x = ((x - 1) * lx + mx) % N + 1; y = ((y - 1) * ly + my) % N + 1; }
            ll i = min(x, y), j = max(x, y);
            if (g > 1) k = ((k - 1) * lk + mk) % (j - i + 1) + 1;
            total += vals[kth(root[j], root[i - 1], 0, M - 1, (int)k)];
        }
    }
    cout << total << '\n';
}
