#include "..\include\SequentialGreedy.h"

#include <iostream>

// Greedily color one vertex
uint16_t SequentialGreedy::colorVertexGreedy(uint64_t vertex, std::vector<uint64_t> &neighbors, ColorMap &colors)
{
	std::set<uint16_t> neighborColors = std::set<uint16_t>();
	for (uint64_t neighbor : neighbors)
	{
		auto search = colors.find(neighbor);
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

// Greedily color all vertices.
int SequentialGreedy::color(AdjacencyList adjacencyList, std::set<Vertex> sortedVertices, bool ascending)
{
	static std::unordered_map<uint64_t, uint16_t> colors = std::unordered_map<uint64_t, uint16_t>();
	uint16_t highestColor = 0;

	// Ascending order
	if (ascending)
	{
		for (auto vertex = sortedVertices.begin(); vertex != sortedVertices.end(); ++vertex)
		{
			uint16_t color = colorVertexGreedy(
				vertex->id,
				adjacencyList.getNeighbors(vertex->id),
				colors
			);

			colors.insert(std::make_pair(vertex->id, color));

			if (color > highestColor)
				highestColor = color;
		}
	}

	// Descending order
	else
	{
		for (auto vertex = sortedVertices.rbegin(); vertex != sortedVertices.rend(); ++vertex)
		{
			uint16_t color = colorVertexGreedy(
				vertex->id,
				adjacencyList.getNeighbors(vertex->id),
				colors
			);

			colors.insert(std::make_pair(vertex->id, color));

			if (color > highestColor)
				highestColor = color;
		}
	}

	return highestColor + 1;
}
