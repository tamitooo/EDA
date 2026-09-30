// 15 - Till I Collapse: para cada k=1..n, min # de segmentos con <= k colores distintos.
// Para cada k se hace el salto goloso: desde l, el segmento termina antes del (k+1)-esimo "primer aparicion" en la version l.
// Total de saltos ~ n ln n, cada uno O(log n).   (misma estructura que 11)
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
    int n; cin >> n;
    vector<int> a(n + 2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    Lc.reserve((size_t)n * 40 + 10); Rc.reserve(Lc.capacity()); Cn.reserve(Lc.capacity());
    Lc.push_back(0); Rc.push_back(0); Cn.push_back(0);
    vector<int> root(n + 2, 0), nextPos(n + 1, 0);
    for (int l = n; l >= 1; l--) {
        root[l] = upd(root[l + 1], 1, n, l, +1);
        if (nextPos[a[l]]) root[l] = upd(root[l], 1, n, nextPos[a[l]], -1);
        nextPos[a[l]] = l;
    }
    for (int k = 1; k <= n; k++) {
        int pos = 1, parts = 0;
        while (pos <= n) {
            parts++;
            if (Cn[root[pos]] <= k) break;           // todo el resto cabe
            pos = kth(root[pos], 1, n, k + 1);       // el siguiente segmento empieza en el (k+1)-esimo distinto
        }
        cout << parts << " \n"[k == n];
    }
}
