
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <queue>

class ColaMedianas
{
	// top es mayor
	using MinQueue = std::priority_queue<int, std::vector<int>, std::less<int>>;
	// top es menor
	using MaxQueue = std::priority_queue<int, std::vector<int>, std::greater<int>>;

	MinQueue min;
	MaxQueue max;

public:
	void insertar(int x) {
		if (!max.empty() && x > max.top())
			max.push(x);
		else
			min.push(x);

		balancea();
	}

	bool vacia() const {
		return min.empty() && max.empty();
	}

	int mediana() const {
		if (min.size() >= max.size()) // Utilizamos el valor de la cola con más elementos
			return min.top();
		else
			return max.top();
	}

	void quitarMediana() {
		if (min.size() >= max.size()) // Utilizamos el valor de la cola con más elementos
			min.pop();
		else
			max.pop();
	}

private:
	void balancea() {
		auto diff = (int)max.size() - (int)min.size();

		if (diff > 1) { // max tiene al menos 2 elementos mas que min
			if (max.empty())
				return;

			min.push(max.top());
			max.pop();
		}
		else if (diff < -1) { // min tiene al menos 2 elementos mas que max
			if (min.empty())
				return;

			max.push(min.top());
			min.pop();
		}
	}
};

void resolver(const std::vector<int>& datos) noexcept
{
	ColaMedianas cola;
	for (auto n : datos) {
		if (n) { //Cliente nuevo
			cola.insertar(n);
		}
		else { //Atender cliente
			if (cola.vacia()) {
				std::cout << "ECSA ";
			}
			else {
				std::cout << cola.mediana() << ' ';
				cola.quitarMediana();
			}
		}
	}
	std::cout << '\n';
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
	int N;
	std::cin >> N;

	if (!std::cin)
		return false;

	std::vector<int> values(N);
	for (int i = 0; i < N; ++i) {
		std::cin >> values[i];
	}

	// escribir solucion
	resolver(values);
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