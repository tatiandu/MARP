
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include "Digrafo.h"

class OrdenTareas
{
public:
    OrdenTareas(Digrafo const &g) : visit(g.V(), false), ant(g.V()),
                                    apilado(g.V(),false), hayciclo(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }

    std::deque<int> const &getOrden() const {
        return orden;
    }

    bool hayCiclo() const {
        return hayciclo;
    }

private:
    std::vector<bool> visit; //Lista de vertices visitados
    std::vector<int> ant; //Lista de vertices anteriores
    std::vector<bool> apilado; //Pila de vertices apilados por llamada para comprobar si hay ciclo
    std::deque<int> orden; //Ordenación topológica
    bool hayciclo;

    void dfs(Digrafo const &g, int v) //Busca ciclos a la vez que forma 
    {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo) //Termina si hay ciclo
                return;
            if (!visit[w]) { //Consultamos el proximo vertice
                ant[w] = v;
                dfs(g, w);
            }
            else if (apilado[w]) { //Encontramos ciclo
                hayciclo = true;
            }
        }
        orden.push_front(v+1); //devolvemos al valor original
        apilado[v] = false;
    }
};

void resolver(OrdenTareas& tareas, int V) {
    std::deque<int> orden = tareas.getOrden();
    
    if(tareas.hayCiclo()) {
        std::cout << "Imposible" << "\n";
    }
    else { //No hay ciclos, entonces escribimos el orden
        for(int i = 0; i < V; ++i) {
            std::cout << orden[i] << " ";
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    //Leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin) //Fin de la entrada
        return false;

    Digrafo g(V);
    int x, y;
    for(int i = 0; i < A; ++i) {
        std::cin >> x >> y;
        x-=1; y-=1; //Ajustamos a 0 para que no de problemas
        g.ponArista(x, y);
    }

    //Solucion
    OrdenTareas tareas(g);
    resolver(tareas, V);
    std::cout << "\n";
    
    return true;
}

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

        // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}