// PSTL: segment tree persistente con update en rango (+x) y suma en rango, SIN propagar (permanencia de marcas).
//   build(a,n)              -> raiz de la version inicial (a indexado 1..n)
//   add(root,l,r,x)         -> nueva raiz con a[l..r] += x
//   sum(root,l,r)           -> suma de a[l..r] en esa version
// Raiz 0 = todo ceros.  Para version inicial vacia: PSTL t(1,n); raiz 0.
#include <bits/stdc++.h>
using namespace std;
struct PSTL {
    typedef long long ll;
    vector<int> L, R; vector<ll> S, A; int lo, hi;
    PSTL(int lo, int hi, size_t reserve = 0) : lo(lo), hi(hi) {
        L.reserve(reserve + 1); R.reserve(reserve + 1); S.reserve(reserve + 1); A.reserve(reserve + 1);
        L.push_back(0); R.push_back(0); S.push_back(0); A.push_back(0);
    }
    int nn(int f) { L.push_back(L[f]); R.push_back(R[f]); S.push_back(S[f]); A.push_back(A[f]); return (int)L.size() - 1; }
    int build(const vector<ll>& a) { return build(lo, hi, a); }
    int build(int l, int r, const vector<ll>& a) {
        int c = nn(0);
        if (l == r) { S[c] = a[l]; return c; }
        int m = (l + r) / 2, x = build(l, m, a), y = build(m + 1, r, a);
        L[c] = x; R[c] = y; S[c] = S[x] + S[y];
        return c;
    }
    int add(int p, int ql, int qr, ll x) { return add(p, lo, hi, ql, qr, x); }
    int add(int p, int l, int r, int ql, int qr, ll x) {
        int c = nn(p);
        S[c] += x * (min(qr, r) - max(ql, l) + 1);
        if (ql <= l && r <= qr) { A[c] += x; return c; }
        int m = (l + r) / 2;
        if (ql <= m) { int t = add(L[p], l, m, ql, qr, x); L[c] = t; }
        if (qr > m) { int t = add(R[p], m + 1, r, ql, qr, x); R[c] = t; }
        return c;
    }
    ll sum(int u, int ql, int qr) { return sum(u, lo, hi, ql, qr); }
    ll sum(int u, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return S[u];
        int m = (l + r) / 2;
        return A[u] * (min(qr, r) - max(ql, l) + 1) + sum(L[u], l, m, ql, qr) + sum(R[u], m + 1, r, ql, qr);
    }
};
#ifdef DEMO
int main() {
    PSTL t(1, 5);
    int v0 = t.build({0, 1, 2, 3, 4, 5});
    int v1 = t.add(v0, 2, 4, 10);
    assert(t.sum(v0, 1, 5) == 15 && t.sum(v1, 1, 5) == 45 && t.sum(v1, 3, 3) == 13);
    puts("PSTL ok");
}
#endif
