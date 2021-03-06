// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <queue>

struct Bateria {
    int id;
    int duracion;
    int capacidad;

    Bateria(int id, int duracion) : id(id), duracion(duracion), capacidad(duracion) {}
};

bool operator<(Bateria const& a, Bateria const& b) {
    return b.duracion < a.duracion || (b.duracion == a.duracion && b.id < a.id);
}

//using pQueue = std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>>;

void resolver(std::priority_queue<Bateria>& baterias, std::queue<Bateria> repuesto, int Z, int T) {
    int tActual = 0;

    while (!baterias.empty()) {
        Bateria b = baterias.top();
        tActual = b.duracion;
        b.capacidad -= Z;

        if (tActual > T) return;

        baterias.pop();
        if (b.capacidad <= 0) { //Se cambia
            if (!repuesto.empty()) {
                Bateria r = repuesto.front(); repuesto.pop();
                r.duracion += tActual;
                baterias.push(r);
            }
        }
        else { //Se carga
            b.duracion = tActual + b.capacidad;
            baterias.push(b);
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int B;
    std::cin >> B;

    if (!std::cin)
        return false;

    int t;
    std::priority_queue<Bateria> baterias;
    for (int i = 1; i <= B; ++i) {
        std::cin >> t;
        Bateria b(i, t);
        baterias.push(b);
    }

    int R, Z, T;
    std::cin >> R;
    std::queue<Bateria> repuesto;
    for (int i = 1; i <= R; ++i) {
        std::cin >> t;
        Bateria b(i+B, t);
        repuesto.push(b);
    }
    std::cin >> Z >> T;

    // escribir sol
    resolver(baterias, repuesto, Z, T);

    if (baterias.size() > 0) {
        if(baterias.size() == B) std::cout << "CORRECTO\n";
        else std::cout << "FALLO EN EL SISTEMA\n";

        while (!baterias.empty()) {
            std::cout << baterias.top().id << ' ' << baterias.top().duracion << '\n';
            baterias.pop();
        }
    }
    else {
        std::cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
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