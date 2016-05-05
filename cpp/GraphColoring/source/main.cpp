#include "../include/FileReader.h"

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
	std::string path = base + "Testing/reactome/out.reactome";

	// Coloring parameters
	bool sortByDegree = true;
	bool iterateAscending = false;
	int algorithm = MIN_MAX_GREEDY;

	// Read file
	std::cout << "Reading file ... ";
	start = Clock::now();
	
	AdjacencyList adjacencyList = FileReader::read(path);

	finish = Clock::now();
	std::cout << std::chrono::duration_cast<ms>(finish - start).count() / 1000.0 << " sec" << std::endl;

	// Sort vertices
	std::cout << "Sorting vertices ... ";
	start = Clock::now();

	std::set<Vertex> sortedVertices = adjacencyList.getSorted(sortByDegree);

	finish = Clock::now();
	std::cout << std::chrono::duration_cast<ms>(finish - start).count() / 1000.0 << " sec" << std::endl;

	// Color graph
	std::cout << "Coloring graph ... ";
	start = Clock::now();

	switch (algorithm)
	{

	case SEQUENTIAL_GREEDY:
		colorer = &SequentialGreedy(adjacencyList, sortedVertices);
		colors = colorer->color(iterateAscending, false);
		break;

	case LUBY_JONES_GREEDY:
		colorer = &LubyJonesGreedy(adjacencyList, sortedVertices);
		colors = colorer->color(iterateAscending, false);
		break;

	case MIN_MAX_GREEDY:
		colorer = &LubyJonesGreedy(adjacencyList, sortedVertices);
		colors = colorer->color(iterateAscending, true);
		break;

	}

	finish = Clock::now();
	std::cout << std::chrono::duration_cast<ms>(finish - start).count() / 1000.0 << " sec" << std::endl;

	// Output coloring results results
	std::cout << "\nColors: " << colors << std::endl;

	while (1) {}

}