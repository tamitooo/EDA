// 04 - Multiconjunto con versiones: SEGMENT TREE PERSISTENTE DINAMICO sobre [0, 1e9] + k-esimo.
// Sin comprimir coordenadas: cada update crea ~31 nodos.  Nodo 0 = nulo.
#include <bits/stdc++.h>
using namespace std;
const int MAXV = 1000000000;
vector<int> Lc, Rc, Cn;
int newNode(int from) { Lc.push_back(Lc[from]); Rc.push_back(Rc[from]); Cn.push_back(Cn[from]); return (int)Lc.size() - 1; }
int upd(int p, int lo, int hi, int x, int d) {
    int c = newNode(p); Cn[c] += d;
    if (lo == hi) return c;
    int m = lo + (hi - lo) / 2;
    if (x <= m) { int t = upd(Lc[p], lo, m, x, d); Lc[c] = t; }
    else { int t = upd(Rc[p], m + 1, hi, x, d); Rc[c] = t; }
    return c;
}
int kth(int u, int k) {
    int lo = 0, hi = MAXV;
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (Cn[Lc[u]] >= k) { u = Lc[u]; hi = m; }
        else { k -= Cn[Lc[u]]; u = Rc[u]; lo = m + 1; }
    }
    return lo;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int Q; cin >> Q;
    Lc.reserve(Q * 32 + 5); Rc.reserve(Q * 32 + 5); Cn.reserve(Q * 32 + 5);
    Lc.push_back(0); Rc.push_back(0); Cn.push_back(0);
    vector<int> ver(Q + 1, 0);
    for (int i = 1; i <= Q; i++) {
        int t, v, y; cin >> t >> v >> y;
        if (t == 1) ver[i] = upd(ver[v], 0, MAXV, y, +1);
        else if (t == 2) ver[i] = upd(ver[v], 0, MAXV, y, -1);
        else { ver[i] = ver[v]; cout << kth(ver[v], y) << '\n'; }
    }
}
