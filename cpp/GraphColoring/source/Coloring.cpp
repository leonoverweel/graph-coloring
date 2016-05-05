#include "../include/Colorer.h"

// Constructor.
Colorer::Colorer(AdjacencyList & adjacencyList, std::set<Vertex>& sortedVertices)
	:adjacencyList(adjacencyList), sortedVertices(sortedVertices) { }

// Default color function returns -1 if not implemented by child class.
int Colorer::color(bool ascending, bool miscParam) 
{ 
	return -1; 
}

// Greedily color one vertex
uint16_t Colorer::lowestAllowedColor(std::vector<uint64_t> &neighborIds, ColorMap &colors)
{
	std::set<uint16_t> neighborColors = std::set<uint16_t>();
	for (uint64_t neighborId : neighborIds)
	{
		auto search = colors.find(neighborId);
		if (search == colors.end())	continue;
		neighborColors.insert(search->second);
	}

	uint16_t last = 0;
	for (uint16_t color : neighborColors)
	{
		if (color == last) last += 1;
		else break;
	}

	return last;
}
