
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Grafo.h"

void dfs(const Grafo& g, int v, std::vector<bool>& visit, std::vector<int>& ant, int& visitados) {
    visit[v] = true;

    for (int w : g.ady(v)) {

        if (!visit[w]) {
            ant[w] = v;
            dfs(g, w, visit, ant, visitados);
            visitados++;
        }
    }
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(const Grafo& g) {
    std::vector<bool> visit(g.V(), false);
    std::vector<int> ant(g.V());
    int origen = 0, visitados = 0;

    dfs(g, origen, visit, ant, visitados);

    if (visitados >= g.V() - 1 && g.A() == g.V() - 1) { //-1 porque el primero no cuenta
        std::cout << "SI" << '\n';
    }
    else {
        std::cout << "NO" << '\n';
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(V); //construye grafo
    int v, w;

    for (int i = 0; i < A; ++i) {
        std::cin >> v >> w;
        g.ponArista(v, w);
    }
    resolver(g);

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
