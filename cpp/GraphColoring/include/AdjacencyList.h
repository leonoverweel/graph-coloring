#pragma once

#include "Vertex.h"

#include <set>
#include <unordered_map>
#include <unordered_set>

class AdjacencyList
{

private:

	std::unordered_map<uint64_t, std::unordered_set<uint64_t>> adjacencyList;
	std::set<Vertex> orderedVertices;
	bool sorted, byDegree;

	std::set<Vertex> sort(bool byDegree);
	void addDirectedEdge(uint64_t a, uint64_t b);

public:

	/**
	*	Constructs an adjacency list.
	*/
	AdjacencyList();

	/**
	*	Add an edge between vectors a and b.
	*
	*	@param a id of vertex a
	*	@param b id of vertex b
	*/
	void addEdge(uint64_t a, uint64_t b);

	/**
	*	Get the pointers to a vertex's neighbors.
	*
	*	@param vertexId id of the vertex whose neighbors to get
	*	@return the ids of vertex's neighbors
	*/
	std::unordered_set<uint64_t> getNeighbors(uint64_t vertexId);

	/**
	*	Get a sorted set of all vertex ids. If not already sorted appropriately, sort first.
	*
	*	@param byDegree whether to sort by degree; if not, sorts by vertex id
	*/
	std::set<Vertex> getSorted(bool byDegree);

};