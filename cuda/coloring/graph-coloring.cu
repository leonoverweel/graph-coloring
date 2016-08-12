#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>

bool verbose = true;

// Read a graph from a file
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
			vertexIdMap.insert(std::make_pair(a, highestId));
			if (verbose) std::cout << "\t\tMap " << a << " to " << highestId << std::endl;
			highestId++;
		}
		
		search = vertexIdMap.find(b);
		if (search == vertexIdMap.end())
		{
			vertexIdMap.insert(std::make_pair(b, highestId));
			if (verbose) std::cout << "\t\tMap " << b << " to " << highestId << std::endl;
			highestId++;
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

	// Sort neighbor lists and remove duplicates
	if (verbose) std::cout << "\tSorting neighbor lists and removing duplicates... ";

	for (int i = 0; i < graph.size(); i++)
	{
		std::vector<uint64_t> * neighborList = &graph[i];
		std::set<uint64_t> set(neighborList->begin(), neighborList->end());
		neighborList->assign(set.begin(), set.end());	
	}

	if (verbose) std::cout << "Done\n";

	// Print the final adjacency list
	if (verbose)
	{
		std::cout << "\tFinal adjacency list:\n";
		for(int i = 0; i < graph.size(); i++)
		{
			std::cout << "\t\t" << i << ": ";
			for(uint64_t neighbor : graph.at(i))
			{
				std::cout << neighbor << ", ";
			}
			std::cout << "\b\b \n";
		}
	}

	return graph;
}

// Flatten a graph into a single data vector with pointers to where each vertex's neighbor list starts and ends. Returns size in bytes.
int flatten (std::vector<std::vector<uint64_t>> * graph, std::vector<uint64_t> * data, std::vector<uint64_t> * indices)
{
	indices->push_back(0);

	for (int i = 0; i < graph->size(); i++)
	{
		data->insert(data->end(), (*graph)[i].begin(), (*graph)[i].end());
		indices->push_back(data->size());
	}

	if (verbose) std::cout << "\tLength of data: " << data->size() << std::endl;
	if (verbose) std::cout << "\tSize in bytes: " << data->size() * sizeof(uint64_t) << std::endl;

	if (verbose)
	{
		std::cout << "\tAdjacency list from flattened data:\n";
		for(int i = 0; i < indices->size() - 1; i++)
		{
			std::cout << "\t\t" << i << ": ";
			for(uint64_t j = (*indices)[i]; j < (*indices)[i+1]; j++) 
		{
				std::cout << (*data)[j] << ", ";
			}
			std::cout << "\b\b \n";
		}
	}

	return data->size() * sizeof(uint64_t);
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
	std::vector<std::vector<uint64_t>> graph = readGraph(path);

	if (verbose) std::cout << "Done\n";
	
	// Generate the random numbers
	if (verbose) std::cout << "Generating random numbers...\n";

	std::random_device rnd_device;
	std::mt19937 mersenne_engine(rnd_device());
	std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
	auto gen = std::bind(dist, mersenne_engine);

	std::vector<int> * random = new std::vector<int>(graph.size());
	int randomSize = random->size() * sizeof(int);

	if (verbose) std::cout << "\tSize: " << randomSize << std::endl;

	std::generate(random->begin(), random->end(), gen);

	if (verbose)
	{
		for (int i = 0; i < graph.size(); i++)
		{
			std::cout << "\t" << i << ": " << random->at(i) << std::endl;
		}
	}

	if (verbose) std::cout << "Done\n";

	// Flatten the graph
	if (verbose) std::cout << "Flattening the graph...\n";
	
	std::vector<uint64_t> * data = new std::vector<uint64_t>();
	std::vector<uint64_t> * indices = new std::vector<uint64_t>();

	int dataSize = flatten(&graph, data, indices);
	int indicesSize = indices->size() * sizeof(uint64_t);

	if (verbose) std::cout << "Done\n";

	// Send data to device
	if (verbose) std::cout << "Sending graph to device...";
	
	uint64_t * deviceDataPointer;
	uint64_t * deviceIndicesPointer;
	uint64_t * deviceRandomPointer;

	cudaMalloc((void**)&deviceDataPointer, dataSize);
	cudaMalloc((void**)&deviceIndicesPointer, indicesSize);
	cudaMalloc((void**)&deviceRandomPointer, randomSize);

	cudaMemcpy(deviceDataPointer, data, dataSize, cudaMemcpyHostToDevice);
	cudaMemcpy(deviceIndicesPointer, indices, indicesSize, cudaMemcpyHostToDevice);
	cudaMemcpy(deviceRandomPointer, random, randomSize, cudaMemcpyHostToDevice);

	if (verbose) std::cout << "Done\n";

	return 0;
}
