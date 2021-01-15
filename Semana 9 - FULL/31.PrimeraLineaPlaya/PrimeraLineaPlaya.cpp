
//Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

struct Hotel {
	int izq;
	int der;
	int longitud;

	Hotel(int izq, int der) : izq(izq), der(der) {
		longitud = der - izq;
	}
};

using pQueue = std::priority_queue<Hotel, std::vector<Hotel>, std::less<Hotel>>;

bool operator<(Hotel const& a, Hotel const& b) { //Para priority queue
	return b.der < a.der;
}

int resolver(pQueue hoteles) {
	int cont = 0; //tuneles

	while (!hoteles.empty()) {
		Hotel h = hoteles.top(); hoteles.pop();
		++cont;

		while (!hoteles.empty() && hoteles.top().izq < (h.izq + h.longitud)) {
			//eliminamos si pueden compartir tunel
			hoteles.pop();
		}
	}
	return cont;
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

	int izq, der;

	//std::priority_queue<Hotel> hoteles;
	pQueue hoteles;

	for (int i = 0; i < N; ++i) {
		std::cin >> izq >> der;
		Hotel h = Hotel(izq, der);
		hoteles.push(h);
	}

	// escribir sol
	int sol = resolver(hoteles);
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