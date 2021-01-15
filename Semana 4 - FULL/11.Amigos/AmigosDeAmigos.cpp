
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Grafo.h"

class MaximaCompConexa
{
public:
    MaximaCompConexa(Grafo const &g) : visit(g.V(), false), maxim(0)
    {
        for (int v = 0; v < g.V(); ++v)
        {
            if (!visit[v])
            { // se recorre una nueva componente conexa
                int tam = dfs(g, v);
                maxim = std::max(maxim, tam);
            }
        }
    }
    // tamaño máximo de una componente conexa
    int maximo() const
    {
        return maxim;
    }

private:
    std::vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    int maxim;               // tamaño de la componente mayor
    int dfs(Grafo const &g, int v)
    {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v))
        {
            if (!visit[w])
                tam += dfs(g, w);
        }
        return tam;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() { //O(V+A)
   
// leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    Grafo g(V); //construye grafo
    int v, w;

    for (int i = 0; i < A; ++i) {
        std::cin >> v >> w;
        g.ponArista(v-1, w-1); //para que empiece en 0
    }
    MaximaCompConexa mcc(g);
    std::cout << mcc.maximo() << '\n';
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
