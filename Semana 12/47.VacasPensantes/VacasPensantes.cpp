// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>
#include "Matriz.h"

//sol(i,j) = { max(sol(i+1, j) + cubo[i], sol(i, j-1) + cubo[j])
//
//sol(i,j) = 0 si i>j
//sol(i,i) = cubo[i]

int resolver(std::vector<int> const& cubos, int i, int j, Matriz<int>& sol) {
    int& res = sol[i][j];

    if (i > 0 || j < cubos.size() - 1) { //Devoradora
        if (cubos[i] > cubos[j]) ++i;
        else --j;
    }

    if (res == -1) {
        if (i > j) res = 0; //Caso base
        else if (i == j) res = cubos[i];
        else {
            res = std::max(resolver(cubos, i + 1, j, sol) + cubos[i],
                           resolver(cubos, i, j - 1, sol) + cubos[j]);
            
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

    if (!N) // Fin de la entrada
        return false;

    std::vector<int> cubos;
    cubos.reserve(N);
    int n;

    for (int i = 0; i < N; ++i) {
        std::cin >> n;
        cubos.push_back(n);
    }

    Matriz<int> mat(N, N, -1);
    int sol = resolver(cubos, 0, N - 1, mat);
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