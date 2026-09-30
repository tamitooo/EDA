// 01 - Historial de Diccionario: TRIE PERSISTENTE + "volver a la version t" (solo copiar la raiz).
// Entrada: Q, luego Q ops: "1 s" | "2 t" | "3 p".  Nodo 0 = nulo.
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
int countPrefix(int root, const string& p) {
    int cur = root;
    for (char c : p) { cur = T[cur].ch[c - 'a']; if (!cur) return 0; }
    return T[cur].cnt;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int Q; cin >> Q;
    T.reserve(500000 + Q + 10);
    T.push_back(Node{});
    vector<int> ver(Q + 1, 0);
    for (int i = 1; i <= Q; i++) {
        int t; cin >> t;
        if (t == 1) { string s; cin >> s; ver[i] = add(ver[i - 1], s); }
        else if (t == 2) { int x; cin >> x; ver[i] = ver[x]; }
        else { string p; cin >> p; ver[i] = ver[i - 1]; cout << countPrefix(ver[i], p) << '\n'; }
    }
}
