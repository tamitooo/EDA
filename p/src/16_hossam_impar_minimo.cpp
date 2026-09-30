// 16 - Hossam and Range Minimum Query (online): menor valor con frecuencia IMPAR en [l,r].
// Segment tree persistente sobre valores comprimidos; cada hoja guarda hash_aleatorio(v) si la paridad es impar, y cada nodo el XOR.
// Comparando root[r] con root[l-1] el hijo izquierdo que difiera contiene el menor valor impar.
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
vector<int> Lc, Rc; vector<ull> Hx;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Hx.push_back(Hx[from]); return (int)Lc.size() - 1; }
int toggle(int p, int lo, int hi, int pos, ull h) {
    int c = newNode(p); Hx[c] ^= h;
    if (lo == hi) return c;
    int m = (lo + hi) / 2;
    if (pos <= m) { int t = toggle(Lc[p], lo, m, pos, h); Lc[c] = t; }
    else { int t = toggle(Rc[p], m + 1, hi, pos, h); Rc[c] = t; }
    return c;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<long long> vals(a.begin() + 1, a.end());
    sort(vals.begin(), vals.end()); vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int M = vals.size();
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<ull> h(M); for (auto& x : h) x = rng();
    Lc.reserve((size_t)n * 20 + 10); Rc.reserve(Lc.capacity()); Hx.reserve(Lc.capacity());
    Lc.push_back(0); Rc.push_back(0); Hx.push_back(0);
    vector<int> root(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int id = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        root[i] = toggle(root[i - 1], 0, M - 1, id, h[id]);
    }
    int q; cin >> q; long long ans = 0;
    while (q--) {
        long long x, y; cin >> x >> y;
        int l = (int)(x ^ ans), r = (int)(y ^ ans);
        int u = root[r], v = root[l - 1];
        if (Hx[u] == Hx[v]) ans = 0;
        else {
            int lo = 0, hi = M - 1;
            while (lo < hi) {
                int m = (lo + hi) / 2;
                if (Hx[Lc[u]] != Hx[Lc[v]]) { u = Lc[u]; v = Lc[v]; hi = m; }
                else { u = Rc[u]; v = Rc[v]; lo = m + 1; }
            }
            ans = vals[lo];
        }
        cout << ans << '\n';
    }
}
