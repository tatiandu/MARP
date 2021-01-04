// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"

struct Cofre {
    int profundidad;
    int valor;

    Cofre(int p, int v) : profundidad(p), valor(v) {}
};

int tesoro_rec(std::vector<Cofre> const& obj, int i, int j, Matriz<int>& tesoro)
{
    if (tesoro[i][j] != -1) // subproblema ya resuelto
        return tesoro[i][j];

    if (i == 0 || j == 0)
        tesoro[i][j] = 0;
    else if (obj[i - 1].profundidad * 3 > j) //p + 2p
        tesoro[i][j] = tesoro_rec(obj, i - 1, j, tesoro);
    else
        tesoro[i][j] = std::max(tesoro_rec(obj, i - 1, j, tesoro), tesoro_rec(obj, i - 1, j - obj[i - 1].profundidad * 3, tesoro) //p + p2
            + obj[i - 1].valor);
    
    return tesoro[i][j];
}

std::pair<int, int> resolver(std::vector<Cofre> const& cofres, int T, std::vector<bool>& sol) {
    int n = cofres.size();
    Matriz<int> tesoro(n + 1, T + 1, -1);
    int valor = tesoro_rec(cofres, n, T, tesoro);

    int i = n, j = T;
    int nCofres = 0;

    std::pair<int, int> pair;
    sol = std::vector<bool>(n, false);
    while (i > 0 && j > 0) {
        if (tesoro[i][j] != tesoro[i - 1][j]) { //Cogemos cofre i
            sol[i - 1] = true;
            j = j - cofres[i - 1].profundidad*3; //p+2p
            ++nCofres;
        }
        --i; //No cogemos cofre i
    }
    pair.first = valor;
    pair.second = nCofres;

    return pair;
}

//Resuelve un caso de prueba
bool resuelveCaso()
{
    // Leer los datos de la entrada
    int T, N;
    std::cin >> T >> N;

    if (!std::cin) // Fin de la entrada
        return false;

    std::vector<Cofre> cofres;
    cofres.reserve(N);
    int p, v;

    for (int i = 0; i < N; ++i) {
        std::cin >> p >> v;
        Cofre c = Cofre(p, v);
        cofres.push_back(c);
    }
    
    std::vector<bool> sol;
    std::pair<int, int> tesoro = resolver(cofres, T, sol);
    
    std::cout << tesoro.first << '\n';
    std::cout << tesoro.second << '\n';
    for (int i = 0; i < sol.size(); ++i) {
        if (sol[i]) {
            std::cout << cofres[i].profundidad << ' ' << cofres[i].valor << '\n';
        }
    }
    std::cout << "---\n";

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