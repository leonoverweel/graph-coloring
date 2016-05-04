#pragma once

#include "Coloring.h"

class LubyJonesGreedy : public Coloring {

public:

	/**
	*	Color a graph using the Luby Jones greedy algorithm.
	*
	*	@param adjacencyList the graph to color
	*	@param sortedVertices sorted set of the vertices in the graph
	*	@param ascending whether to iterate over the sorted vertices in an ascending order
	*	@return the number of colors used to color the graph
	*/
	static int color(AdjacencyList &adjacencyList, std::set<Vertex> &sortedVertices, bool ascending);

};