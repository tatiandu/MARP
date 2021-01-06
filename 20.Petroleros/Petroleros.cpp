
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include "ConjuntosDisjuntos.h"

using Mapa = std::vector<std::string>;
class Manchas
{
public:
    Manchas(Mapa const& M) : F(M.size()), C(M[0].size()),
       maxim(0), cjtos(F*C), visit(F, std::vector<bool>(C, false))
    {
        for (int i = 0; i < F; ++i) {
            for (int j = 0; j < C; ++j)
            {
                if (!visit[i][j] && M[i][j] == '#') {
                    int nuevotam = dfs(M, i, j);
                    maxim = std::max(maxim, nuevotam);
                }
            }
        }
    }
    int maximo() const { return maxim; }

    void nuevaMancha(Mapa const& M, int i, int j) {
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni, nj) && M[ni][nj] == '#') {
                cjtos.unir(i * C + j, ni * C + nj);
            }
        }
        int tam = cjtos.cardinal(i * C + j);
        maxim = std::max(maxim, tam);
    }

private:
    int F, C; // tamaño del mapa
    std::vector<std::vector<bool>> visit;
    int maxim; // tamaño de la mancha más grande
    ConjuntosDisjuntos cjtos;

    bool correcta(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }

    const std::vector<std::pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1},
                                                    {1,1},{1,-1},{-1,-1},{-1,1} };

    int dfs(Mapa const& M, int i, int j) {
        visit[i][j] = true;
        int tam = 1;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
                tam += dfs(M, ni, nj);
                cjtos.unir(i * C + j, ni * C + nj);
            }
        }
        return tam;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int F, C;
    std::cin >> F >> C;

    if (!std::cin)
        return false;

    std::string _;
    std::getline(std::cin, _); //para salto de linea

    Mapa mapa(F);
    // leemos la imagen
    for (std::string& linea : mapa) {
        std::getline(std::cin, linea);
    }

    //escribir sol
    Manchas manchas(mapa);
    std::cout << manchas.maximo() << ' ';

    int N, a, b;
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std::cin >> a >> b;
        a -= 1; b -= 1;
        mapa[a][b] = '#';
        manchas.nuevaMancha(mapa, a, b);
        std::cout << manchas.maximo() << ' ';
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
