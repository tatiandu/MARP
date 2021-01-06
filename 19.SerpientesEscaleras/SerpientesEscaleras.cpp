
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <queue>


class CaminoMasCorto {
public:
    CaminoMasCorto(Digrafo const& g, int s) : visit(g.V(), false),
        ant(g.V()), dist(g.V()), s(s) {
        bfs(g);
    }
    // número de aristas entre s y v
    int distancia(int v) const {
        return dist[v];
    }
    // devuelve el camino más corto desde el origen a v (si existe)
    std::queue<int> camino(int v) const {
        if (!visit[v]) throw std::domain_error("No existe camino");
        std::queue<int> cam;
        for (int x = v; x != s; x = ant[x])
            cam.push(x);
        cam.push(s);
        return cam;
    }

private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
    std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
    int s;

    void bfs(Digrafo const& g) {
        std::queue<int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, K, S, E;
    std::cin >> N >> K >> S >> E;

    if (!N && !K && !S && !E)
        return false;

    Digrafo g(N*N);
    std::queue<std::pair<int, int>> serpientes;
    std::queue<std::pair<int, int>> escaleras;
    int a, b;

    for (int i = 0; i < S; ++i) {
        std::pair<int, int> pair;
        std::cin >> pair.first >> pair.second;

        serpientes.push(pair);
    }
    for (int i = 0; i < E; ++i) {
        std::pair<int, int> pair;
        std::cin >> pair.first >> pair.second;

        escaleras.push(pair);
    }

    //Hacer grafo
    for (int i = 0; i < N*N - 1; ++i) {
        for (int j = 1; j <= K; ++j) {

            int x = i + j;

            if (!serpientes.empty() && i >= serpientes.front().first-1)
                serpientes.pop();
            else if (!escaleras.empty() && i >= escaleras.front().first-1)
                escaleras.pop();

            if (!serpientes.empty() && x == serpientes.front().first-1) {
                g.ponArista(i, serpientes.front().second-1);
            }
            else if (!escaleras.empty() && x == escaleras.front().first-1) {
                g.ponArista(i, escaleras.front().second-1);
            }
            else if (x <= N*N - 1) {
                g.ponArista(i, x);
            }
        }
    }

    // escribir sol
    CaminoMasCorto sol(g, 0);
    std::cout << sol.distancia(99) << '\n';
    std::queue<int> camino = sol.camino(99);

    while (!camino.empty()) {
        std::cout << camino.front() << ' ';
        camino.pop();
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
