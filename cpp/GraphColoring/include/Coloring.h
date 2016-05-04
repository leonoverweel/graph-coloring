#pragma once

#include "AdjacencyList.h"

#include <unordered_map>

class Coloring
{

protected:
	typedef std::unordered_map<uint64_t, uint16_t> ColorMap;
	static uint16_t colorVertexGreedy(uint64_t vertex, std::vector<uint64_t> &neighbors, ColorMap &colors);

};