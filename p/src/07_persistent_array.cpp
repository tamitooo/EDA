// 07 - Persistent Array: SEGMENT TREE PERSISTENTE con actualizacion puntual.
// create i j x: nueva revision desde i con a[j]=x.  get i j.  Revision inicial = 1.
#include <bits/stdc++.h>
using namespace std;
vector<int> Lc, Rc, Val;
int n;
vector<int> init;
int build(int lo, int hi) {
    Lc.push_back(0); Rc.push_back(0); Val.push_back(0);
    int c = (int)Lc.size() - 1;
    if (lo == hi) { Val[c] = init[lo]; return c; }
    int m = (lo + hi) / 2;
    int l = build(lo, m); int r = build(m + 1, hi);
    Lc[c] = l; Rc[c] = r;
    return c;
}
int upd(int p, int lo, int hi, int pos, int v) {
    Lc.push_back(Lc[p]); Rc.push_back(Rc[p]); Val.push_back(Val[p]);
    int c = (int)Lc.size() - 1;
    if (lo == hi) { Val[c] = v; return c; }
    int m = (lo + hi) / 2;
    if (pos <= m) { int t = upd(Lc[p], lo, m, pos, v); Lc[c] = t; }
    else { int t = upd(Rc[p], m + 1, hi, pos, v); Rc[c] = t; }
    return c;
}
int get(int u, int pos) {
    int lo = 1, hi = n;
    while (lo < hi) { int m = (lo + hi) / 2; if (pos <= m) { u = Lc[u]; hi = m; } else { u = Rc[u]; lo = m + 1; } }
    return Val[u];
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n; init.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> init[i];
    vector<int> roots(1, 0);          // roots[0] sin uso -> la revision 1 es roots[1]
    roots.push_back(build(1, n));
    int m; cin >> m;
    while (m--) {
        string op; cin >> op;
        if (op == "create") { int i, j, x; cin >> i >> j >> x; roots.push_back(upd(roots[i], 1, n, j, x)); }
        else { int i, j; cin >> i >> j; cout << get(roots[i], j) << '\n'; }
    }
}
