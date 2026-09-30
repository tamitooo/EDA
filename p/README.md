# Persistencia - EDA (C++17)

Cada `src/NN_*.cpp` es un programa completo (con `main`, lee de stdin). Probados con los ejemplos de los enunciados.
Compilar uno:  `g++ -O2 -std=c++17 src/01_historial_diccionario.cpp -o a && ./a < tests/01.in`
Todos: `./run_tests.sh` (en Windows: Git Bash / WSL). Usan `<bits/stdc++.h>` (g++/MinGW; MSVC no lo trae).

## Del simulacro
| # | Problema | Idea |
|---|----------|------|
| 01 | Historial de Diccionario | trie persistente; "volver a t" = copiar la raiz |
| 02 | Xor historico | trie persistente sobre arbol (root[hijo] = root[padre] + a) |
| 03 | k-esimo Xor en rango | trie persistente por prefijos, hijo preferido = bit de x |
| 04 | Multiconjunto | segtree persistente dinamico [0,1e9], k-esimo |
| 05 | Prefijos en rango | trie persistente por indice, cnt(r) - cnt(l-1) |
| 06 | Snowmen | pila persistente (lista con padre y suma) |
| 07 | Persistent Array | segtree persistente, update puntual |
| 08 | Persistent Queue | arbol de pushes + (tail,size) + binary lifting |
| 09 | Intercity Express | segtree persistente (max) por tickets ordenados por fin |
| 10 | K-th Element on a Segment | segtree persistente sobre valores |
| 11 | Rollback | version l (de der. a izq.): 1 en primera aparicion; k-esimo 1 |
| 12 | K-Query | (j-i+1) - #(<=k) con persistente |
| 13 | K-Query Online | igual + decodificacion xor |
| 14 | D-Query | version r: 1 en ultima aparicion |
| 15 | Till I Collapse | salto goloso por k con la estructura de 11 |
| 16 | Hossam (impar minimo) | persistente con hash xor por paridad |
| 17 | Llave Xor (editorial) | trie persistente, max xor en rango, multi-test |

## Extras que podrian caer (formato definido en el comentario de cada archivo)
| # | Tema |
|---|------|
| 18 | versiones + set puntual + suma en rango |
| 19 | versiones + suma/add en rango (lazy sin propagar) |
| 20 | MEX en rango |
| 21 | DSU persistente (online) |
| 22 | misma entrada que 21, offline con DSU + rollback |
| 23 | conteo de valores en [lo,hi] dentro de [l,r] |

## Receta general
1. Cada update crea O(log) nodos nuevos y copia el resto -> `root[i]` es la version i.
2. "Volver a la version t" / ramificar: `ver[i] = ver[t]` (o `ver[v]` modificado).
3. Rango [l,r] = `root[r]` menos `root[l-1]` (conteos/sumas se restan).
4. Nodo 0 = nulo con todo en 0; reservar ~ (#updates * (log+1)) nodos.
5. Distintos / primera o ultima aparicion: poner 1 en la posicion y quitar 1 en la anterior/siguiente.

## Estructuras sueltas (`estructuras/`, para copiar al examen)
Sin `main` (solo hay uno de prueba dentro de `#ifdef DEMO`). Se usan con `#include "archivo.hpp"` o pegando el contenido.
| Archivo | Contiene |
|---------|----------|
| persistent_segtree.hpp | `PST`: suma/conteo, `add`, `range`, `kth`, `cntLess`; rango [lo,hi] dinamico (sirve para [0,1e9]) |
| persistent_segtree_lazy.hpp | `PSTL`: add en rango + suma en rango con versiones |
| persistent_trie.hpp | `BinTrie` (max xor, k-esimo xor) y `StrTrie` (prefijos) |
| persistent_stack_queue.hpp | `PStack` y `PQueue` |
| dsu_persistente_y_rollback.hpp | `PDSU` (online) y `RDSU` (rollback) |

Probar una: `g++ -std=c++17 -DDEMO -x c++ estructuras/persistent_segtree.hpp -o t && ./t`
Ejemplo de uso de PST por prefijos:
```cpp
PST t(0, M-1);            // valores comprimidos 0..M-1
vector<int> root(n+1, 0);
for (int i = 1; i <= n; i++) root[i] = t.add(root[i-1], id[i], 1);
t.kth(root[r], root[l-1], k);   // k-esimo en a[l..r]
```
