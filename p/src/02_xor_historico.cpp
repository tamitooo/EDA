// 02 - Xor historico: max(a_c xor x) en el camino u -> ancestro w.
// TRIE PERSISTENTE SOBRE ARBOL: root[u] = root[padre[u]] + a[u].  Camino = root[u] "menos" root[padre[w]].
#include <bits/stdc++.h>
using namespace std;
const int B = 30, N = 200000, MAXN = N * (B + 1) + 5;
static int ch[MAXN][2], cnt[MAXN];
int tot = 0;
int ins(int prev, int x) {
    int root = ++tot, cur = root;
    for (int b = B - 1; b >= 0; b--) {
        ch[cur][0] = ch[prev][0]; ch[cur][1] = ch[prev][1]; cnt[cur] = cnt[prev] + 1;
        int c = (x >> b) & 1, nx = ++tot;
        ch[cur][c] = nx; prev = ch[prev][c]; cur = nx;
    }
    cnt[cur] = cnt[prev] + 1;
    return root;
}
int maxXor(int hi, int lo, int x) {
    int res = 0;
    for (int b = B - 1; b >= 0; b--) {
        int d = ((x >> b) & 1) ^ 1;
        if (cnt[ch[hi][d]] - cnt[ch[lo][d]] > 0) { res |= 1 << b; hi = ch[hi][d]; lo = ch[lo][d]; }
        else { hi = ch[hi][d ^ 1]; lo = ch[lo][d ^ 1]; }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> p(n + 1), a(n + 1), root(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> p[i] >> a[i]; root[i] = ins(root[p[i]], a[i]); }
    int q; cin >> q;
    while (q--) {
        int u, w, x; cin >> u >> w >> x;
        cout << maxXor(root[u], root[p[w]], x) << '\n';
    }
}
