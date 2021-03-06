// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>
#include "Matriz.h"

//sol(i,j) = { sol(i+1, j-1) + 1 si B[i]=B[j] && (B[i]=1 || B[i]=2)
//           { max(sol(i+2, j), sol(i, j-2), sol(i+1, j-1)) en otro caso
//
//sol(i,j) = 0 si i>=j

int resolver(std::vector<int> const& bizcocho, int i, int j, Matriz<int>& sol) {
    int& res = sol[i][j];

    if (res == -1) {
        if (i >= j-1) res = 0; //Caso base
        else {
            if (bizcocho[i] == bizcocho[j] && bizcocho[i] > 0) {
                res = resolver(bizcocho, i + 1, j - 1, sol) + 1;
            }
            else {
                res = std::max(resolver(bizcocho, i + 2, j, sol),
                               std::max(resolver(bizcocho, i + 1, j - 1, sol),
                                        resolver(bizcocho, i, j - 2, sol)));
            }
        }
    }
    return res;
}

//Resuelve un caso de prueba
bool resuelveCaso()
{
    // Leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!std::cin) // Fin de la entrada
        return false;

    std::vector<int> bizcocho;
    bizcocho.reserve(N);
    int n;

    for (int i = 0; i < N; ++i) {
        std::cin >> n;
        bizcocho.push_back(n);
    }

    Matriz<int> mat(N, N, -1);
    int sol = resolver(bizcocho, 0, N - 1, mat);
    std::cout << sol << '\n';

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