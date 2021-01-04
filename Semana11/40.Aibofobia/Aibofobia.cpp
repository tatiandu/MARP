// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"

//Longitud del menor palindromo añadiendo letras a la palabra
int resolver_rec(std::string const& palabra, int i, int j, Matriz<int>& palindromo) { //Descendente O(n^2) ??
    int& res = palindromo[i][j];

    if (res == -1) {
        if (i > j) res = 0; //Caso base
        else if (i == j) res = 0; //Caso base

        else if (palabra[i] == palabra[j])
            res = resolver_rec(palabra, i + 1, j - 1, palindromo);
        else
            res = std::min(resolver_rec(palabra, i + 1, j, palindromo) + 1,
                resolver_rec(palabra, i, j - 1, palindromo) + 1);
    }
    return res;
}

//Construye el palindromo
void reconstruir(std::string const& palabra, Matriz<int> const& palindromo, int i, int j, std::string& sol) { //O(n)?
    if (i > j) return; //Caso base
    if (i == j) sol.push_back(palabra[i]); //Caso base

    else if (palabra[i] == palabra[j]) {
        sol.push_back(palabra[i]);
        reconstruir(palabra, palindromo, i + 1, j - 1, sol);
        sol.push_back(palabra[j]);
    }
    else if (palindromo[i][j] == palindromo[i + 1][j] + 1) {
        sol.push_back(palabra[i]);
        reconstruir(palabra, palindromo, i + 1, j, sol);
        sol.push_back(palabra[i]);
    }
    else {
        sol.push_back(palabra[j]);
        reconstruir(palabra, palindromo, i, j - 1, sol);
        sol.push_back(palabra[j]);
    }
}

//Resuelve un caso de prueba
bool resuelveCaso()
{
    // Leer los datos de la entrada
    std::string palabra;
    std::cin >> palabra;

    if (!std::cin) // Fin de la entrada
        return false;

    int n = palabra.length();
    Matriz<int> palindromo(n, n, -1);

    //Escribir solución
    int res = resolver_rec(palabra, 0, n - 1, palindromo);
    std::string sol;
    reconstruir(palabra, palindromo, 0, n - 1, sol);

    std::cout << res << ' ' << sol << '\n';

    return true;
}

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}