// 08 - Persistent Queue: los elementos empujados forman un ARBOL (cada push es hijo del ultimo de su cola).
// Version = (tail, size).  Frente = ancestro de tail a profundidad depth[tail]-size+1  -> binary lifting (k-esimo ancestro).
#include <bits/stdc++.h>
using namespace std;
const int LOG = 18;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<array<int, LOG>> up(n + 2);
    vector<int> dep(n + 2, 0), val(n + 2, 0), tail(n + 1, 0), sz(n + 1, 0);
    up[0].fill(0);
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        int t, v; cin >> t >> v;
        if (t == 1) {
            int x; cin >> x;
            int u = ++tot; val[u] = x; dep[u] = dep[tail[v]] + 1;
            up[u][0] = tail[v];
            for (int j = 1; j < LOG; j++) up[u][j] = up[up[u][j - 1]][j - 1];
            tail[i] = u; sz[i] = sz[v] + 1;
        } else {
            int u = tail[v], diff = sz[v] - 1;      // subir sz-1 niveles hasta el frente
            for (int j = 0; j < LOG; j++) if (diff >> j & 1) u = up[u][j];
            cout << val[u] << '\n';
            tail[i] = tail[v]; sz[i] = sz[v] - 1;
        }
    }
}
