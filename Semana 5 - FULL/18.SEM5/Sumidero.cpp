
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include "Digrafo.h"

class Sumidero
{
public:
	Sumidero(Digrafo const& d) : sumidero(-1)
	{
		if (d.V() == 1) sumidero = 0; //Si solo hay un vertice este es el sumidero

		else {
			int a = 0, b = 1, next = 2;

			while (a < d.V() && b < d.V()) {
				if (d.hayArista(a, b)) { //A no es posible sumidero
					sumidero = b;
					a = b;
				}
				else { //B no es posible sumidero
					sumidero = a;
				}
				b = next;
				++next;
			}

			if (sumidero != -1) {
				if (d.ady(sumidero).size() == 0) {
					for (int i = 0; i < d.V(); ++i) {
						if (sumidero != i)
						{
							if (!d.hayArista(i, sumidero)) { //No es sumidero
								sumidero = -1;
								break;
							}
						}
					}
				}
				else sumidero = -1;
			}
		}
	}

	//Devuelve el nodo sumidero
	int tieneSumidero() const {
		return sumidero;
	}

private:
	int sumidero;
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int V, A;
	std::cin >> V >> A;

	if (!std::cin) //fin de entrada
		return false;

	Digrafo digrafo(V); //construye grafo
	int v, w;

	for (int i = 0; i < A; ++i) {
		std::cin >> v >> w;
		digrafo.ponArista(v, w);
	}

	Sumidero sumidero(digrafo);
	//escribir solucion
	int sol = sumidero.tieneSumidero();
	if (sol == -1)
		std::cout << "NO";
	else
		std::cout << "SI " << sol;

	std::cout << '\n';
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