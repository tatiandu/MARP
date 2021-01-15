
// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include "bintree_eda.h"
#include <climits>

int tree_height(const bintree<int>& tree)
{
	if (tree.empty())
		return 0;

	const auto lh = tree_height(tree.left());
	const auto rh = tree_height(tree.right());

	return std::max(lh, rh) + 1;
}

bool isBST(const bintree<int>& tree, int min, int max)
{
	if (tree.empty())
		return true;

	if (tree.root() < min || tree.root() > max)
		return 0;

	return isBST(tree.left(), min, tree.root()-1) &&
		isBST(tree.right(), tree.root()+1, max);
}

bool isAVL(const bintree<int>& tree)
{
	if (tree.empty()) //Si es vacío
		return true;

	bool valid = isBST(tree, INT_MIN, INT_MAX);
	if (!valid) return false;

	const auto difference = std::abs(tree_height(tree.left()) - tree_height(tree.right()));

	return (difference <= 1) &&
		isAVL(tree.left()) &&
		isAVL(tree.right());
}

void resuelveCaso()
{
	//leer datos
	auto tree = leerArbol(-1);

	//solucion
	if (isAVL(tree)) std::cout << "SI" << "\n";
	else std::cout << "NO" << "\n";

}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}