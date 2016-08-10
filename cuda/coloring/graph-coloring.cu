#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

bool verbose = true;

std::vector<std::vector<uint64_t>> readGraph (const std::string& path)
{
	// Open the file and make sure it exists
	std::ifstream remapStream;
	remapStream.open(path.c_str());

	// Remap the vertex ids
	if (verbose) std::cout << "\tRemapping vertex IDs...\n";

	std::vector<std::string> lines;
	std::string line;

	uint64_t a, b;
	uint64_t highestId = 0;

	std::unordered_map<uint64_t, uint64_t> vertexIdMap; // <original, remapped>
	
	while (std::getline(remapStream, line))
	{
		if (line[0] == '%') 
		{
			if (verbose) std::cout << "\t\tSkip" << std::endl;
			continue;
		}

		std::istringstream string(line);
		string >> a >> b;
		
		auto search = vertexIdMap.find(a);
		if (search == vertexIdMap.end())
		{
			vertexIdMap.insert(std::make_pair(a, highestId++));
			if (verbose) std::cout << "\t\tMap " << a << " to " << highestId << std::endl;
		}
		
		search = vertexIdMap.find(b);
		if (search == vertexIdMap.end())
		{
			vertexIdMap.insert(std::make_pair(b, highestId++));
			if (verbose) std::cout << "\t\tMap " << b << " to " << highestId << std::endl;
		}
	}

	if (verbose) std::cout << "\tDone\n";

	// Create adjacency list
	if (verbose) std::cout << "\tCreating adjacency list...\n";

	std::vector<std::vector<uint64_t>> graph(vertexIdMap.size());
	
	std::ifstream neighborStream;
	neighborStream.open(path.c_str());

	while (std::getline(neighborStream, line))
	{
		if (line[0] == '%')
		{
			if (verbose) std::cout << "\t\tSkip\n";
			continue;
		}

		std::istringstream string(line);
		string >> a >> b;

		if (a != b)
		{
			uint64_t remappedA = vertexIdMap.find(a)->second;
			uint64_t remappedB = vertexIdMap.find(b)->second;

			graph.at(remappedA).push_back(remappedB);
			graph.at(remappedB).push_back(remappedA);

			if (verbose) std::cout << "\t\tAdd edge between "
				<< "vertex " << remappedA << " (originally " << a << ") and "
				<< "vertex " << remappedB << " (originally " << b << ")\n";
		}
	}

	if (verbose) std::cout << "\tDone\n";

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
	if (verbose) std::cout << "Reading graph...\n";
	std::string path(argv[1]);
	std::vector<std::vector<uint64_t>> lines = readGraph(path);
	if (verbose) std::cout << "Done\n";

	return 0;
}
