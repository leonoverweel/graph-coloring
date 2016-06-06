#pragma once

#include "Colorer.h"

class LubyJones : public Colorer {

public:

	/**
	*	Constructor for a greedy Luby Jones graph colorer.
	*
	*	@param graph the graph to color
	*	@param sortedVertices sorted set of the vertices in the graph
	*/
	LubyJones(Graph &graph, Graph::VertexVector &sortedVertices);

	/**
	*	Color a graph using the Luby Jones greedy algorithm.
	*
	*	@param verify whether the coloring should be checked for correctness
	*	@param minMax whether the min-max variation of Luby Jones should be used
	*		at(0): whether to use sequential (0) or random (1) numbers
	*		at(1): number of MIS iterations to use (0 is until done, n > 0 is n iterations)
	*	@return the number of colors used to color the graph (or -1 if unsuccessful)
	*/
	int color(bool verify, std::vector<uint16_t> params) override;

};