
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include "Matriz.h"

//v = valor moneda tipo i
//k = num monedas tipo i elegidas
//c = num total monedas tipo i
//i = tipo de moneda
//j = cantidad que queda por pagar
//
//sol(i,j) = min ( k + sol(i-1, j-k*v )
//        0<=k<=min(c, j/v)
//
//sol(0, j) = Infinito si j>0
//sol(i, j) = 0

const int Infinito = 1000000000;

struct Moneda {
    int valor;
    int cantidad;
};

int resolver(std::vector<Moneda>& monedas, int precio) {
    int n = monedas.size();

    //Vector en lugar de matriz para ahorrar espacio pues solo nos hace falta la fila superior
    std::vector<int> sol(precio + 1, Infinito); sol[0] = 0; 

    for (int i = 1; i < n; ++i) {
        for (int j = precio; j > 0; --j) {
            int aux = Infinito;
            int cotaSuperior = std::min(monedas[i].cantidad, j / monedas[i].valor); //min(c, j/v)

            for (int k = 0; k <= cotaSuperior; ++k) { // 0 <= k <= min(c, j/v)
                aux = std::min(aux, k + sol[j - k * monedas[i].valor]);
            }
            sol[j] = aux;
        }
    }
    return sol[precio];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!std::cin)
        return false;

    std::vector<Moneda> monedas(N + 1, { 0, 0 });
    for (int i = 1; i <= N; ++i) {
        std::cin >> monedas[i].valor;
    }
    for (int i = 1; i <= N; ++i) {
        std::cin >> monedas[i].cantidad;
    }

    int P;
    std::cin >> P;

    //Escribir solución
    int sol = resolver(monedas, P);

    if(sol != Infinito)
        std::cout << "SI " << sol << '\n';
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
