#pragma once

#include <stdint.h>

struct Vertex {

	uint64_t id;
	uint16_t degree;
	bool sortByDegree;

	bool operator<(const Vertex& other) const {
		if (sortByDegree) 
			return degree < other.degree || (degree == other.degree && id < other.id);
		return id < other.id;
	}

	bool operator>(const Vertex& other) const {
		if (sortByDegree) 
			return degree < other.degree || (degree == other.degree && id > other.id);
		return id > other.id;
	}

	bool operator==(const Vertex& other) const {
		return this->id == other.id;
	}

};