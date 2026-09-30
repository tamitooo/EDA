// 03 - k-esimo menor de (a_i xor x), i en [l,r].  Trie persistente por prefijos del arreglo.
// Idea: al hacer xor con x, el hijo "preferido" es el de bit igual al de x (da bit 0 en el resultado).
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
int kthXor(int hi, int lo, int x, int k) {
    int res = 0;
    for (int b = B - 1; b >= 0; b--) {
        int c = (x >> b) & 1;                       // da bit 0 en el resultado
        int s = cnt[ch[hi][c]] - cnt[ch[lo][c]];
        if (k <= s) { hi = ch[hi][c]; lo = ch[lo][c]; }
        else { k -= s; res |= 1 << b; hi = ch[hi][c ^ 1]; lo = ch[lo][c ^ 1]; }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> root(n + 1, 0);
    for (int i = 1; i <= n; i++) { int a; cin >> a; root[i] = ins(root[i - 1], a); }
    int q; cin >> q;
    while (q--) {
        int l, r, x, k; cin >> l >> r >> x >> k;
        cout << kthXor(root[r], root[l - 1], x, k) << '\n';
    }
}
