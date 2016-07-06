#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph
{

public:

	typedef uint16_t Color;
	typedef uint64_t Vertex;
	typedef std::vector<Vertex> VertexVector;
	typedef std::vector<std::pair<Vertex, VertexVector>> AdjacencyList;

	/**
	*	Constructs a Graph from a file.
	*
	*	@param filepath the path to the file to read
	*	@param sortByDegree whether the vertices should be ordered by degree (true) or vertex id (false)
	*	@param sortAscending whether the vertices should be sorted in ascending (true) or descending (false) order
	*/
	Graph(std::string filepath, bool sortByDegree, bool sortAscending);

	/**
	*	Get the color of the vertex with the specified id.
	*
	*	@param vertex the id of the vertex whose color to get
	*	@return the color of the vertex with the specified id
	*/
	Color getColor(Vertex vertex);

	/**
	*	Set the color of the vertex with the specified id.
	*
	*	@param vertex the id of the vertex whose color to set
	*	@param color the color to set for the vertex with the specified id
	*/
	void setColor(Vertex vertex, Color color);

	/**
	*	Get the ids of a vertex's neighbors.
	*
	*	@param vertex id of the vertex whose neighbors to get
	*	@return the ids of vertex's neighbors
	*/
	VertexVector getNeighbors(Vertex vertex);

	/**
	*	Get the sorted set of vertex ids, to iterate over.
	*
	*	@return a reference to the sorted set of vertex ids
	*/
	VertexVector getSortedVertices();


	/**
 	*	Get the adjacency list
 	*
 	*	@return the adjacency list
 	*/
	AdjacencyList getAdjacencyList();

private:

	AdjacencyList adjacencyList;
	VertexVector sortedVertices;

};
