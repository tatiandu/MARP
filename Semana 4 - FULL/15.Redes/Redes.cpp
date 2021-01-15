
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include "Grafo.h"

int bfs(Grafo const &g, int n, int ttl, std::vector<bool>& visit)
{
    int inalcanzables = g.V();
    std::vector<int> dist(g.V(), 0);   // dist[v] = aristas en el camino s-v más corto
    std::queue<int> q;

    dist[n] = 0;
    visit[n] = true;
    inalcanzables--;
    q.push(n);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if(dist[v] == ttl)
            break;

        for (int w : g.ady(v)) {
            if (!visit[w]) {
                dist[w] = dist[v] + 1;
                visit[w] = true;
                inalcanzables--;
                q.push(w);
            }
        }
    }
    return inalcanzables;
}

void resolver(Grafo& g) {
    int consultas, n, ttl, inalcanzables;
    std::cin >> consultas;

    for (int i = 0; i < consultas; ++i) {
        std::cin >> n >> ttl;
        std::vector<bool> visit (g.V(), false); // visit[v] = ¿hay camino de s a v?

        inalcanzables = bfs(g, n-1, ttl, visit);
        
        std::cout << inalcanzables << '\n';
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()  // C*(V+A) ?? (C=consultas)
{
    int V, A;
    std::cin >> V >> A;

    if (!std::cin) //fin de entrada
        return false;

    Grafo g(V); //construye grafo
    int v, w;

    for (int i = 0; i < A; ++i) {
        std::cin >> v >> w;
        g.ponArista(v-1, w-1); //para que empiece en 0
    }
    resolver(g);
    std::cout << "---" << '\n';

    return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
    while(resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
