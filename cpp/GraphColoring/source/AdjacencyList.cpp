#include "../include/AdjacencyList.h"

#include <unordered_map>

// Constructor.
AdjacencyList::AdjacencyList()
{
	adjacencyList = std::unordered_map<uint64_t, std::vector<uint64_t>>();
	sorted = false;
}

// Add an edge from a to b and from b to a.
void AdjacencyList::addEdge(uint64_t a, uint64_t b)
{
	sorted = false;
	addDirectedEdge(a, b);
	addDirectedEdge(b, a);
}

// Get a vertex's neighbors.
std::vector<uint64_t> AdjacencyList::getNeighbors(uint64_t vertexId)
{
	auto search = adjacencyList.find(vertexId);

	if (search == adjacencyList.end()) {
		return std::vector<uint64_t>();
	}
			
	return search->second;
}

// Get the sorted vertices.
std::set<Vertex> AdjacencyList::getSorted(bool byDegree)
{
	if (!sorted || this->byDegree != byDegree) 
		sort(byDegree);
	return orderedVertices;
}

// Add a directed adge from a to b.
void AdjacencyList::addDirectedEdge(uint64_t a, uint64_t b)
{
	auto search = adjacencyList.find(a);
	std::vector<uint64_t> neighbors;

	if (search == adjacencyList.end())
	{
		neighbors = std::vector<uint64_t>();
		neighbors.push_back(b);
		adjacencyList.insert(std::make_pair(a, neighbors));
	}

	else
	{
		neighbors = search->second;
		neighbors.push_back(b);
		adjacencyList[a] = neighbors;
	}

}

// Sort the vertices
std::set<Vertex> AdjacencyList::sort(bool byDegree) {
	orderedVertices = std::set<Vertex>();

	for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
	{
		Vertex vertex = {
			it->first,
			it->second.size(),
			byDegree
		};

		orderedVertices.insert(vertex);
	}

	this->byDegree = byDegree;
	this->sorted = true;

	return orderedVertices;
}