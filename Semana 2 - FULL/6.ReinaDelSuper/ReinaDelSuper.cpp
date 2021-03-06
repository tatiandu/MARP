
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <queue>

struct Caja {
    int id;
    int tiempo;

    Caja(int id, int tiempo) : id(id), tiempo(tiempo) {}
};

bool operator<(Caja const& a, Caja const& b) {
    return b.tiempo < a.tiempo || (a.tiempo == b.tiempo && b.id < a.id);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C;
    std::cin >> N >> C;

    if (!N && !C)
        return false;

    int c;
    std::priority_queue<Caja> cola;

    for (int i = 0; i < N; ++i) {
        Caja caja = Caja(i + 1, 0);
        cola.push(caja);
    }
    for (int i = 0; i < C; ++i) {
        std::cin >> c; //cliente
        Caja caja = cola.top(); cola.pop();
        caja.tiempo += c;

        cola.push(caja);
    }

    //escribir solucion
    int sol = cola.top().id;
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