
// Tatiana Duarte Balvís

// Ordeno las actividade de menor a mayor según cuando comiencen
// Con una cola de int marco cuando quedará libre cada una de las personas
// Para saber si podran asistir a la siguiente actividad o no

#include <iostream>
#include <fstream>
#include <queue>

struct registro {
    int momento; // cuándo le toca
    int id; // identificador (se utiliza en caso de empate)
    int periodo; // tiempo entre consultas

    registro (int momento, int id, int periodo) :
        momento(momento), id(id), periodo(periodo) {}
};

bool operator<(registro const& a, registro const& b) {
    return b.momento < a.momento || (a.momento == b.momento && b.id < a.id);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!N)
        return false;

    int id, periodo;
    std::priority_queue<registro> cola;
    for (int i = 0; i < N; ++i) {
        std::cin >> id >> periodo;
        registro r = registro(periodo, id, periodo);
        cola.push(r);
    }

    int envios; // número de envíos a mostrar
    std::cin >> envios;

    //escribir sol
    while (envios--) {
        auto e = cola.top(); cola.pop();

        std::cout << e.id << '\n';

        e.momento += e.periodo;
        cola.push(e);
    }
    std::cout << "---\n";

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