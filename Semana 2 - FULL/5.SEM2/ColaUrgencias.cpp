
// Tatiana Duarte Balvís

// Ordeno las actividade de menor a mayor según cuando comiencen
// Con una cola de int marco cuando quedará libre cada una de las personas
// Para saber si podran asistir a la siguiente actividad o no

#include <iostream>
#include <fstream>
#include <queue>

class ColaUrgencias {
private:
    struct Paciente {
        int id;
        std::string nombre;
        int gravedad;

        Paciente(int id, std::string nombre, int gravedad) :
            id(id), nombre(nombre), gravedad(gravedad) {}

        bool operator<(const Paciente& rhs) const
        {
            return rhs.gravedad > gravedad || (gravedad == rhs.gravedad && rhs.id < id);
        }
    };

    std::priority_queue<Paciente> pacientes;
    int time = 0;

public:
    ColaUrgencias() {};

    void ingresarPaciente(std::string nombre, int gravedad) {
        Paciente p = Paciente(++time, nombre, gravedad);
        pacientes.push(p);
    }

    std::string nombrePrimero() const {
        return pacientes.top().nombre;
    }

    void atenderPaciente() {
        pacientes.pop();
    }
};

void resolver(ColaUrgencias& pacientes) {
    char c;
    std::cin >> c;

    if (c == 'I') {
        std::string nombre;
        int gravedad;
        std::cin >> nombre >> gravedad;

        pacientes.ingresarPaciente(nombre, gravedad);
    }
    else {
        std::cout << pacientes.nombrePrimero() << '\n';
        pacientes.atenderPaciente();
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!N)
        return false;

    ColaUrgencias cola;
    for (int i = 0; i < N; ++i) {
        resolver(cola);
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