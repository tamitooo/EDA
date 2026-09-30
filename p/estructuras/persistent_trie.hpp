// Tries persistentes.  Nodo 0 = nulo.  cnt[nodo] = # de valores/palabras que pasan por el nodo.
// Rango de versiones: usar (root[r], root[l-1]).  Arbol: (root[u], root[padre[w]]).
//   BinTrie (enteros de B bits):  insert, maxXor(ru,rv,x), kthXor(ru,rv,x,k), countXorLess? (ver kthXor)
//   StrTrie (a-z):                add, countPrefix(ru,rv,p)
#include <bits/stdc++.h>
using namespace std;
struct BinTrie {
    int B; vector<array<int, 2>> ch; vector<int> cnt;
    BinTrie(int B = 30, size_t reserve = 0) : B(B) { ch.reserve(reserve + 1); cnt.reserve(reserve + 1); ch.push_back({0, 0}); cnt.push_back(0); }
    int insert(int prev, int x) {
        int root = (int)ch.size(), cur = root;
        ch.push_back(ch[prev]); cnt.push_back(cnt[prev] + 1);
        for (int b = B - 1; b >= 0; b--) {
            int c = (x >> b) & 1, pn = ch[prev][c];
            int nx = (int)ch.size(); ch.push_back(ch[pn]); cnt.push_back(cnt[pn] + 1);
            ch[cur][c] = nx; prev = pn; cur = nx;
        }
        return root;
    }
    int maxXor(int u, int v, int x) {           // max (a xor x) entre valores de (u - v); supone que no es vacio
        int res = 0;
        for (int b = B - 1; b >= 0; b--) {
            int d = ((x >> b) & 1) ^ 1;
            if (cnt[ch[u][d]] - cnt[ch[v][d]] > 0) { res |= 1 << b; u = ch[u][d]; v = ch[v][d]; }
            else { u = ch[u][d ^ 1]; v = ch[v][d ^ 1]; }
        }
        return res;
    }
    int kthXor(int u, int v, int x, int k) {    // k-esimo menor de (a xor x), con repeticiones
        int res = 0;
        for (int b = B - 1; b >= 0; b--) {
            int c = (x >> b) & 1, s = cnt[ch[u][c]] - cnt[ch[v][c]];
            if (k <= s) { u = ch[u][c]; v = ch[v][c]; }
            else { k -= s; res |= 1 << b; u = ch[u][c ^ 1]; v = ch[v][c ^ 1]; }
        }
        return res;
    }
};
struct StrTrie {
    struct Node { int ch[26]; int cnt; };
    vector<Node> T;
    StrTrie(size_t reserve = 0) { T.reserve(reserve + 1); T.push_back(Node{}); }
    int add(int prev, const string& s) {
        int root = (int)T.size(); T.push_back(T[prev]); T[root].cnt++;
        int cur = root;
        for (char c : s) {
            int k = c - 'a', pn = T[cur].ch[k];
            int nx = (int)T.size(); T.push_back(T[pn]); T[nx].cnt++;
            T[cur].ch[k] = nx; cur = nx;
        }
        return root;
    }
    int countPrefix(int u, int v, const string& p) {     // v=0 si no hay rango
        for (char c : p) { u = T[u].ch[c - 'a']; v = T[v].ch[c - 'a']; if (!u) return 0; }
        return T[u].cnt - T[v].cnt;
    }
};
#ifdef DEMO
int main() {
    BinTrie t; vector<int> r(1, 0);
    for (int x : {5, 1, 7, 2, 7, 4}) r.push_back(t.insert(r.back(), x));
    assert(t.maxXor(r[6], r[0], 3) == 7 && t.kthXor(r[5], r[1], 3, 1) == 1);
    StrTrie s; vector<int> w(1, 0);
    for (string x : {"arbol", "arco", "casa", "arbusto", "ar", "cosa"}) w.push_back(s.add(w.back(), x));
    assert(s.countPrefix(w[6], w[0], "ar") == 4 && s.countPrefix(w[4], w[1], "arb") == 1);
    puts("Tries ok");
}
#endif
