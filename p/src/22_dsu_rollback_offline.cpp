// 22 - Mismo problema que 21 pero OFFLINE: arbol de versiones + DFS + DSU con ROLLBACK (union por tamano, sin compresion).
// Entrada: n Q ; ops "1 v a b" | "2 v a b" (ver 21).  Es la alternativa mas simple cuando NO obligan a ser online.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, Q; cin >> n >> Q;
    vector<int> T(Q + 1), V(Q + 1), A(Q + 1), B(Q + 1), head(Q + 1, -1), nxt(Q + 1, -1), ans(Q + 1, -1);
    for (int i = 1; i <= Q; i++) { cin >> T[i] >> V[i] >> A[i] >> B[i]; nxt[i] = head[V[i]]; head[V[i]] = i; }
    vector<int> par(n + 1), sz(n + 1, 1), hist;
    iota(par.begin(), par.end(), 0);
    auto find = [&](int x) { while (par[x] != x) x = par[x]; return x; };
    struct Fr { int v; bool exit; size_t saved; };
    vector<Fr> st; st.push_back({0, false, 0});
    while (!st.empty()) {
        Fr f = st.back(); st.pop_back();
        if (f.exit) {
            while (hist.size() > f.saved) { int rb = hist.back(); hist.pop_back(); int ra = par[rb]; sz[ra] -= sz[rb]; par[rb] = rb; }
            continue;
        }
        size_t saved = hist.size();
        int v = f.v;
        if (v >= 1) {
            int ra = find(A[v]), rb = find(B[v]);
            if (T[v] == 1) {
                if (ra != rb) { if (sz[ra] < sz[rb]) swap(ra, rb); par[rb] = ra; sz[ra] += sz[rb]; hist.push_back(rb); }
            } else ans[v] = (ra == rb);
        }
        st.push_back({v, true, saved});
        for (int e = head[v]; e != -1; e = nxt[e]) st.push_back({e, false, 0});
    }
    for (int i = 1; i <= Q; i++) if (T[i] == 2) cout << ans[i] << '\n';
}
