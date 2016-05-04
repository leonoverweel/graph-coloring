#pragma once

#include "Colorer.h"

class LubyJonesGreedy : public Colorer {

private:
	
	typedef std::unordered_map<uint64_t, uint64_t> NumberMap;

	/**
	*	Color a vertex if it is the local maximum, and update the colors map and highest color accordingly.
	*
	*	@param vertexNumbers map from the vertex ids to the numbers assigned to them to decide local maxima
	*	@param colors map from the vertex ids to their colors
	*	@param highest the highest color used so far
	*	@param vertexId the id of the vertex to color
	*/
	void colorVertex(NumberMap& vertexNumbers, ColorMap& colors, uint16_t& highest, uint64_t vertexId);

	/**
	*	Assign a number to each vertex that will be used to determine local maxima. If ascending, vertices with low ids/
	*	degrees get a high number (so they are colored earlier); if not ascending (so, descending), vertices with high
	*	ids/ degrees get a high number (so they are colored earlier).
	*
	*	@param ascending order in which to iterate over the sorted vertices
	*/
	NumberMap LubyJonesGreedy::assignNumbers(bool ascending);

public:

	/**
	*	Constructor for a greedy Luby Jones graph colorer.
	*
	*	@param adjacencyList the graph to color
	*	@param sortedVertices sorted set of the vertices in the graph
	*/
	LubyJonesGreedy(AdjacencyList &adjacencyList, std::set<Vertex> &sortedVertices);

	/**
	*	Color a graph using the Luby Jones greedy algorithm.
	*
	*	@param ascending whether to iterate over the sorted vertices in an ascending order
	*	@return the number of colors used to color the graph
	*/
	int color(bool ascending) override;

};