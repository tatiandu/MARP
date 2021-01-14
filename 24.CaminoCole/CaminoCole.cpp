
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

class CaminosMin
{
public:
    CaminosMin(DigrafoValorado<int> const& g, int orig) :
        origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()), caminos(g.V(), 0) {
        dist[origen] = 0;
        caminos[origen] = 1;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int64_t calculaNCaminos(DigrafoValorado<int> const& g, int v) {
        if (!hayCamino(v)) return 0;

        if (caminos[v] == 0) {
            int64_t min = distancia(v);
            for (auto a : g.ady(v)) {
                int w = a.hasta();
                if (dist[w] + a.valor() <= min) {
                    caminos[v] += calculaNCaminos(g, w);
                }
            }
        }
        return caminos[v];
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    int64_t distancia(int v) const { return dist[v]; }
    int64_t nCaminos(int v) const { return caminos[v]; }

private:
    const int INF = 1000000000;
    int origen;
    std::vector<int64_t> dist;
    std::vector<int64_t> caminos; //Caminos minimos a cada indice
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<int64_t> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin)
        return false;

    int a, b, c;
    DigrafoValorado<int> g(V);
    for (int i = 0; i < A; ++i) {
        std::cin >> a >> b >> c;
        g.ponArista(AristaDirigida<int>(a - 1, b - 1, c));
        g.ponArista(AristaDirigida<int>(b - 1, a - 1, c));
    }

    CaminosMin sol(g, 0);
    std::cout << sol.calculaNCaminos(g, V - 1) << '\n';

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
