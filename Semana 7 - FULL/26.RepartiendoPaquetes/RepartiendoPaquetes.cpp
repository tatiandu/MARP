
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
    std::vector<int> dist;
    IndexPQ<int> pq;

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
    int V, A;
    std::cin >> V >> A;

    if (!std::cin)
        return false;

    int a, b, c;
    DigrafoValorado<int> g(V);
    DigrafoValorado<int> gInv(V);
    for (int i = 0; i < A; ++i) {
        std::cin >> a >> b >> c;
        g.ponArista(AristaDirigida<int>(a - 1, b - 1, c));
        gInv.ponArista(AristaDirigida<int>(b - 1, a - 1, c));
    }

    bool imposible = false;
    int oficina, P, esfuerzoTotal = 0;
    std::cin >> oficina >> P;

    CaminosMin ida(g, oficina - 1);
    CaminosMin vuelta(gInv, oficina - 1);

    for (int i = 0; i < P; ++i) {
        std::cin >> a;

        if (!imposible) {
            if (!ida.hayCamino(a - 1) || !vuelta.hayCamino(a - 1)) {
                imposible = true;
            }
            esfuerzoTotal += ida.distancia(a - 1) + vuelta.distancia(a - 1);
        }
    }

    if (imposible)
        std::cout << "Imposible\n";
    else
        std::cout << esfuerzoTotal << '\n';

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
