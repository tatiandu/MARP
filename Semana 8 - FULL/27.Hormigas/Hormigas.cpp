
//Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

int resolver(std::vector<int> datos, int len) { //datos ya ordenador de menor a mayor
    int count = 0;

    int i = 0;
    while (i < datos.size() ) {
        int dato = datos[i];
        ++count;
        while (i+1 < datos.size()) { 
            if (datos[i + 1] > dato + len) { //Si no se pueden tapar ambos
                break;
            }
            ++i;
        }
        ++i;
    }
    return count;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, L;
    // leer los datos de la entrada
    std::cin >> N >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    int v;
    std::vector<int> buratos;
    buratos.reserve(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> v;
        buratos.push_back(v);
    }

    // escribir sol
    int sol = resolver(buratos, L);
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