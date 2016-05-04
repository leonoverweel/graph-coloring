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
	SequentialGreedy(AdjacencyList &adjacencyList, std::set<Vertex> &sortedVertices);

	/**
	*	Color a graph using the sequential greedy algorithm.
	*
	*	@param ascending whether to iterate over the sorted vertices in an ascending order
	*	@return the number of colors used to color the graph
	*/
	int color(bool ascending) override;

};