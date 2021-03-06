
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

class SinTeclado
{
public:
    SinTeclado(DigrafoValorado<int> const& g, int tCargaOrig, int orig) :
        origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = tCargaOrig;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v) const { return dist[v]; }

private:
    const int INF = 1000000;
    int origen;
    std::vector<int> dist;
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;

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
    int N;
    std::cin >> N;

    if (!N)
        return false;

    std::vector<int> tCarga;
    tCarga.reserve(N);
    for (int i = 0; i < N; ++i) {
        int t;
        std::cin >> t;
        tCarga.push_back(t);
    }

    int M, a, b, c;
    std::cin >> M;
    DigrafoValorado<int> g(N);
    for (int i = 0; i < M; ++i) {
        std::cin >> a >> b >> c;
        int valor = c + tCarga[b - 1];
        g.ponArista(AristaDirigida<int>(a-1, b-1, valor));
    }

    SinTeclado sol(g, tCarga[0], 0);
    if (sol.hayCamino(N - 1))
        std::cout << sol.distancia(N - 1) << '\n';
    else
        std::cout << "IMPOSIBLE\n";

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
