#pragma once

#include "AdjacencyList.h"

#include <unordered_map>

class SequentialGreedy {

private:
	typedef std::unordered_map<uint64_t, uint16_t> ColorMap;

	static uint16_t colorVertexGreedy(uint64_t vertex, std::vector<uint64_t> &neighbors, ColorMap &colors);

public:
	/**
	*	Color a graph using the sequential greedy algorithm.
	*
	*	@param adjacencyList the graph to color
	*	@param sortedVertices sorted set of the vertices in the graph
	*	@param ascending whether to iterate over the sorted vertices in an ascending order
	*	@return the number of colors used to color the graph
	*/
	static int color(AdjacencyList adjacencyList, std::set<Vertex> sortedVertices, bool ascending);

};