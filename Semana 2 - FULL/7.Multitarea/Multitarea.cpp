
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <queue>

struct Tarea {
    int64_t comienzo;
    int64_t fin;
    int periodo;

    Tarea(int comienzo, int fin, int periodo) : comienzo(comienzo), fin(fin), periodo(periodo) {}
};

bool operator<(Tarea const& a, Tarea const& b) {
    return b.comienzo < a.comienzo;
}

bool resolver(std::priority_queue<Tarea> tareas, int T) {
    int64_t ocupado = 0;

    while (!tareas.empty()) {
        Tarea t = tareas.top(); tareas.pop();

        if (ocupado > t.comienzo)
            return false; //hay conflicto

        ocupado = t.fin;
        if (ocupado >= T && tareas.top().comienzo >= T)
            return true;

        if (t.periodo != -1) { //si se repite
            t.comienzo += t.periodo;
            t.fin += t.periodo;

            tareas.push(t);
        }
    }
    return true;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M, T;
    std::cin >> N >> M >> T;

    if (!std::cin)
        return false;

    int ini, fin, periodo;
    std::priority_queue<Tarea> tareas;

    for (int i = 0; i < N; ++i) {
        std::cin >> ini >> fin;
        Tarea t = Tarea(ini, fin, -1);
        tareas.push(t);
    }
    for (int i = 0; i < M; ++i) {
        std::cin >> ini >> fin >> periodo;
        Tarea t = Tarea(ini, fin, periodo);
        tareas.push(t);
    }

    //escribir solucion
    if (resolver(tareas, T))
        std::cout << "NO" << '\n';
    else
        std::cout << "SI" << '\n';

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