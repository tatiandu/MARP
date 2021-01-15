// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"
#include <unordered_map>

const int Infinito = 1000000;

//Floyd O(n^3) siendo n = num personas
int gradoSep(Matriz<int>& G) {
    int V = G.numfils(); // número de vértices del grafo

    for (int k = 0; k < V; ++k) { // actualizaciones de las matrices
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = G[i][k] + G[k][j];
                if (temp < G[i][j]) { // es mejor pasar por k
                    G[i][j] = temp;
                }
            }
        }
    }

    int gradoSeparacion = 0;

    for (int i = 0; i < V; ++i) {
        for (int j = i+1; j < V; ++j) {
            gradoSeparacion = std::max(gradoSeparacion, G[i][j]);
        }
    }
    return gradoSeparacion;
}

//Resuelve un caso de prueba
bool resuelveCaso()
{
    // Leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin) // Fin de la entrada
        return false;

    Matriz<int> grafo(V, V, Infinito);
    for (int i = 0; i < V; ++i) {
        grafo[i][i] = 0;
    }

    std::string n, m;
    std::unordered_map<std::string, int> map;
    int indice = 0;

    for (int i = 0; i < A; ++i) {
        std::cin >> n >> m;

        if (map.find(n) == map.end()) { //Nombre 1
            map.insert({ n, indice });
            ++indice;
        }
        if (map.find(m) == map.end()) { //Nombre 2
            map.insert({ m, indice });
            ++indice;
        }
        grafo[map[n]][map[m]] = 1; // 1 = hay arista
        grafo[map[m]][map[n]] = 1;
    }

    //Escribir solución
    int sol = gradoSep(grafo);
    if (sol != Infinito)
        std::cout << sol << '\n';
    else
        std::cout << "DESCONECTADA\n";

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