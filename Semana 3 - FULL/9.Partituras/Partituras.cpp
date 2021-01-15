
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <queue>

struct Instrumento {
	int n;
	int partituras;

	Instrumento(int n, int p = 1) : n(n), partituras(p) {}
};

struct prioridad {
	bool operator()(Instrumento const& a, Instrumento const& b) {
		int ib = b.n / b.partituras;
		int ia = a.n / a.partituras;

		return ib > ia || (ib == ia && b.n % b.partituras > a.n % a.partituras);
	}
};

using pQueue = std::priority_queue<Instrumento, std::vector<Instrumento>, prioridad>;

Instrumento resolver(pQueue& cola, int P)
{
	while (P > 0) {
		Instrumento inst = cola.top(); cola.pop();
		if (inst.n == inst.partituras)
			return inst;

		++inst.partituras;
		cola.push(inst);

		--P;
	}
	return cola.top();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int P, N;
	std::cin >> P >> N;

	if (!std::cin)
		return false;

	int n;
	pQueue cola;
	for (int i = 0; i < N; ++i) {
		std::cin >> n;
		Instrumento inst = Instrumento(n);
		cola.push(inst);
	}

	if (cola.empty()) {
		std::cout << "0\n";
		return true;
	}

	// escribir solucion
	P -= N; //Menos N porque los grupos de instrumentos ya tienen una partitura
	Instrumento sol = resolver(cola, P);
	if(sol.n % sol.partituras == 0)
		std::cout << sol.n/sol.partituras << '\n';
	else
		std::cout << sol.n/sol.partituras +1 << '\n';

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