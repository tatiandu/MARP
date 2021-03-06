// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"

const int Infinite = 1000000;

struct Bombilla {
    int potencia;
    int coste;
};

std::pair<int, int> resolver(const std::vector<Bombilla>& B, int pMax, int pMin) {
    int n = B.size();
    std::vector<int> bombillas(pMax + 1, Infinite); //Costes??
    bombillas[0] = 0;

    //matriz sobre el propio vector
    for (int i = 1; i <= n; ++i) {
        for (int j = B[i - 1].potencia; j <= pMax; ++j) {
            bombillas[j] = std::min(bombillas[j], bombillas[j - B[i - 1].potencia] + B[i-1].coste);
        }
    }

    std::pair<int, int> sol;
    int min = bombillas[pMin];
    sol.first = min;
    sol.second = pMin;

    for (int i = pMin + 1; i <= pMax; ++i) {
        min = std::min(min, bombillas[i]);
        if (min < sol.first) { //Hemos encontrado uno mejor
            sol.first = min;
            sol.second = i;
        }
    }
    return sol;
}

//Resuelve un caso de prueba
bool resuelveCaso()
{
    // Leer los datos de la entrada
    int N, pMax, pMin;
    std::cin >> N >> pMax >> pMin;

    if (!std::cin) // Fin de la entrada
        return false;

    std::vector<Bombilla> bombillas (N);
    int b;

    for (int i = 0; i < N; ++i) {
        std::cin >> b;
        bombillas[i].potencia = b;
    }
    for (int i = 0; i < N; ++i) {
        std::cin >> b;
        bombillas[i].coste = b;
    }

    const std::pair<int, int>& sol = resolver(bombillas, pMax, pMin);
    if (sol.first == Infinite)
        std::cout << "IMPOSIBLE\n";
    else 
        std::cout << sol.first << ' ' << sol.second << '\n';

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