
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <queue>
#include <unordered_map>

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
    //std::queue<int> camino(int v) const {
    //    if (!visit[v]) throw std::domain_error("No existe camino");
    //    std::queue<int> cam;
    //    for (int x = v; x != s; x = ant[x])
    //        cam.push(x);
    //    cam.push(s);
    //    return cam;
    //}

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

    Digrafo g(N * N);
    std::unordered_map<int, int> serpEsc;
    int a, b;

    for (int i = 0; i < S+E; ++i) {
        std::cin >> a >> b;
        serpEsc.insert({ a-1, b-1 });
    }

    int V = N * N;
    //Hacer grafo
    for (int i = 0; i < V-1; ++i) { //Si n = 10, de 1 a 99
        for (int j = K; j >= 1; --j) {

            int x = i + j; //Porque de i puedes acceder a i+1, i+2, ... , i+K

            if (x < V) {
                if (serpEsc.find(x) != serpEsc.end()) { //Serpiente en x
                    g.ponArista(i, serpEsc[x]);
                } else {
                    g.ponArista(i, x);
                }
            }
        }
    }

    //for (int i = 0; i < g.V(); ++i) {
    //    std::cout << i+1 << ": ";
    //    for (int j : g.ady(i)) {
    //        std::cout << j+1 << " ";
    //    }
    //    std::cout << '\n';
    //}

    // escribir sol
    CaminoMasCorto sol(g, 0);
    std::cout << sol.distancia(V -1) << '\n';

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
