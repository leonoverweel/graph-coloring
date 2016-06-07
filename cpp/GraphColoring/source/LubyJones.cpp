#include "..\include\LubyJones.h"

#include <iostream>

#define FALSE				0
#define TRUE				1
#define ALL					0

#define SKIP				0
#define UNKNOWN				1
#define LOCAL_MAX			2
#define NOT_LOCAL_MAX		3

// Constructor
LubyJones::LubyJones(Graph &graph, Graph::VertexVector &sortedVertices)
	: Colorer(graph, sortedVertices) { }

// Color the graph.
int LubyJones::color(bool verify, std::vector<uint16_t> params)
{
	// Grab parameters.
	uint16_t randomNumbers = params.at(0);
	uint16_t MISiteratios = params.at(1);

	// Return 0 for empty graph.
	if (sortedVertices.size() == 0)
		return 0;

	// Assign numbers...
	Graph::VertexVector vertexNumbers = Graph::VertexVector(sortedVertices.size());

	// sequentially, or
	if (params.at(0) == FALSE)
	{
		int number = sortedVertices.size();
		for (Graph::Vertex vertex : sortedVertices)
			vertexNumbers.at(vertex) = --number;
	}

	// randomly.
	else
	{
		// to do
	}
	
	// Color.
	uint64_t colored = 0;
	uint64_t toColor = sortedVertices.size();
	Graph::Color round = 0;

	// Main coloring loop.
	while (colored < toColor)
	{
		// Round number serves as color for this round (increment first to start at color 1).
		round++;
		
		// Maximal Independent Set algorithm parameters.
		Graph::VertexVector independentSet = Graph::VertexVector();
		uint64_t known = 0;
		uint64_t toKnow = 0;
		uint16_t iteration = 0;

		// Vertices to find MIS in this round.
		std::vector<uint16_t> vertices = std::vector<uint16_t>(sortedVertices.size());

		#pragma omp parallel for reduction(+:toKnow)
		for (int64_t vertex = 0; vertex < sortedVertices.size(); vertex++)
		{
			if (graph.getColor(vertex) == 0)
			{
				vertices.at(vertex) = UNKNOWN;
				toKnow++;
			}
		}
		
		// MIS main loop.
		while (known < toKnow && (iteration < MISiteratios || MISiteratios == ALL))
		{
			
			// Choose independent set in remaining vertices.
			uint64_t knownShared = 0;

			for (int64_t vertex = 0; vertex < sortedVertices.size(); vertex++)
			{
				
				// Skip if already colored.
				if (vertices.at(vertex) == SKIP || vertices.at(vertex) == NOT_LOCAL_MAX)
					continue;

				// Check if vertex is local max.
				Graph::Vertex vertexNumber = vertexNumbers.at(vertex);
				Graph::VertexVector neighbors = graph.getNeighbors(vertex);
				bool localMax = true;

				for (int64_t neighbor = 0; neighbor < neighbors.size(); neighbor++)
				{
					Graph::Color neighborColor = graph.getColor(neighbor);
					if (vertexNumbers.at(neighbor) > vertexNumber && vertices.at(neighbor) != SKIP)
					{
						localMax = false;
						break;
					}
				}

				// If local max, mark vertex as LOCAL_MAX and neighbors as NOT_LOCAL_MAX.
				if (localMax)
				{
					vertices.at(vertex) = LOCAL_MAX;
					knownShared++;

					for (Graph::Vertex neighbor : neighbors)
					{
						if (vertices.at(neighbor) != NOT_LOCAL_MAX && vertices.at(neighbor) != SKIP)
						{
							vertices.at(neighbor) = NOT_LOCAL_MAX;
							knownShared++;
						}
					}

					// Also add vertex to current round independent set.
					independentSet.push_back(vertex);
				}
			}

			// Mark current LOCAL_MAX and NOT_LOCAL_MAX as skippable for next MIS iteration.
			for (Graph::Vertex vertex = 0; vertex < vertices.size(); vertex++)
				if (vertices.at(vertex) == LOCAL_MAX || vertices.at(vertex) == NOT_LOCAL_MAX)
					vertices.at(vertex) = SKIP;

			known += knownShared;
			iteration++;
		}

		// Color independent set
		for (Graph::Vertex vertex : independentSet)
		{
			graph.setColor(vertex, round);
			colored++;
		}

	}
	
	// Verify and return.
	if (verify && !Colorer::verify())
		return -1;
		
	return round;
}