
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include "Matriz.h"

//sol(i,j) = min ( sol(i,k) + sol(k,j) + 2*(longitud j-i) )
//            i<=k<=j
//caso base: sol(i, i+1) = 0 porque al ser seguidos no hay que cortar y no se hace esfuerzo

const int Infinito = 1000000000;

int resolver(std::vector<int>& cortes, int L) {
    int n = cortes.size();

    Matriz<int> M(n, n, 0); 
    for (int d = 2; d <= n; ++d) { // d = 2 porque los casos base son d = 1
        for (int i = 0; i < n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            M[i][j] = Infinito;
            for (int k = i + 1; k < j; ++k) {
                int temp = M[i][k] + M[k][j] + 2 * (cortes[j] - cortes[i]);
                if (temp < M[i][j]) {
                    M[i][j] = temp;
                }
            }
        }
    }
    return M[0][n-1]; //De 0 a L
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int L, N;
    std::cin >> L >> N;

    if (!L && !N)
        return false;

    std::vector<int> cortes(N + 2, 0); // +2 por longitud L y longitud 0
    cortes[N + 1] = L;
    for (int i = 1; i <= N; ++i) {
        std::cin >> cortes[i];
    }

    //Escribir solución
    std::cout << resolver(cortes, L) << '\n';

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
