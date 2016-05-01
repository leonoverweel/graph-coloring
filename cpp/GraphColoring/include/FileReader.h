#pragma once

#include "AdjacencyList.h"

class FileReader
{
	
public:

	/**
	*	Read an edge list in an out.* file and return the adjacency list of the undirected graph it represents.
	*
	*	@param filepath path to the out.* file relative to the VS project file
	*	@return the adjacency list representing the graph in the out.* file
	*/
	static AdjacencyList read(std::string filepath);

};