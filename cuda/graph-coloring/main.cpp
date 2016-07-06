#include "Graph.h"

#include <iostream>
#include <string>

int main() {

	// Graph location
	std::string base = "../../../graphs";
	std::string path = base + "tiny.graph";

	// Coloring parameters
	bool sortByDegree = true;
	bool sortAscending = false;
	bool verify = true;

	// Read file
	std::cout << "Reading file ... ";
	
	Graph graph = Graph(path, sortByDegree, sortAscending);

	std::cout << "done" << std::endl;

	Graph::VertexVector vertices = graph.getSortedVertices();
}
