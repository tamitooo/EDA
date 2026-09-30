// 17 - Llave Xor (del editorial del simulacro): max(x xor a_i) con i en [l,r].  Varios casos de prueba.
// Entrada: t ; por caso: n q ; a_1..a_n ; q lineas "x l r".   Trie persistente por prefijos.
#include <bits/stdc++.h>
using namespace std;
const int B = 30, N = 200000, MAXN = N * (B + 1) + 5;
static int ch[MAXN][2], cnt[MAXN];
int tot;
int ins(int prev, int x) {
    int root = ++tot, cur = root;
    for (int b = B - 1; b >= 0; b--) {
        ch[cur][0] = ch[prev][0]; ch[cur][1] = ch[prev][1]; cnt[cur] = cnt[prev] + 1;
        int c = (x >> b) & 1, nx = ++tot;
        ch[cur][c] = nx; prev = ch[prev][c]; cur = nx;
    }
    ch[cur][0] = ch[cur][1] = 0; cnt[cur] = cnt[prev] + 1;
    return root;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q; tot = 0;
        vector<int> root(n + 1, 0);
        for (int i = 1; i <= n; i++) { int a; cin >> a; root[i] = ins(root[i - 1], a); }
        while (q--) {
            int x, l, r; cin >> x >> l >> r;
            int hi = root[r], lo = root[l - 1], res = 0;
            for (int b = B - 1; b >= 0; b--) {
                int d = ((x >> b) & 1) ^ 1;
                if (cnt[ch[hi][d]] - cnt[ch[lo][d]] > 0) { res |= 1 << b; hi = ch[hi][d]; lo = ch[lo][d]; }
                else { hi = ch[hi][d ^ 1]; lo = ch[lo][d ^ 1]; }
            }
            cout << res << '\n';
        }
    }
}
