#include "..\include\SequentialGreedy.h"

// Constructor
SequentialGreedy::SequentialGreedy(AdjacencyList & adjacencyList, std::set<Vertex>& sortedVertices)
	: Colorer(adjacencyList, sortedVertices) { }

// Color one vertex
void SequentialGreedy::colorVertex(ColorMap& colors, uint16_t& highest, uint64_t vertexId)
{
	uint16_t color = lowestAllowedColor(adjacencyList.getNeighbors(vertexId), colors);
	
	colors.insert(std::make_pair(vertexId, color));

	if (color > highest)
		highest = color;
}

// Greedily color all vertices.
int SequentialGreedy::color(bool ascending)
{
	static std::unordered_map<uint64_t, uint16_t> colors = std::unordered_map<uint64_t, uint16_t>();
	uint16_t highestColor = 0;

	// Ascending order
	if (ascending)
		for (auto vertex = sortedVertices.begin(); vertex != sortedVertices.end(); ++vertex)
			colorVertex(colors, highestColor, vertex->id);

	// Descending order
	else
		for (auto vertex = sortedVertices.rbegin(); vertex != sortedVertices.rend(); ++vertex)
			colorVertex(colors, highestColor, vertex->id);

	return highestColor + 1;
}