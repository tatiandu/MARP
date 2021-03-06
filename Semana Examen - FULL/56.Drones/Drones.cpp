// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <queue>

using pQueue = std::priority_queue<int, std::vector<int>, std::less<int>>;

std::vector<int> resolver(std::priority_queue<int> pilasA, std::priority_queue<int> pilasB, int N) {
    std::vector<int> sol;

    while (!pilasA.empty() && !pilasB.empty()) {
        int tiempoVueloDron;
        int tiempoVueloTotal = 0;
        int nDrones = 0;
        std::vector<int> auxA; std::vector<int> auxB;

        while (!pilasA.empty() && !pilasB.empty() && nDrones < N) {
            ++nDrones;

            int a = pilasA.top(); pilasA.pop();
            int b = pilasB.top(); pilasB.pop();
            tiempoVueloDron = std::min(a, b);

            if (a != b) { //Si no se descargaron las dos pilas
                if (tiempoVueloDron == a) auxB.push_back(b - a);
                else auxA.push_back(a - b);
            }
            tiempoVueloTotal += tiempoVueloDron;
        }
        sol.push_back(tiempoVueloTotal); //Horas de vuelo de ese día

        //Guardamos las pilas que aún tienen carga
        for (int i = 0; i < auxA.size(); ++i)
            pilasA.push(auxA[i]);
        for (int i = 0; i < auxB.size(); ++i)
            pilasB.push(auxB[i]);
    }
    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!std::cin)
        return false;

    int A, B, t;
    std::cin >> A >> B;

    std::priority_queue<int> pilasA;
    for (int i = 0; i < A; ++i) {
        std::cin >> t;
        pilasA.push(t);
    }

    std::priority_queue<int> pilasB;
    for (int i = 0; i < B; ++i) {
        std::cin >> t;
        pilasB.push(t);
    }

    // escribir sol
    std::vector<int> sol = resolver(pilasA, pilasB, N);

    for (int i = 0; i < sol.size(); ++i)
        std::cout << sol[i] << ' ';

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