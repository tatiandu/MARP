// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Festival {
    int grupos;
    int entrada;

    Festival(int g, int e) : grupos(g), entrada(e) {}
};

//sol(i,j)= { sol(i-1, j) si festival[i].entrada > j
//          { max(sol(i-1, j), sol(i-1, j-festival[i].entrada) + festival[i].grupos) si festival[i].entrada <= j
//sol(0,j) = 0
//sol(i,j) = 0

int resolver(std::vector<Festival> const& festivales, int P) {
    int n = festivales.size();
    std::vector<int64_t> sol(P + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = P; j > 0; --j) {
            if (festivales[i].entrada > j)
                break;
            sol[j] = std::max(sol[j - festivales[i].entrada] + festivales[i].grupos, sol[j]);
        }
    }
    return sol[P];
}

//Resuelve un caso de prueba
bool resuelveCaso()
{
    // Leer los datos de la entrada
    int P, N;
    std::cin >> P >> N;

    if (!std::cin) // Fin de la entrada
        return false;

    std::vector<Festival> festivales;
    festivales.reserve(N);
    int g, e;

    for (int i = 0; i < N; ++i) {
        std::cin >> g >> e;
        Festival f = Festival(g, e);
        festivales.push_back(f);
    }

    int sol = resolver(festivales, P);
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