
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

class CaminosMin
{
public:
    CaminosMin(DigrafoValorado<int> const& g, int orig) :
        origen(orig), dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    int64_t distancia(int v) const { return dist[v]; }

private:
    const int INF = 1000000000;
    int origen;
    std::vector<int64_t> dist;
    IndexPQ<int64_t> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!std::cin)
        return false;

    int v;
    DigrafoValorado<int> g(N);
    for (int i = 0; i < N-1; ++i) {
        for (int j = i+1; j < N; ++j) {
            std::cin >> v;
            g.ponArista(AristaDirigida<int>(i, j, v));
        }
    }

    // escribir sol
    for (int i = 0; i < N - 1; ++i) {
        CaminosMin sol(g, i);

        for (int j = i + 1; j < N; ++j) {
            std::cout << sol.distancia(j) << ' ';
        }
        std::cout << '\n';
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
