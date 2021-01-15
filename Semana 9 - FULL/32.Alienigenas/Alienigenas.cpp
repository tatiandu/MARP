
//Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

struct Trabajo {
	int ini;
	int fin;

	Trabajo(int ini, int fin) : ini(ini), fin(fin) {}
};

using pQueue = std::priority_queue<Trabajo, std::vector<Trabajo>, std::less<Trabajo>>;

bool operator<(Trabajo const& a, Trabajo const& b) { //Para priority queue
	return b.ini < a.ini;
}

int resolver(pQueue trabajos, int C, int F) {
	int nTrabajos = 0;
	bool posible = true;

	while (!trabajos.empty() && posible && C < F) {
		int max = -1; //Lo que llevamos abarcado por intervalo

		while (!trabajos.empty() && trabajos.top().ini <= C) {
			if (trabajos.top().fin > C && trabajos.top().fin > max) {
				max = trabajos.top().fin;
			}
			trabajos.pop();
		}

		if (max == -1) posible = false;
		else {
			++nTrabajos;
			C = max;
		}
	}

	if (posible && C >= F) return nTrabajos;
	else return -1;
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	// leer los datos de la entrada
	int C, F, N;
	std::cin >> C >> F >> N;
	if (!C && !F && !N)
		return false;

	int ini, fin;

	pQueue trabajos;

	for (int i = 0; i < N; ++i) {
		std::cin >> ini >> fin;
		Trabajo t = Trabajo(ini, fin);
		trabajos.push(t);
	}

	// escribir sol
	int sol = resolver(trabajos, C, F);

	if (sol == -1) std::cout << "Imposible" << "\n";
	else std::cout << sol << "\n";

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