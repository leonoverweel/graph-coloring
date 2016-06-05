#include "..\include\SequentialGreedy.h"

#include <iostream>

// Constructor
SequentialGreedy::SequentialGreedy(Graph &graph, Graph::VertexVector &sortedVertices)
	: Colorer(graph, sortedVertices) { }

// Color one vertex
void SequentialGreedy::colorVertex(Graph::Color &highest, Graph::Vertex vertex)
{
	Graph::Color color = lowestAllowedColor(graph.getNeighbors(vertex));
	
	graph.setColor(vertex, color);

	if (color > highest)
		highest = color;
}

// Greedily color all vertices.
int SequentialGreedy::color(bool verify, std::vector<uint16_t> miscParam)
{
	uint16_t highestColor = 1;

	// Color each vertex.
	for (int i = 0; i < sortedVertices.size(); i++)
		colorVertex(highestColor, sortedVertices.at(i));

	// Verify the coloring, if necessary.
	if (verify && !Colorer::verify())
		return -1;

	return highestColor;
}