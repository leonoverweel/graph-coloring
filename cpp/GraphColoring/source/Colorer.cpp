#include "../include/Colorer.h"

#include <set>
#include <iostream>

// Constructor.
Colorer::Colorer(Graph &graph, Graph::VertexVector &sortedVertices)
	:graph(graph), sortedVertices(sortedVertices) { }

// Default color function returns -1 if not implemented by child class.
int Colorer::color(bool ascending, std::vector<uint16_t> miscParam) 
{ 
	return -1; 
}

// Greedily color one vertex
uint16_t Colorer::lowestAllowedColor(Graph::VertexVector &neighbors)
{

	// Find the vertex's neighbor's colors

	std::set<Graph::Color> neighborColors = std::set<Graph::Color>();
	Graph::Color neighborColor; 

	for (Graph::Vertex neighbor : neighbors)
	{
		neighborColor = graph.getColor(neighbor);
		if (neighborColor != 0)
			neighborColors.insert(neighborColor);
	}

	// Pick the lowest color not in the neighbor's colors

	Graph::Color last = 1;
	for (Graph::Color color : neighborColors)
	{
		if (color == last) last++;
		else break;
	}

	return last;
}

// Verify that this is a correct coloring for the graph.
bool Colorer::verify()
{
	for (auto vertex : sortedVertices)
	{

		// Make sure the vertex is colored.

		Graph::Color vertexColor = graph.getColor(vertex);
		if (vertexColor == 0)
			return false;
			
		// Make sure none of the vertex's neighbors have the same color.

		Graph::VertexVector neighbors = graph.getNeighbors(vertex);
		for (auto neighbor : neighbors)
		{
			Graph::Color neighborColor = graph.getColor(neighbor);
			if (vertexColor == neighborColor)
				return false;
		}
	}

	return true;
}
