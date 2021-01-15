
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
//#include "EntInf.h"

std::vector<int> resolver(std::vector<int> const& sectores, int valor) {
    int n = sectores.size();
    std::vector<int> dardos(valor + 1, 100000); //Lo que seria la primera fila de la matriz
    dardos[0] = 0;

    //Calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i) {
        for (int j = sectores[i - 1]; j <= valor; ++j) {
            dardos[j] = std::min(dardos[j], dardos[j - sectores[i - 1]] + 1);
        }
    }

    std::vector<int> sol;
    if (dardos[valor] != 100000) { //Si es infinito es que no hay solucion
        int i = n, j = valor;
        while (j > 0) { //si aun no hemos llegado al valor buscado

            //1. Si el valor del sector i es menor o igual que el valor que nos queda por completar
            //2. Si nos vale ese sector i
            if (sectores[i - 1] <= j && dardos[j] == dardos[j - sectores[i - 1]] + 1) {
                //Dardo al sector i
                sol.push_back(sectores[i - 1]);
                j = j - sectores[i - 1];
            }
            else //No nos vale ese sector i
                --i;
        }
    }
    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int V, S;
    std::cin >> V >> S;

    if (!std::cin)  // fin de la entrada
        return false;

    int s;
    std::vector<int> sectores;
    for (int i = 0; i < S; ++i) {
        std::cin >> s;
        sectores.push_back(s);
    }

    // escribir sol
    std::vector<int> sol = resolver(sectores, V);

    int n = sol.size();
    if (n > 0) {
        std::cout << sol.size() << ":";
        for (int i = 0; i < sol.size(); ++i) {
            std::cout << " " << sol.at(i);
        }
    }
    else {
        std::cout << "Imposible";
    }
    std::cout << '\n';

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