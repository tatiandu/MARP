
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include <queue>

class ARM_Kruskal
{
private:
    std::vector<Arista<int>> _ARM;
    std::vector<bool> visit;
    int coste;
    bool conexo;
    bool todosV;

public:
    int costeARM() const {
        return coste;
    }
    /*std::vector<Arista<int>> const& ARM() const {
        return _ARM;
    }*/
    bool todosVertices() const { return todosV; }

    bool esConexo() const { return conexo; }

    ARM_Kruskal(GrafoValorado<int> const& g) : coste(0), visit(g.V(), false), conexo(false), todosV(false) {
        std::priority_queue<Arista<int>, std::vector<Arista<int>>, std::greater<Arista<int>>> pq;
        auto aristas = g.aristas();
        for (int i = 0; i < aristas.size(); ++i) {
            pq.push(aristas[i]);
        }

        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                visit[v] = visit[w] = true;
                _ARM.push_back(a); coste += a.valor();

                if (_ARM.size() == g.V() - 1) break;
            }
        }

        if (cjtos.num_cjtos() == 1) conexo = true;
        if (cjtos.cardinal(0) == g.V()) todosV = true;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int I, P;
    std::cin >> I >> P;

    if (!std::cin)
        return false;

    int a, b, c;
    GrafoValorado<int> g(I);
    for (int i = 0; i < P; ++i) {
        std::cin >> a >> b >> c;
        g.ponArista(Arista<int>(a - 1, b - 1, c));
    }

    ARM_Kruskal arm(g);
    if (arm.esConexo() && arm.todosVertices()) std::cout << arm.costeARM() << '\n';
    else std::cout << "No hay puentes suficientes\n";

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
