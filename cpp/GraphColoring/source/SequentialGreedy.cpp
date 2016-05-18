#include "..\include\SequentialGreedy.h"

#include <iostream>

// Constructor
SequentialGreedy::SequentialGreedy(Graph &graph, Graph::VertexVector &sortedVertices)
	: Colorer(graph, sortedVertices) { }

// Color one vertex
void SequentialGreedy::colorVertex(ColorMap &colors, Graph::Color &highest, Graph::Vertex vertex)
{
	Graph::Color color = lowestAllowedColor(graph.getNeighbors(vertex), colors);
	
	colors.insert(std::make_pair(vertex, color));

	if (color > highest)
		highest = color;
}

// Greedily color all vertices.
int SequentialGreedy::color(bool verify, bool miscParam)
{
	static ColorMap colors = ColorMap();
	uint16_t highestColor = 0;

	// Color each vertex.
	for (int i = 0; i < sortedVertices.size(); i++)
		colorVertex(colors, highestColor, sortedVertices.at(i));

	// Verify the coloring, if necessary.
	if (verify && !Colorer::verify(colors))
		return -1;

	return highestColor + 1;
}