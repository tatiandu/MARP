// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Pelicula {
    int comienzo;
    int final;
    int duracion;

    Pelicula(int ini, int dur) : comienzo(ini), duracion(dur) {
        final = comienzo + duracion;
    }
};

bool operator<(Pelicula const& a, Pelicula const& b) {
    return b.comienzo > a.comienzo;
}

//i = pelis de la i a la n
//sol(i,j) = { sol(i+1, j) si comienzo.i < j
//           { max(sol(i+1, j), sol(i+1, final.i+10) + duracion.i) si comienzo.i >= j
//sol(n+1,j) = 0

int resolver(std::vector<Pelicula> const& pelis) {
    int n = pelis.size();
    int T = 24*60 + 10; //10 minutos extra
    std::vector<int> sol(T+1, 0);

    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j <= T; ++j) {
            if (pelis[i].comienzo < j)
                break;
            sol[j] = std::max(sol[pelis[i].final + 10] + pelis[i].duracion, sol[j]);
        }
    }
    return sol[0];
}

//Resuelve un caso de prueba
bool resuelveCaso()
{
    // Leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!N) // Fin de la entrada
        return false;

    std::vector<Pelicula> pelis;
    pelis.reserve(N);
    int h, m, d;
    char aux;

    for (int i = 0; i < N; ++i) {
        std::cin >> h >> aux >> m >> d;
        m += h * 60; //pasar horas a minutos y sumar
        Pelicula p = Pelicula(m, d);
        pelis.push_back(p);
    }

    // solucion
    sort(pelis.begin(), pelis.end());
    int sol = resolver(pelis);
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