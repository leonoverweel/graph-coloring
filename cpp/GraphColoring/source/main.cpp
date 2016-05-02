#include "../include/AdjacencyList.h"
#include "../include/FileReader.h"
#include "../include/SequentialGreedy.h"

#include <iostream>
#include <string>
#include <chrono>

int main() {

	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds ms;
	Clock::time_point start, finish;
	
	std::string base = "../../../../OneDrive/Documents/TU Delft/Research/Graphs/";
	std::string path = base + "Testing/arenas-jazz/out.arenas-jazz";

	bool sortByDegree = true;
	bool iterateAscending = false;

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

	uint16_t colors = SequentialGreedy::color(adjacencyList, sortedVertices, iterateAscending);

	finish = Clock::now();
	std::cout << std::chrono::duration_cast<ms>(finish - start).count() / 1000.0 << " sec" << std::endl << std::endl;

	std::cout << "Colors: " << colors << std::endl;

	while (1) {}

}