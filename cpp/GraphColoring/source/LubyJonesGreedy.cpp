#include "..\include\LubyJonesGreedy.h"

#include <iostream>

// Constructor
LubyJonesGreedy::LubyJonesGreedy(Graph &graph, Graph::VertexVector &sortedVertices)
	: Colorer(graph, sortedVertices) { }

// Color the graph.
int LubyJonesGreedy::color(bool verify, bool minMax)
{
	// Return 0 for empty graph.
	if (sortedVertices.size() == 0)
		return 0;

	// Assign numbers.
	Graph::VertexVector vertexNumbers = Graph::VertexVector(sortedVertices.size());
	int number = sortedVertices.size();

	for (Graph::Vertex vertex : sortedVertices)
		vertexNumbers.at(vertex) = --number;

	// Color.
	Graph::Color round = 0;
	uint32_t colored = 0;

	while (colored < sortedVertices.size())
	{
		round++;

		#pragma omp parallel for reduction (+:colored)
		for (int vertex = 0; vertex < sortedVertices.size(); vertex++)
		{

			// Skip vertex if already colored
			if (graph.getColor(vertex) != 0)
				continue;

			// Check if local max.
			Graph::Vertex vertexNumber = vertexNumbers.at(vertex);
			Graph::VertexVector neighbors = graph.getNeighbors(vertex);
			bool localMax = true;

			for (Graph::Vertex neighbor : neighbors)
			{
				Graph::Color neighborColor = graph.getColor(neighbor);
				if (vertexNumbers.at(neighbor) > vertexNumber && (neighborColor == 0 || neighborColor == round))
				{
					localMax = false;
					break;
				}
			}

			// Color if local max.
			if (localMax)
			{
				graph.setColor(vertex, round);
				colored++;
			}
		}
	}

	if (verify && !Colorer::verify())
		return -1;
		
	return round;
}