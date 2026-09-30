// Pila y cola persistentes.  Las versiones se identifican por un int (0 = vacia); cada operacion devuelve la nueva version.
//   PStack: push(v,x), pop(v) (version sin el tope), top(v), sum(v) (suma de la pila), size(v)
//   PQueue: push(v,x), pop(v,out) (out = elemento sacado), front(v), size(v)   [binary lifting, O(log n) por pop]
#include <bits/stdc++.h>
using namespace std;
struct PStack {
    vector<int> par, val, dep; vector<long long> sm;
    PStack() : par(1, 0), val(1, 0), dep(1, 0), sm(1, 0) {}     // nodo 0 = vacia; version = nodo tope
    int push(int v, int x) { par.push_back(v); val.push_back(x); dep.push_back(dep[v] + 1); sm.push_back(sm[v] + x); return (int)par.size() - 1; }
    int pop(int v) { return par[v]; }
    int top(int v) { return val[v]; }
    long long sum(int v) { return sm[v]; }
    int size(int v) { return dep[v]; }
};
struct PQueue {
    static const int LOG = 20;
    vector<array<int, LOG>> up; vector<int> val, dep;     // nodos = elementos empujados (arbol)
    vector<int> tail, sz;                                  // version -> (ultimo nodo, tamano)
    PQueue() : up(1), val(1, 0), dep(1, 0), tail(1, 0), sz(1, 0) { up[0].fill(0); }
    int push(int v, int x) {
        int u = (int)up.size(); up.emplace_back(); val.push_back(x); dep.push_back(dep[tail[v]] + 1);
        up[u][0] = tail[v]; for (int j = 1; j < LOG; j++) up[u][j] = up[up[u][j - 1]][j - 1];
        tail.push_back(u); sz.push_back(sz[v] + 1);
        return (int)tail.size() - 1;
    }
    int front(int v) { int u = tail[v], d = sz[v] - 1; for (int j = 0; j < LOG; j++) if (d >> j & 1) u = up[u][j]; return val[u]; }
    int pop(int v, int& out) { out = front(v); tail.push_back(tail[v]); sz.push_back(sz[v] - 1); return (int)tail.size() - 1; }
    int size(int v) { return sz[v]; }
};
#ifdef DEMO
int main() {
    PStack s; int a = s.push(0, 1), b = s.push(a, 5), c = s.pop(b), d = s.push(a, 4);
    assert(s.sum(b) == 6 && c == a && s.sum(d) == 5 && s.top(b) == 5);
    PQueue q; int v1 = q.push(0, 1), v2 = q.push(v1, 2), v3 = q.push(v2, 3), v4 = q.push(v2, 4); int o;
    int v5 = q.pop(v3, o); assert(o == 1);
    int v6 = q.pop(v5, o); assert(o == 2); (void)v4; (void)v6;
    int v7 = q.pop(v4, o); assert(o == 1); (void)v7;
    puts("Pila/Cola ok");
}
#endif
