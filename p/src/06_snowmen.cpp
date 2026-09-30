// 06 - Snowmen: PILA PERSISTENTE (lista enlazada inmutable).  Version = puntero al nodo tope.
// push: nodo nuevo cuyo padre es el tope de la version t.  pop: version = padre del tope.  sum[nodo] = masa total.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> par(n + 2, 0), ver(n + 1, 0);
    vector<long long> sum(n + 2, 0);
    int tot = 0; long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int t, m; cin >> t >> m;
        if (m > 0) { ++tot; par[tot] = ver[t]; sum[tot] = sum[ver[t]] + m; ver[i] = tot; }
        else ver[i] = par[ver[t]];
        ans += sum[ver[i]];
    }
    cout << ans << '\n';
}
