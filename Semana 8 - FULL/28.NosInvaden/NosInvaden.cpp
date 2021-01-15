
//Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

int resolver(std::priority_queue<int> enemigos, std::priority_queue<int> aliados) {
    int count = 0; //victorias

    int i = 0;
    while (!aliados.empty()) {
        auto aliado = aliados.top(); aliados.pop();

        while (!enemigos.empty() && aliado < enemigos.top()) {
            enemigos.pop();
        }

        if (!enemigos.empty() && aliado >= enemigos.top()) {
            ++count;
            enemigos.pop();
        }
    }
    return count;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    // leer los datos de la entrada
    std::cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    int v;
    //Para ordenar de mayor a menor
    std::priority_queue<int> enemigos;
    std::priority_queue<int> aliados;

    for (int i = 0; i < N; ++i) {
        std::cin >> v;
        enemigos.push(v);
    }

    for (int i = 0; i < N; ++i) {
        std::cin >> v;
        aliados.push(v);
    }

    // escribir sol
    int sol = resolver(enemigos, aliados);
    std::cout << sol << "\n";

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