#include "../include/Coloring.h"

// Greedily color one vertex
uint16_t Coloring::colorVertexGreedy(uint64_t vertex, std::vector<uint64_t> &neighbors, ColorMap &colors)
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
