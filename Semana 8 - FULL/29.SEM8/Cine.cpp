// Tatiana Duarte Balvís

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct Movie
{
	unsigned startTime;
	unsigned endTime;
	unsigned duration;

	Movie(unsigned start_time, unsigned duration) :
		startTime(start_time), endTime(start_time + duration), duration(duration)
	{}

	bool operator<(const Movie& m) const
	{
		return endTime > m.endTime;
	}
};

int resolver(const std::vector<Movie>& movies)
{
	std::priority_queue<Movie> q;
	for (const auto& f : movies) {
		q.push(f);
	}

	int count = 0;
	while (!q.empty())
	{
		const auto film = q.top(); q.pop();
		++count;
		while (!q.empty() && q.top().startTime < (film.endTime + 10)) {
			//eliminamos si empieza antes que nuestra pelicula
			q.pop();
		}
	}
	return count;
}
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	std::cin >> N;
	if (!N)
		return false;

	int duration, h, m;
	char _; //TODO

	std::vector<Movie> movies;
	movies.reserve(N);

	for (int i = 0; i < N; ++i) {
		std::cin >> h >> _ >> m >> duration;
		movies.emplace_back((h * 60 + m), duration); //horas a minutos
	}

	std::cout << resolver(movies) << '\n';
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
