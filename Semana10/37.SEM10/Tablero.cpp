// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"

struct Solution {
    int sum;
    int col;
};

std::vector<int> resolver_rec(const Matriz<int>& tablero)
{
    int N = tablero.numcols();
    std::vector<int> juego(N);

    juego = tablero[0]; //caso base

    for (int i = 1; i < N; ++i) {
        int anterior = juego[0];
        juego[0] = std::max(juego[0], juego[1]) + tablero[i][0];
        for (int j = 1; j < N - 1; ++j) {
            int actual = juego[j];
            juego[j] = std::max(std::max(anterior, juego[j]), juego[j + 1]) + tablero[i][j];
            anterior = actual;
        }
        juego[N - 1] = std::max(anterior, juego[N - 1]) + tablero[i][N - 1];
    }
    return juego;
}

Solution resolver(const Matriz<int>& tablero)
{
    const std::vector<int>& juego = resolver_rec(tablero);

    Solution sol;
    int max = sol.sum = juego[0];
    sol.col = 0;

    for (int i = 1; i < juego.size(); ++i) {
        max = std::max(max, juego[i]);
        if (max != sol.sum) { //Si hemos encontrado uno mejor
            sol.sum = max;
            sol.col = i;
        }
    }
    return sol;
}

//Resuelve un caso de prueba
bool resuelveCaso()
{
    // Leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!std::cin) // Fin de la entrada
        return false;

    Matriz<int> tablero(N, N, 0);
    int v;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> v;
            tablero[i][j] = v;
        }
    }

    Solution sol = resolver(tablero);
    std::cout << sol.sum << ' ' << sol.col+1 << '\n';

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