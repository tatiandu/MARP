
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <vector>

//1. Posible formar la cuerda deseada
//2. Cuantas formas de formar la cuerda
//3. Minimo numero posible de sub-cuerdas
//4. Minimo coste

const int64_t Infinito = 1000000000000000000;

struct Cuerda {
    int longitud;
    int coste;

    Cuerda(int l, int c) : longitud(l), coste(c) {}
};

//1. sol(i,j) = { sol(i-1, j) si    i.longitud > j
//              { sol(i-1, j-i.longitud || sol(i-1, j) si    i.longitud <= j
// sol(0,j) = false si j>0
// sol(i,0) = true
bool resolver1(std::vector<Cuerda> const& cuerdas, int L) {
    int n = cuerdas.size();
    std::vector<bool> sol(L + 1, false);
    sol[0] = true;

    for (int i = 0; i < n; ++i) {
        for (int j = L; j > 0; --j) {
            if (cuerdas[i].longitud > j)
                break;
            sol[j] = sol[j - cuerdas[i].longitud] || sol[j];
        }
    }
    return sol[L];
}

//2. sol(i,j) = { sol(i-1, j) si    i.longitud > j
//              { sol(i-1, j-i.longitud + sol(i-1, j) si    i.longitud <= j
// sol(0,j) = 0 si j>0
// sol(i,0) = 1
int64_t resolver2(std::vector<Cuerda> const& cuerdas, int L) {
    int n = cuerdas.size();
    std::vector<int64_t> sol(L + 1, 0);
    sol[0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = L; j > 0; --j) {
            if (cuerdas[i].longitud > j)
                break;
            sol[j] += sol[j - cuerdas[i].longitud];
        }
    }
    return sol[L];
}

//3. sol(i,j) = { sol(i-1, j) si    i.longitud > j
//              { min(sol(i-1, j-i.longitud) + 1, sol(i-1, j)) si    i.longitud <= j
// sol(0,j) = Infinito si j>0
// sol(i,0) = 0
int64_t resolver3(std::vector<Cuerda> const& cuerdas, int L) {
    int n = cuerdas.size();
    std::vector<int64_t> sol(L + 1, Infinito);
    sol[0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = L; j > 0; --j) {
            if (cuerdas[i].longitud > j)
                break;
            sol[j] = std::min(sol[j - cuerdas[i].longitud] + 1, sol[j]);
        }
    }
    return sol[L];
}

//4. sol(i,j) = { sol(i-1, j) si    i.longitud > j
//              { min(sol(i-1, j-i.longitud) + i.coste, sol(i-1, j)) si    i.longitud <= j
// sol(0,j) = Infinito si j>0
// sol(i,0) = 0
int64_t resolver4(std::vector<Cuerda> const& cuerdas, int L) {
    int n = cuerdas.size();
    std::vector<int64_t> sol(L + 1, Infinito);
    sol[0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = L; j > 0; --j) {
            if (cuerdas[i].longitud > j)
                break;
            sol[j] = std::min(sol[j - cuerdas[i].longitud] + cuerdas[i].coste, sol[j]);
        }
    }
    return sol[L];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, L;
    std::cin >> N >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    int l, c;
    std::vector<Cuerda> cuerdas;
    for (int i = 0; i < N; ++i) {
        std::cin >> l >> c;
        Cuerda cuerda(l, c);
        cuerdas.push_back(cuerda);
    }

    // escribir sol
    bool sol1 = resolver1(cuerdas, L);

    if (sol1) {
        int64_t sol2 = resolver2(cuerdas, L);
        int64_t sol3 = resolver3(cuerdas, L);
        int64_t sol4 = resolver4(cuerdas, L);
        std::cout << "SI " << sol2 << ' ' << sol3 << ' ' << sol4 << '\n';
    }
    else
        std::cout << "NO\n";

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