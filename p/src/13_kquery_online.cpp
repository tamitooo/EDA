// 13 - K-Query Online: igual que 12 pero i=a^last, j=b^last, k=c^last.  Se recorta a [1,n]; si queda vacio -> 0.
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
int cntLess(int u, int v, int lo, int hi, int idx) {
    if (idx <= lo) return 0;
    if (hi < idx) return Cn[u] - Cn[v];
    int m = (lo + hi) / 2;
    return cntLess(Lc[u], Lc[v], lo, m, idx) + cntLess(Rc[u], Rc[v], m + 1, hi, idx);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<ll> vals(a.begin() + 1, a.end());
    sort(vals.begin(), vals.end()); vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int M = vals.size();
    Lc.push_back(0); Rc.push_back(0); Cn.push_back(0);
    vector<int> root(n + 1, 0);
    for (int i = 1; i <= n; i++) root[i] = upd(root[i - 1], 0, M - 1, lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());
    int q; cin >> q; ll last = 0;
    while (q--) {
        ll x, y, z; cin >> x >> y >> z;
        ll i = x ^ last, j = y ^ last, k = z ^ last;
        i = max(i, 1LL); j = min(j, (ll)n);
        ll ans = 0;
        if (i <= j) {
            int idx = upper_bound(vals.begin(), vals.end(), k) - vals.begin();
            ans = (j - i + 1) - cntLess(root[j], root[i - 1], 0, M - 1, idx);
        }
        cout << ans << '\n'; last = ans;
    }
}
