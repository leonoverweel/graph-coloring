#pragma once

#include "Graph.h"

#include <unordered_map>

class Colorer
{

public:

	/**
	*	Color the graph. This method returns -1 unless it is overriden by a class that inherits from this class.
	*
	*	@param verify whether the coloring should be checked for correctness
	*	@param miscParam parameter different algorithms can use to vary their behavior
	*	@return the number of colors used to color the graph
	*/
	virtual int color(bool verify, bool miscParam);

protected:
	typedef std::unordered_map<Graph::Vertex, Graph::Color> ColorMap;

	Graph& graph;
	Graph::VertexVector& sortedVertices;

	/**
	*	Constructor.
	*
	*	@param adjacencyList the adjacency list representing the graph to be colored
	*	@param sortedVertices a list of the vertex ids, sorted in the order in which they should be colored
	*/
	Colorer(Graph &graph, Graph::VertexVector &sortedVertices);

	/**
	*	Greedily find the lowest allowed color a vertex, by trying increasing colors until one is allowed.
	*
	*	@param neighborIds vector of the ids of the neighbors of the vertex to be colored
	*	@param colors unordered map from vertex ids to their color
	*	@return a color for the vertex
	*/
	Graph::Color lowestAllowedColor(Graph::VertexVector &neighbors, ColorMap &colors);

	/**
	*	Check to see if a valid coloring was performed.
	*
	*	@param colors the map from Graph::Vertex to Graph::Color of colors assigned to vertices
	*	@return true if this is a valid coloring for the graph
	*/
	bool verify(ColorMap colors);

};