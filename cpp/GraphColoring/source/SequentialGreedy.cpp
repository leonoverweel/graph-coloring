#include "..\include\SequentialGreedy.h"

#include <iostream>

// Greedily color one vertex
uint16_t SequentialGreedy::colorVertexGreedy(uint64_t vertex, std::vector<uint64_t> &neighbors, ColorMap &colors)
{
	uint16_t color = 0;
	bool lowest_found = false;

	while (!lowest_found)
	{
		lowest_found = true;

		for (uint64_t id : neighbors)
		{
			auto search = colors.find(id);

			if (search == colors.end())
				continue;

			if (color == search->second)
			{
				lowest_found = false;
				color++;
				break;
			};
		}
	}

	return color;
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
