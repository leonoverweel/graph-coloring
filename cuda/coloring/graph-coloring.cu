#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::vector<uint64_t>> readGraph (const std::string& path)
{
	std::vector<std::vector<uint64_t>> graph;

	// Open the file and make sure it exists
	std::ifstream remapStream;
	remapStream.open(path.c_str());

	if (!remapStream) return graph;

	// Remap the vertex ids
	std::vector<std::string> lines;
	std::string line;

	uint64_t a, b;
	uint64_t highestId = 0;

	std::unordered_map<uint64_t, uint64_t> vertexIdMap; // <original, remapped>
	
	while (std::getline(remapStream, line))
	{
		if (line[0] == '%') 
		{
			std::cout << "Skipped" << std::endl;
			continue;
		}

		std::istringstream string(line);
		string >> a >> b;
		
		auto search = vertexIdMap.find(a);
		if (search == vertexIdMap.end())
		{
			vertexIdMap.insert(std::make_pair(a, highestId++));
			std::cout << "Map " << a << " to " << highestId << std::endl;
		}
		
		search = vertexIdMap.find(b);
		if (search == vertexIdMap.end())
		{
			vertexIdMap.insert(std::make_pair(b, highestId++));
			std::cout << "Map " << b << " to " << highestId << std::endl;
		}
	}

	return graph;
}

int main (int argc, char *argv[])
{

	// Make sure a graph is passed
	if (argc != 2)
	{
		std::cout << "No graph provided!\n";
		return 1;
	}

	// Read the graph
	std::string path(argv[1]);
	std::vector<std::vector<uint64_t>> lines = readGraph(path);

	return 0;
}
