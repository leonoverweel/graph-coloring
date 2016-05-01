#include "../include/AdjacencyList.h"

#include <iostream>

int main() {

	AdjacencyList adjacencyList = AdjacencyList();

	adjacencyList.addEdge(0, 1);
	adjacencyList.addEdge(0, 2);
	adjacencyList.addEdge(0, 3);
	adjacencyList.addEdge(0, 4);
	adjacencyList.addEdge(1, 3);
	adjacencyList.addEdge(2, 3);

	auto sorted = adjacencyList.getSorted(true);

	for (auto it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		std::cout << it->id << " (" << it->degree << ")" << std::endl;
	}

	while (1) {}

}