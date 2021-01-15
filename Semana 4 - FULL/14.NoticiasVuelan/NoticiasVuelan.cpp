
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include "Grafo.h"

int dfs(Grafo const& g, int v, std::vector<bool>& visit, std::vector<int>& dfsIndex) { //resolver
	visit[v] = true;
	int tam = 1;

	for (int w : g.ady(v)) {
		if (!visit[w]) {
			dfsIndex.push_back(w);
			tam += dfs(g, w, visit, dfsIndex);
		}
	}
	return tam;
}

std::vector<int> resolver(Grafo const& g) {
	std::vector<bool> visit(g.V(), false);
	std::vector<int> tamDFS(g.V(), 0);

	for (int i = 0; i < g.V(); ++i) {
		if (!visit[i]) { //Solo hacemos dfs de los no visitados
			std::vector<int> dfsIndex;
			int tam = dfs(g, i, visit, dfsIndex);
			tamDFS[i] = tam;

			for (int j = 0; j < dfsIndex.size(); ++j) { //Marcamos tamaños
				tamDFS[dfsIndex[j]] = tam;
			}
		}
	}
	return tamDFS;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int V, G;
	std::cin >> V >> G;

	if (!std::cin) //fin de entrada
		return false;

	Grafo grafo(V); //construye grafo
	int g, v, w;

	for (int i = 0; i < G; ++i) {
		std::cin >> g;

		if (g >= 1) {
			std::cin >> v; //La primera persona del grupo los une a todos para simplificar

			for (int j = 1; j < g; ++j) {
				std::cin >> w;
				grafo.ponArista(v - 1, w - 1);
			}
		}
	}

	//escribir solucion
	const std::vector<int>& sol = resolver(grafo);
	for (int i = 0; i < sol.size(); ++i) {
		std::cout << sol[i] << ' ';
	}
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