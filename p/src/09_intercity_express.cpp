// 09 - Intercity Express (online).  Asiento c libre en [a,b)  <=>  nxt_c(a) >= b,
// con nxt_c(a) = inicio del primer ticket del asiento c cuyo fin > a  (INF si no hay).
// Version k = despues de procesar los k tickets de menor fin; para consulta a: k = #tickets con fin <= a.
// Segment tree persistente (max) sobre asientos; buscar el asiento MAS A LA IZQUIERDA con valor >= b.
#include <bits/stdc++.h>
using namespace std;
const int INF = 2000000000;
vector<int> Lc, Rc, Mx;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Mx.push_back(Mx[from]); return (int)Lc.size() - 1; }
int build(int lo, int hi, const vector<int>& val) {
    int c = newNode(0);
    if (lo == hi) { Mx[c] = val[lo]; return c; }
    int m = (lo + hi) / 2;
    int l = build(lo, m, val); int r = build(m + 1, hi, val);
    Lc[c] = l; Rc[c] = r; Mx[c] = max(Mx[l], Mx[r]);
    return c;
}
int upd(int p, int lo, int hi, int pos, int v) {
    int c = newNode(p);
    if (lo == hi) { Mx[c] = v; return c; }
    int m = (lo + hi) / 2;
    if (pos <= m) { int t = upd(Lc[p], lo, m, pos, v); Lc[c] = t; }
    else { int t = upd(Rc[p], m + 1, hi, pos, v); Rc[c] = t; }
    Mx[c] = max(Mx[Lc[c]], Mx[Rc[c]]);
    return c;
}
int firstGE(int u, int lo, int hi, int b) {
    while (lo < hi) {
        int m = (lo + hi) / 2;
        if (Mx[Lc[u]] >= b) { u = Lc[u]; hi = m; } else { u = Rc[u]; lo = m + 1; }
    }
    return lo;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, s, m; cin >> n >> s >> m;
    vector<int> C(m), A(m), Bv(m);
    vector<vector<int>> seat(s + 1);
    for (int i = 0; i < m; i++) { cin >> C[i] >> A[i] >> Bv[i]; seat[C[i]].push_back(i); }
    vector<int> val(s + 1, INF), nx(m, INF);
    for (int c = 1; c <= s; c++) {
        sort(seat[c].begin(), seat[c].end(), [&](int x, int y) { return A[x] < A[y]; });
        if (!seat[c].empty()) val[c] = A[seat[c][0]];
        for (size_t j = 0; j < seat[c].size(); j++) nx[seat[c][j]] = (j + 1 < seat[c].size()) ? A[seat[c][j + 1]] : INF;
    }
    vector<int> ord(m); iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) { return Bv[x] < Bv[y]; });
    Lc.reserve(2 * s + (size_t)m * 18 + 10); Rc.reserve(Lc.capacity()); Mx.reserve(Lc.capacity());
    Lc.push_back(0); Rc.push_back(0); Mx.push_back(0);
    vector<int> roots(m + 1), ends(m);
    roots[0] = build(1, s, val);
    for (int k = 0; k < m; k++) { roots[k + 1] = upd(roots[k], 1, s, C[ord[k]], nx[ord[k]]); ends[k] = Bv[ord[k]]; }
    int q; cin >> q; long long p = 0;
    while (q--) {
        long long x, y; cin >> x >> y;
        long long a = x + p, b = y + p;
        int k = upper_bound(ends.begin(), ends.end(), a) - ends.begin();
        int r = roots[k], ans = 0;
        if (Mx[r] >= b) ans = firstGE(r, 1, s, (int)b);
        cout << ans << '\n'; p = ans;
    }
}
