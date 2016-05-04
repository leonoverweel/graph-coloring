#include "..\include\LubyJonesGreedy.h"

#include <iostream>

// Constructor
LubyJonesGreedy::LubyJonesGreedy(AdjacencyList& adjacencyList, std::set<Vertex>& sortedVertices)
	: Colorer(adjacencyList, sortedVertices) { }

// Assign numbers
LubyJonesGreedy::NumberMap LubyJonesGreedy::assignNumbers(bool ascending)
{
	NumberMap vertexNumbers = NumberMap();
	int number;
	
	if (ascending) number = sortedVertices.size();
	else number = 0;

	for (Vertex vertex : sortedVertices)
	{
		vertexNumbers.insert(std::make_pair(vertex.id, number));
		if (ascending) number--;
		else number++;
	}

	return vertexNumbers;
}

// Color a vertex if it is a local maximum.
void LubyJonesGreedy::colorVertex(NumberMap& vertexNumbers, ColorMap& colors, uint16_t& highest, uint64_t vertexId)
{

	// Skip vertex if already colored.
	auto search = colors.find(vertexId);
	if (search != colors.end()) return;

	// Check if local max.
	auto vertexNumber = vertexNumbers.find(vertexId)->second;
	auto neighbors = adjacencyList.getNeighbors(vertexId);
	bool localMax = true;

	for (uint64_t neighbor : neighbors)
	{
		if (vertexNumbers.find(neighbor)->second > vertexNumber && colors.find(neighbor) == colors.end())
		{
			localMax = false;
			break;
		}
	}

	// Color with lowest allowed color if local max.
	if (localMax)
	{
		uint16_t color = lowestAllowedColor(neighbors, colors);
		colors.insert(std::make_pair(vertexId, color));

		if (color > highest)
			highest = color;
	}
}

// Color the graph.
int LubyJonesGreedy::color(bool ascending)
{
	// Return 0 for empty graph
	if (sortedVertices.size() == 0)
		return 0;

	ColorMap& colors = ColorMap();;
	NumberMap& vertexNumbers = assignNumbers(ascending);
	uint16_t highestColor = 0;
	
	
	while (colors.size() < sortedVertices.size())
	{
		if (ascending)
			for (auto it = sortedVertices.begin(); it != sortedVertices.end(); ++it)
				colorVertex(vertexNumbers, colors, highestColor, it->id);
		else
			for (auto it = sortedVertices.rbegin(); it != sortedVertices.rend(); ++it)
				colorVertex(vertexNumbers, colors, highestColor, it->id);
	}
	
	return highestColor + 1;
}