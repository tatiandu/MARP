
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Grafo.h"

class ColocarGuardias
{
public:
    ColocarGuardias(Grafo const &g) : visit(g.V(), false), guardia(g.V(), false), totalGuardias(0), imposible(false)
    {
        for (int v = 0; v < g.V() && !imposible; ++v) { //si es imposible para
            if (!visit[v]) // se recorre una nueva componente conexa
            {
                if(!g.ady(v).empty()) { //si tiene adyacentes
                    guardia[v] = true; //marcamos el primer vertice de la componente con guardia
                    int numGuardiasSubg = 1; //numero de guardias por subgrafo
                    int subgrafoV = 1; //a cada llamada a dfs aumentamos el numero de vertices del subgrafo
                    int minim = 0;

                    numGuardiasSubg += dfs(g, v, subgrafoV);
                    
                    if(!imposible) { //si ha sido posible se compara el numero de cruces con guardia y sin guardia
                        if(numGuardiasSubg > 1)  {
                            int minim = std::min(numGuardiasSubg, subgrafoV-numGuardiasSubg);
                            totalGuardias += minim; //una vez calculado el minimo se acumulan
                        }
                        else {
                            totalGuardias += numGuardiasSubg;
                        }                    
                    }
                }  
                else { //si no tiene adyacentes se marca visitado solo
                    visit[v] = true;
                }
            }
        }
    }
    
    int minimo() const { // tamaño minimo de guardias
        return totalGuardias;
    }

    bool esImposible() const { //si es imposible o no (aka si no es bipartirto)
        return imposible;
    }

private:
    std::vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    std::vector<bool> guardia; // guardia[v] = hay guardia en el vértice v?
    int totalGuardias;
    bool imposible;

    int dfs(Grafo const &g, int v, int& sgV)
    {
        int num = 0;
        visit[v] = true;
        
        for (int w : g.ady(v))
        {
            if (!visit[w]) { //si no ha sido visitado
                guardia[w] = !guardia[v]; //marcamos el vertice
                if(guardia[w]) //si hay guardia aumentamos contador
                    num++;

                num += dfs(g, w, ++sgV);
            }
            else { //si ha sido visitado
                if(guardia[w] == guardia[v]) { //si los dos tienen guardia o no
                    imposible = true;
                    return 0;
                }
            }
        }
        return num;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() //O(V+A)
{
    // leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin) //fin de entrada
        return false;

    Grafo g(V); //construye grafo
    int v, w;

    for (int i = 0; i < A; ++i)
    {
        std::cin >> v >> w;
        g.ponArista(v - 1, w - 1); //para que empiece en 0
    }
    ColocarGuardias cg(g);

    if (!cg.esImposible()) //si ha sido posible
        std::cout << cg.minimo() << '\n';
    else
        std::cout << "IMPOSIBLE" << '\n';

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
