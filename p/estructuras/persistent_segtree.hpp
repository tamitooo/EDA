// PST: segment tree persistente (suma/conteo).  Rango [lo,hi] cualquiera (nodos dinamicos: sirve para [0,1e9] sin comprimir).
// Version = int (raiz). Raiz 0 = version vacia (todo 0).  Un update crea O(log) nodos.
//   add(root,pos,d)        -> nueva raiz con a[pos] += d          (conteos: d=+1 / -1)
//   range(ru,rv,l,r)       -> suma en [l,r] de (version ru) - (version rv)   [rv=0 por defecto]
//   kth(ru,rv,k)           -> k-esimo menor (S = conteos >=0) de (ru - rv)
//   cntLess(ru,rv,idx)     -> suma de posiciones < idx
// Uso tipico: versiones por prefijo root[i]=add(root[i-1],pos(a_i),1)  ->  rango [l,r] = (root[r], root[l-1]).
#include <bits/stdc++.h>
using namespace std;
struct PST {
    typedef long long ll;
    vector<int> L, R; vector<ll> S; int lo, hi;
    PST(int lo, int hi, size_t reserve = 0) : lo(lo), hi(hi) {
        L.reserve(reserve + 1); R.reserve(reserve + 1); S.reserve(reserve + 1);
        L.push_back(0); R.push_back(0); S.push_back(0);
    }
    int nn(int f) { L.push_back(L[f]); R.push_back(R[f]); S.push_back(S[f]); return (int)L.size() - 1; }
    int add(int p, int pos, ll d) { return add(p, lo, hi, pos, d); }
    int add(int p, int l, int r, int pos, ll d) {
        int c = nn(p); S[c] += d;
        if (l == r) return c;
        int m = l + (r - l) / 2;
        if (pos <= m) { int t = add(L[p], l, m, pos, d); L[c] = t; }
        else { int t = add(R[p], m + 1, r, pos, d); R[c] = t; }
        return c;
    }
    ll range(int u, int v, int ql, int qr) { return range(u, v, lo, hi, ql, qr); }
    ll range(int u, int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return S[u] - S[v];
        int m = l + (r - l) / 2;
        return range(L[u], L[v], l, m, ql, qr) + range(R[u], R[v], m + 1, r, ql, qr);
    }
    ll cntLess(int u, int v, int idx) { return idx <= lo ? 0 : range(u, v, lo, min(idx - 1, hi)); }
    int kth(int u, int v, ll k) {
        int l = lo, r = hi;
        while (l < r) {
            int m = l + (r - l) / 2; ll s = S[L[u]] - S[L[v]];
            if (k <= s) { u = L[u]; v = L[v]; r = m; } else { k -= s; u = R[u]; v = R[v]; l = m + 1; }
        }
        return l;
    }
    int kth(int u, ll k) { return kth(u, 0, k); }
};
#ifdef DEMO
int main() {
    PST t(0, 1000000000);
    vector<int> root(1, 0);
    for (int x : {5, 3, 8, 3}) root.push_back(t.add(root.back(), x, 1));
    assert(t.kth(root[4], 2) == 3);                  // {5,3,8,3} -> 2do menor = 3
    assert(t.range(root[4], root[1], 0, 4) == 2);    // a[2..4] = {3,8,3}: valores <=4 -> 2
    assert(t.cntLess(root[4], root[0], 6) == 3);
    puts("PST ok");
}
#endif
