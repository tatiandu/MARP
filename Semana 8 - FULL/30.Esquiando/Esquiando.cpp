
//Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

int resolver(std::priority_queue<int> alturas, std::priority_queue<int> longitud) {
    int sum = 0; //victorias

    while (!alturas.empty() && !longitud.empty()) {
		sum += abs(alturas.top() - longitud.top());
		alturas.pop();
		longitud.pop();
    }
    return sum;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	// leer los datos de la entrada
	int N;
	std::cin >> N;
	if (!N)
		return false;

	int v;

	std::priority_queue<int> alturas;
	std::priority_queue<int> longitud;

    for (int i = 0; i < N; ++i) {
        std::cin >> v;
        alturas.push(v);
    }

    for (int i = 0; i < N; ++i) {
        std::cin >> v;
        longitud.push(v);
    }

    // escribir sol
    int sol = resolver(alturas, longitud);
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