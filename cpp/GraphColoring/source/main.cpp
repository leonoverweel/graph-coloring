#include "../include/Graph.h"
#include "../include/LubyJonesGreedy.h"
#include "../include/SequentialGreedy.h"

#include <iostream>
#include <string>
#include <chrono>

#define SEQUENTIAL_GREEDY	0
#define LUBY_JONES_GREEDY	1
#define MIN_MAX_GREEDY		2

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
	int algorithm = LUBY_JONES_GREEDY;

	// Read file
	std::cout << "Reading file ... ";
	start = Clock::now();
	
	Graph graph = Graph(path, sortByDegree, sortAscending);

	finish = Clock::now();
	std::cout << std::chrono::duration_cast<ms>(finish - start).count() / 1000.0 << " sec" << std::endl;

	Graph::VertexVector sortedVertices = graph.getSortedVertices();
	
	// Color graph
	std::cout << "Coloring graph ... ";
	start = Clock::now();

	switch (algorithm)
	{

	case SEQUENTIAL_GREEDY:
		colorer = &SequentialGreedy(graph, sortedVertices);
		colors = colorer->color(verify, false);
		break;

	case LUBY_JONES_GREEDY:
		colorer = &LubyJonesGreedy(graph, sortedVertices);
		colors = colorer->color(verify, false);
		break;

	case MIN_MAX_GREEDY:
		colorer = &LubyJonesGreedy(graph, sortedVertices);
		colors = colorer->color(verify, true);
		break;

	}

	finish = Clock::now();
	std::cout << std::chrono::duration_cast<ms>(finish - start).count() / 1000.0 << " sec" << std::endl;

	// Output coloring results results
	std::cout << "\nColors: " << colors << std::endl;

	while (1) {}

}