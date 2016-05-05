#pragma once

#include "AdjacencyList.h"

#include <unordered_map>

class Colorer
{

protected:
	typedef std::unordered_map<uint64_t, uint16_t> ColorMap;

	AdjacencyList& adjacencyList;
	std::set<Vertex>& sortedVertices;

	/**
	*	Greedily find the lowest allowed color a vertex, by trying increasing colors until one is allowed.
	*
	*	@param neighborIds vector of the ids of the neighbors of the vertex to be colored
	*	@param colors unordered map from vertex ids to their color
	*	@return a color for the vertex
	*/
	uint16_t lowestAllowedColor(std::vector<uint64_t> &neighbors, ColorMap &colors);

	/**
	*	Constructor.
	*
	*	@param adjacencyList the adjacency list representing the graph to be colored
	*	@param sortedVertexIds a list of the vertex ids, sorted in the order in which they should be colored
	*/
	Colorer(AdjacencyList& adjacencyList, std::set<Vertex>& sortedVertexIds);

public:

	/**
	*	Color the graph. This method returns -1 unless it is overriden by a class that inherits from this class.
	*
	*	@param ascending whether the sorted list of vertex ids should be iterated in an ascending order
	*	@param miscParam parameter different algorithms can use to vary their behavior
	*/
	virtual int color(bool ascending, bool miscParam);

};