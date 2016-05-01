#include "../include/AdjacencyList.h"
#include "../include/FileReader.h"

#include <iostream>

int main() {

	std::string base = "../../../../OneDrive/Documents/TU Delft/Research/Graphs/";
	std::string path = base + "tiny/out.tiny";
	
	AdjacencyList adjacencyList = FileReader::read(path);
	auto sorted = adjacencyList.getSorted(true);

	for (auto it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		std::cout << it->id << " (" << it->degree << ")" << std::endl;
	}

	while (1) {}

}