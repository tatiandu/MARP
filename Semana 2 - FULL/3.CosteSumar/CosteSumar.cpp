
// Tatiana Duarte Balvís

// Ordeno las actividade de menor a mayor según cuando comiencen
// Con una cola de int marco cuando quedará libre cada una de las personas
// Para saber si podran asistir a la siguiente actividad o no

#include <iostream>
#include <fstream>
#include <queue>

using pQueue = std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>>;

int64_t resolver(pQueue sumandos) {
    int64_t sum, a, b, coste = 0;

    while (sumandos.size() > 1) {
        a = sumandos.top(); sumandos.pop();
        b = sumandos.top(); sumandos.pop();

        sum = a + b;
        coste += sum;

        sumandos.push(sum);
    }
    return coste;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (N == 0)
        return false;

    int64_t v;
    pQueue sumandos;
    for (int i = 0; i < N; ++i) {
        std::cin >> v;
        sumandos.push(v);
    }

    // escribir sol
    int64_t sol = resolver(sumandos);
    std::cout << sol << '\n';

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