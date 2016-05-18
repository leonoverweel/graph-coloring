#include "../include/Colorer.h"

#include <set>

// Constructor.
Colorer::Colorer(Graph &graph, Graph::VertexVector &sortedVertices)
	:graph(graph), sortedVertices(sortedVertices) { }

// Default color function returns -1 if not implemented by child class.
int Colorer::color(bool ascending, bool miscParam) 
{ 
	return -1; 
}

// Greedily color one vertex
uint16_t Colorer::lowestAllowedColor(Graph::VertexVector &neighborIds, ColorMap &colors)
{
	std::set<Graph::Color> neighborColors = std::set<Graph::Color>();

	for (Graph::Vertex neighborId : neighborIds)
	{
		auto search = colors.find(neighborId);
		if (search == colors.end())	continue;
		neighborColors.insert(search->second);
	}

	Graph::Color last = 0;
	for (Graph::Color color : neighborColors)
	{
		if (color == last) last++;
		else break;
	}

	return last;
}

// Verify that this is a correct coloring for the graph.
bool Colorer::verify(ColorMap colors)
{
	for (auto vertex : sortedVertices)
	{
		Graph::VertexVector neighbors = graph.getNeighbors(vertex);
		Graph::Color vertexColor = colors.find(vertex)->second;

		for (auto neighbor : neighbors)
		{
			Graph::Color neighborColor = colors.find(neighbor)->second;
			
			if (vertexColor == neighborColor)
				return false;
		}
	}

	return true;
}
