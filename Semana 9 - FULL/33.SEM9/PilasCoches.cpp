#include <iostream>
#include <fstream>
#include <list>

/**
 * @brief Ordenamos los datos de menor a mayor voltaje, y luego cogemos la pila
 * más grande y buscamos la pila más pequeña cuya suma de voltaje que cumpla la
 * condición bV + mV >= minV (siendo bV la pila más grande y mV la pila más
 * pequeña).
 *
 * @cost
 * - Coste computacional: O(n^2), n = datos.size().
 * - Coste espacial: O(1), no reservamos espacio en el heap y el coste en el
 *                   stack es trivial.
 * @return La cantidad de parejas de pilas que se pueden utilizar.
 */
int resolver(std::list<int>&& datos, int minV)
{
    int count = 0;
    // Ordenamos todos los datos de menor a mayor (coste O(n * log n), siendo n
    // el número de elementos).
    datos.sort();
    // Necesitamos al menos 2 pilas para hacer una pareja :)
    while (datos.size() >= 2)
    {
        auto max = datos.back(); datos.pop_back();
        for (auto it = datos.begin(); it != datos.end(); )
        {
            if (max + *it >= minV)
            {
                datos.erase(it);
                ++count;
                break;
            }
            else it = datos.erase(it);
        }
    }
    return count;
}

/**
 * @brief Resuelve un caso de prueba.
 */
void resuelveCaso()
{
    // leer los datos de la entrada
    int N, V, v;
    std::cin >> N >> V;
    std::list<int> batteries;

    for (int i = 0; i < N; ++i)
    {
        std::cin >> v;
        batteries.push_back(v);
    }

    std::cout << resolver(std::move(batteries), V) << '\n';
}

int main()
{
    //ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
    {
        resuelveCaso();
    }
    //para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}