
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <queue>

class CaminoMasCorto {
public:
    CaminoMasCorto(DigrafoValorado<int> const& g, int origen, int target) :
        visit(g.V(), false), dist(g.V()), origen(origen), target(target) {

        bfs(g);
    }
    bool hayCamino() const { return visit[target]; }
    int distanciaAristas() const { return dist[target]; }

private:
    std::vector<bool> visit;
    std::vector<int> dist;
    int origen, target;

    void bfs(DigrafoValorado<int> const& g) {
        std::queue<int> q;
        dist[origen] = 0; visit[origen] = true;
        q.push(origen);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto a : g.ady(v)) {
                int w = a.hasta();
                if (!visit[w]) {
                    dist[w] = dist[v] + 1;
                    visit[w] = true;

                    if (w == target) return;
                    q.push(w);
                }
            }
        }
    }
};

class CaminosMin
{
public:
    CaminosMin(DigrafoValorado<int> const& g, int orig) :
        origen(orig), dist(g.V(), std::pair<int, int>(INF, 0)), ulti(g.V()), pq(g.V()) {
        dist[origen].first = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v].first != INF; }
    int distanciaValor(int v) const { return dist[v].first; }
    int distanciaAristas(int v) const { return dist[v].second; }

private:
    const int INF = 2147483647;
    int origen;
    std::vector<std::pair<int, int>> dist; //first: valor, second: distancia en aristas del origen
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<int64_t> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w].first > dist[v].first + a.valor()) {
            dist[w].first = dist[v].first + a.valor();
            dist[w].second = dist[v].second + 1;
            ulti[w] = a;
            pq.update(w, dist[w].first);
        }
        else if (dist[w].first == dist[v].first + a.valor() && dist[w].second > dist[v].second + 1) {
            dist[w].second = dist[v].second + 1;
            ulti[w] = a;
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

    int K;
    std::cin >> K;
    for (int i = 0; i < K; ++i) {
        std::cin >> a >> b;

        CaminoMasCorto bfs(g, a - 1, b - 1);
        CaminosMin dijkstra(g, a - 1);

        if (dijkstra.hayCamino(b - 1)) {
            std::cout << dijkstra.distanciaValor(b - 1);

            if (dijkstra.distanciaAristas(b - 1) == bfs.distanciaAristas())
                std::cout << " SI\n";
            else
                std::cout << " NO\n";
        }
        else {
            std::cout << "SIN CAMINO\n";
        }
    }
    std::cout << "---\n";

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
