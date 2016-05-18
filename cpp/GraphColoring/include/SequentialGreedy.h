#pragma once

#include "Colorer.h"

class SequentialGreedy: public Colorer {

private:

	/**
	*	Color a vertex with the lowest color allowed.
	*
	*	@param colors map from the vertex ids to their colors
	*	@param highest the highest color used so far
	*	@param vertexId the id of the vertex to color
	*/
	void colorVertex(ColorMap& colors, uint16_t& highest, uint64_t vertexId);

public:

	/**
	*	Constructor for a greedy Luby Jones graph colorer.
	*
	*	@param adjacencyList the graph to color
	*	@param sortedVertices sorted set of the vertices in the graph
	*/
	SequentialGreedy(Graph &graph, Graph::VertexVector &sortedVertices);

	/**
	*	Color a graph using the sequential greedy algorithm.
	*
	*	@param verify whether the coloring should be checked for correctness
	*	@param miscParam not used for sequential greedy
	*	@return the number of colors used to color the graph
	*/
	int color(bool verify, bool miscParam) override;

};