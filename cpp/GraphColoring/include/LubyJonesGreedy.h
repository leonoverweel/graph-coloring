#pragma once

#include "Colorer.h"

class LubyJonesGreedy : public Colorer {

public:

	/**
	*	Constructor for a greedy Luby Jones graph colorer.
	*
	*	@param graph the graph to color
	*	@param sortedVertices sorted set of the vertices in the graph
	*/
	LubyJonesGreedy(Graph &graph, Graph::VertexVector &sortedVertices);

	/**
	*	Color a graph using the Luby Jones greedy algorithm.
	*
	*	@param verify whether the coloring should be checked for correctness
	*	@param minMax whether the min-max variation of Luby Jones should be used
	*	@return the number of colors used to color the graph (or -1 if unsuccessful)
	*/
	int color(bool verify, bool minMax) override;

};