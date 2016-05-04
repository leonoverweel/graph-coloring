#include "..\include\LubyJonesGreedy.h"

#include <iostream>

int LubyJonesGreedy::color(AdjacencyList & adjacencyList, std::set<Vertex>& sortedVertices, bool ascending)
{
	// Return 0 for empty graph
	if (sortedVertices.size() == 0)
		return 0;

	ColorMap colors = ColorMap();
	std::unordered_map<uint64_t, uint64_t> vertexNumbers = std::unordered_map<uint64_t, uint64_t>();
	
	uint64_t size = sortedVertices.size();
	uint64_t number = size;
	uint16_t highestColor = 0;

	// If ascending, vertices with low degrees/ ids get assigned the earlier (higher) numbers, and get colored first.
	if (ascending)
	{
		for (auto it = sortedVertices.begin(); it != sortedVertices.end(); ++it)
		{
			vertexNumbers.insert(std::make_pair(it->id, number));
			number--;
		}

		while (colors.size() < size)
		{
			for (Vertex vertex : sortedVertices)
			{

				// Skip vertex if already colored.
				auto search = colors.find(vertex.id);
				if (search != colors.end()) continue;

				// Check if local max.
				auto vertexNumber = vertexNumbers.find(vertex.id)->second;
				auto neighbors = adjacencyList.getNeighbors(vertex.id);
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
					uint16_t color = colorVertexGreedy(vertex.id, neighbors, colors);
					colors.insert(std::make_pair(vertex.id, color));

					if (color > highestColor)
						highestColor = color;
				}
			}
		}
	}

	// If descending, vertices with high degrees/ ids get assigned the earlier (higher) numbers, and get colored first.
	else
	{
		for (auto it = sortedVertices.rbegin(); it != sortedVertices.rend(); ++it)
		{
			vertexNumbers.insert(std::make_pair(it->id, number));
			number--;
		}
		
		while (colors.size() < size)
		{
			for (auto it = sortedVertices.rbegin(); it != sortedVertices.rend(); ++it)
			{
				auto vertex = *it;
				// Skip vertex if already colored.
				auto search = colors.find(vertex.id);
				if (search != colors.end()) continue;

				// Check if local max.
				auto vertexNumber = vertexNumbers.find(vertex.id)->second;
				auto neighbors = adjacencyList.getNeighbors(vertex.id);
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
					uint16_t color = colorVertexGreedy(vertex.id, neighbors, colors);
					colors.insert(std::make_pair(vertex.id, color));

					if (color > highestColor)
						highestColor = color;
				}
			}
		}
	}

	return highestColor + 1;
}
