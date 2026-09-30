// 05 - Prefijos en rango: cuantas s_l..s_r empiezan con p.  Trie persistente por indice de palabra.
// Respuesta = cnt en root[r] - cnt en root[l-1] siguiendo el mismo camino p.
#include <bits/stdc++.h>
using namespace std;
struct Node { int ch[26]; int cnt; };
vector<Node> T;
int copyNode(int from) { Node nd = T[from]; T.push_back(nd); return (int)T.size() - 1; }
int add(int prevRoot, const string& s) {
    int root = copyNode(prevRoot); T[root].cnt++;
    int cur = root;
    for (char c : s) {
        int k = c - 'a';
        int nx = copyNode(T[cur].ch[k]); T[nx].cnt++;
        T[cur].ch[k] = nx; cur = nx;
    }
    return root;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    T.reserve(500000 + n + 10);
    T.push_back(Node{});
    vector<int> root(n + 1, 0);
    for (int i = 1; i <= n; i++) { string s; cin >> s; root[i] = add(root[i - 1], s); }
    while (q--) {
        int l, r; string p; cin >> l >> r >> p;
        int a = root[r], b = root[l - 1];
        for (char c : p) { a = T[a].ch[c - 'a']; b = T[b].ch[c - 'a']; if (!a) break; }
        cout << T[a].cnt - T[b].cnt << '\n';
    }
}
