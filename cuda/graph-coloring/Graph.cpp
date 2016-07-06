#include "Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <map>

// Constructor.
Graph::Graph(std::string filepath, bool sortByDegree, bool sortAscending)
{

	// Remap all vertices to new sequential ids.

	std::unordered_map<Vertex, Vertex> vertexIdRemap;
	
	Vertex a, b;
	Vertex maxId = 0;
	std::string line;

	std::ifstream remapStream(filepath);
	while (std::getline(remapStream, line))
	{
		if (line[0] == '%') continue;

		std::istringstream string(line);
		string >> a >> b;

		auto search = vertexIdRemap.find(a);
		if (search == vertexIdRemap.end())
			vertexIdRemap.insert(std::make_pair(a, maxId++));

		search = vertexIdRemap.find(b);
		if (search == vertexIdRemap.end())
			vertexIdRemap.insert(std::make_pair(b, maxId++));
	}

	// Initialize adjacency list.

	adjacencyList = AdjacencyList();

	for (int i = 0; i < vertexIdRemap.size(); i++)
		adjacencyList.push_back(std::make_pair(0, VertexVector()));

	// Add neighbors to adjacency list.

	std::ifstream neighborsStream(filepath);
	while (std::getline(neighborsStream, line))
	{
		if (line[0] == '%') continue;

		std::istringstream string(line);
		string >> a >> b;

		if (a != b)
		{
			Vertex aRemapped = vertexIdRemap.find(a)->second;
			Vertex bRemapped = vertexIdRemap.find(b)->second;

			adjacencyList.at(aRemapped).second.push_back(bRemapped);
			adjacencyList.at(bRemapped).second.push_back(aRemapped);
		}		
	}

	// Sort neighbors and remove duplicates.

	for (auto &vertex : adjacencyList)
	{
		std::set<Vertex> set(vertex.second.begin(), vertex.second.end());
		vertex.second.assign(set.begin(), set.end());
	}

	// Sort vertices into set (by id or by degree).

	std::map<double, Vertex> sortedVertexMap;

	for (int i = 0; i < adjacencyList.size(); i++)
	{
		if (sortByDegree)
		{
			double key = adjacencyList.at(i).second.size() + (double)i / (double)adjacencyList.size();
			sortedVertexMap.insert(std::make_pair(key, i));
		}
		else
			sortedVertexMap.insert(std::make_pair(i, i));
	}

	// Instantiate and fill the sortedVertices variable (ascending or descending).

	sortedVertices = VertexVector();

	if (sortAscending)
		for (auto it = sortedVertexMap.begin(); it != sortedVertexMap.end(); ++it)
			sortedVertices.push_back(it->second);
	else
		for (auto it = sortedVertexMap.rbegin(); it != sortedVertexMap.rend(); ++it)
			sortedVertices.push_back(it->second);

}

// Get the color of the vertex with the specified id.
Graph::Color Graph::getColor(Vertex vertex)
{
	return adjacencyList.at(vertex).first;
}

void Graph::setColor(Vertex vertex, Color color)
{
	adjacencyList.at(vertex).first = color;
}

// Get the ids of a vertex's neighbors.
Graph::VertexVector Graph::getNeighbors(Vertex vertex)
{
	return adjacencyList.at(vertex).second;
}

// Get the sorted set of vertex ids, to iterate over.
Graph::VertexVector Graph::getSortedVertices()
{
	return sortedVertices;
}

// Get the adjacency list
Graph::AdjacencyList Graph::getAdjacencyList()
{
	return adjacencyList;
}
