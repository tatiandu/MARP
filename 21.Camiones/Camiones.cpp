
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"

class DFS
{
public:
    DFS(GrafoValorado<int> const& G, int v, int u, int umbral) : posible(false), visit(G.V(), false) {
        dfs(G, v, u, umbral);
    }

    bool esPosible() const { return posible; }

private:
    std::vector<int> visit;
    bool posible;

    // visita los nodos alcanzables desde v respetando el umbral, para si llega a w
    void dfs(GrafoValorado<int> const& G, int v, int u, int umbral) {
        if (v == u)
            posible = true;

        visit[v] = true;
        for (auto a : G.ady(v)) {
            if (a.valor() >= umbral) {
                int w = a.otro(v);
                if (!visit[w])
                    dfs(G, w, u, umbral);
            }
        }
    }
};

bool resolver(GrafoValorado<int> const& G) {
    int v, u, umbral;
    std::cin >> v >> u >> umbral;

    DFS camino(G, v-1, u-1, umbral);

    return camino.esPosible();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin)
        return false;

    int a, b, c;
    GrafoValorado<int> g(V);
    for (int i = 0; i < A; ++i) {
        std::cin >> a >> b >> c;
        g.ponArista(Arista<int>(a - 1, b - 1, c));
    }

    int K;
    std::cin >> K;
    for (int i = 0; i < K; ++i) {
        if (resolver(g)) std::cout << "SI\n";
        else std::cout << "NO\n";
    }

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
