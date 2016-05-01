#include "../include/FileReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Read an out.* file and return the graph it represents.
AdjacencyList FileReader::read(std::string filepath)
{
	AdjacencyList adjacencyList = AdjacencyList();

	std::ifstream infile(filepath);
	std::string line;
	int64_t a, b;

	while (std::getline(infile, line))
	{
		if (line[0] == '%') continue;

		std::istringstream string(line);
		string >> a >> b;

		adjacencyList.addEdge(a, b);
	}

	return adjacencyList;
}
