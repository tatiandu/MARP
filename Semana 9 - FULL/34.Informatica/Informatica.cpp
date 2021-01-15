
// Tatiana Duarte Balvís

// Ordeno las actividade de menor a mayor según cuando comiencen
// Con una cola de int marco cuando quedará libre cada una de las personas
// Para saber si podran asistir a la siguiente actividad o no

#include <iostream>
#include <fstream>
#include <queue>

struct Actividad {
    int ini;
    int fin;

    Actividad(int ini, int fin) : ini(ini), fin(fin) {}
};

using pQueue = std::priority_queue<Actividad, std::vector<Actividad>, std::less<Actividad>>;

bool operator<(Actividad const& a, Actividad const& b) {
    return a.ini > b.ini;
}

//O(n logn)
int resolver(pQueue actividades) {
    int cont = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> libre; //Cuando estará libre la persona i
    bool nuevaPersona = true;

    Actividad a = actividades.top();

    while (!actividades.empty()) {
        actividades.pop();

        if (nuevaPersona) {
            ++cont;
            libre.push(a.fin);
        }
        if (actividades.empty()) {
            break;
        }

        //Si el que acaba antes no vale, necesitamos una persona más
        if (actividades.top().ini < libre.top()) {
            nuevaPersona = true;
        }
        else {
            int x = libre.top();
            libre.pop();
            x = actividades.top().fin;
            libre.push(x);
            nuevaPersona = false;
        }
        //Siguiente actividad
        a = actividades.top();
    }
    return cont;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!N)
        return false;

    int ini, fin;
    pQueue actividades;
    for (int i = 0; i < N; ++i) {
        std::cin >> ini >> fin;
        Actividad a = Actividad(ini, fin);
        actividades.push(a);
    }

    // escribir sol
    int sol = resolver(actividades);
    std::cout << sol - 1 << "\n";

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