
// Tatiana Duarte Balvís

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

const int MAX = 10000; //para modulo
const int INF = 1000000000; //infinito

int adyacente(int v, int i) { //O(1)
    switch (i) {
        case 0:
            return (v + 1) % MAX; // + 1
        case 1:
            return (v * 2) % MAX; // * 2
        case 2:
            return v / 3; // / 3
    }
}

int bfs(int origen, int destino) //O(V+A)
{
    if (origen == destino) //si es el mismo num no hacemos nada
        return 0;

    std::vector<int> distancia(MAX, INF); //
    distancia[origen] = 0;
    std::queue<int> cola; //cola para recorrido en anchura
    cola.push(origen);

    while (!cola.empty())
    {
        int v = cola.front();
        cola.pop(); //sacamos de la cola el elemento que consultamos

        for (int i = 0; i < 3; ++i) //3 porque segun el problema hay tres aristas por vertice
        {
            int w = adyacente(v, i); //hacemos la operacion correspondiente
            if (distancia[w] == INF) //si no ha sido consultado
            {
                distancia[w] = distancia[v] + 1; //distancia siempre uno mas que la del vertice anterior
                if (w == destino) //si llegamos al resultado buscado
                    return distancia[w];
                else //si no, lo añadimos a la cola para seguir consultando
                    cola.push(w);
            }
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    //leer los datos de la entrada
    int origen, destino;
    std::cin >> origen >> destino;

    if (!std::cin) //fin de la entrada
        return false;

    //solucion
    std::cout << bfs(origen, destino) << "\n";
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