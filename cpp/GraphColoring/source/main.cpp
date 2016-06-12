#include "../include/Graph.h"
#include "../include/LubyPlassman.h"
#include "../include/LubyJonesGreedy.h"
#include "../include/SequentialGreedy.h"

#include <iostream>
#include <string>
#include <chrono>
#include <omp.h>

#define SEQUENTIAL_GREEDY	0
#define LUBY_JONES_GREEDY	1
#define MIN_MAX_GREEDY		2
#define LUBY_PLASSMAN		3

#define FALSE				0
#define TRUE				1
#define ALL					0

int main() {

	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds ms;
	Clock::time_point start, finish;

	Colorer* colorer;
	uint16_t colors;
	
	// Graph location
	std::string base = "../../../../OneDrive/Documents/TU Delft/Research/Graphs/";
	std::string path = base + "Testing/arenas-jazz/out.arenas-jazz";

	// Coloring parameters
	bool sortByDegree = true;
	bool sortAscending = false;
	bool verify = true;
	uint16_t lubyJonesMISrandom = FALSE;
	uint16_t lubyJonesMISiterations = ALL;
	int algorithm = LUBY_PLASSMAN;
	omp_set_num_threads(4);

	// Read file
	std::cout << "Reading file ... ";
	start = Clock::now();
	
	Graph graph = Graph(path, sortByDegree, sortAscending);

	finish = Clock::now();
	std::cout << std::chrono::duration_cast<ms>(finish - start).count() / 1000.0 << " sec" << std::endl;

	Graph::VertexVector sortedVertices = graph.getSortedVertices();
	std::vector<uint16_t> params = std::vector<uint16_t>();
	
	// Color graph
	std::cout << "Coloring graph ... ";
	start = Clock::now();

	switch (algorithm)
	{

	case SEQUENTIAL_GREEDY:
		colorer = &SequentialGreedy(graph, sortedVertices);
		params.push_back(FALSE);
		colors = colorer->color(verify, params);
		break;

	case LUBY_JONES_GREEDY:
		colorer = &LubyJonesGreedy(graph, sortedVertices);
		params.push_back(FALSE);
		colors = colorer->color(verify, params);
		break;

	case MIN_MAX_GREEDY:
		colorer = &LubyJonesGreedy(graph, sortedVertices);
		params.push_back(TRUE);
		colors = colorer->color(verify, params);
		break;

	case LUBY_PLASSMAN:
		colorer = &LubyPlassman(graph, sortedVertices);
		params.push_back(lubyJonesMISrandom);
		params.push_back(lubyJonesMISiterations);
		colors = colorer->color(verify, params);
		break;

	}

	finish = Clock::now();
	std::cout << std::chrono::duration_cast<ms>(finish - start).count() / 1000.0 << " sec" << std::endl;

	// Output coloring results results
	std::cout << "\nColors: " << colors << std::endl;

	while (1) {}

}