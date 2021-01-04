// Grupo07
// Tatiana Duarte Balv�s
// Antonio Rom�n Cerezo

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h" // propios o los de las estructuras de datos de clase

/**
 * @brief Resuelve el caso recursivo, comprobamos con un caso base de que i y j
 * est�n dentro del rango de datos.
 * @param a El primer string.
 * @param b El segundo string.
 * @param i El �ndice actual del string a.
 * @param j El �ndice actual del string b.
 * @param datos Los datos de las soluciones que se van procesando.
 * @cost O(n ^ 2), siendo n el tama�o de la palabra m�s larga.
 */
int resolver_rec(const std::string& a, const std::string& b, int i, int j,
    Matriz<int>& datos)
{
    // i debe ser menor que el tama�o del primer string, as�mismo j debe serlo
    // para el segundo string.
    if (i >= a.size() || j >= b.size())
        return 0;

    // Lee por referencia la soluci�n actual en la matriz. Si es -1, el dato no
    // ha sido procesado, y por tanto, debemos llamar de forma recursiva para
    // asignar el nuevo dato.
    auto& res = datos[i][j];
    if (res == -1)
    {
        if (a[i] == b[j])
            res = resolver_rec(a, b, i + 1, j + 1, datos) + 1;
        else
            res = std::max(resolver_rec(a, b, i + 1, j, datos),
                resolver_rec(a, b, i, j + 1, datos));
    }

    // Devolvemos la soluci�n.
    return res;
}

/**
 * @brief Reconstruye un string dados los datos y la matriz de soluciones.
 * @param a El primer string.
 * @param b El segundo string.
 * @param datos Los datos de las soluciones ya procesadas por resolver_rec.
 * @param i El �ndice actual del string a.
 * @param j El �ndice actual del string b.
 * @param sol La soluci�n del problema, se pasa como referencia vol�til y se va
 * modificando en la funci�n.
 * @cost
 * - Coste computacional: O(n), siendo n el tama�o del string m�s largo.
 * - Coste espacial: O(n), siendo n el tama�o del string m�s peque�o.
*/
void reconstruir(const std::string& a, const std::string& b,
    const Matriz<int>& datos, int i, int j, std::string& sol)
{
    if (i >= a.size() || j >= b.size())
        return;

    if (a[i] == b[j]) {
        sol.push_back(a[i]);
        reconstruir(a, b, datos, i + 1, j + 1, sol);
    }
    else if (i < a.size() - 1 && datos[i][j] == datos[i + 1][j])
        reconstruir(a, b, datos, i + 1, j, sol);
    else
        reconstruir(a, b, datos, i, j + 1, sol);
}

// funci�n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
std::string resolver(const std::string& a, const std::string& b)
{
    Matriz<int> datos {(int)a.size(), (int)b.size(), -1 };
    int res = resolver_rec(a, b, 0, 0, datos);

    std::string sol = "";
    if(res != 0)
        reconstruir(a, b, datos, 0, 0, sol);

    return sol;
}

/**
 * @brief Resuelve un caso de prueba, leyendo de la entrada, y luego escribe la
 * respuesta.
 * @return Si se deben leer m�s datos.
 */
bool resuelveCaso()
{
    // Leer los datos de la entrada
    std::string a, b;
    std::cin >> a >> b;

    if (!std::cin) // Fin de la entrada
        return false;

    const auto sol = resolver(a, b);
    std::cout << sol << '\n';

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