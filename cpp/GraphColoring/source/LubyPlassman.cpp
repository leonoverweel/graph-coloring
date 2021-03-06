#include "..\include\LubyPlassman.h"

#include <iostream>

const int FALSE = 0;
const int TRUE = 1;

const int ALL = 0;

const int SKIP = 0;
const int UNKNOWN = 1;
const int LOCAL_MAX = 2;
const int NOT_LOCAL_MAX = 3;

// Constructor
LubyPlassman::LubyPlassman(Graph &graph, Graph::VertexVector &sortedVertices)
	: Colorer(graph, sortedVertices) { }

// Color the graph.
int LubyPlassman::color(bool verify, std::vector<uint16_t> params)
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
		
		// Holds the vertex status (SKIP, UNKNOWN, LOCAL_MAX or NOT_LOCAL_MAX).
		std::vector<uint16_t> vertices = std::vector<uint16_t>(sortedVertices.size());

		// Keeps track of how many vertices still need to be marked as LOCAL_MAX or NOT_LOCAL_MAX this round.
		uint64_t known = 0;
		uint64_t toKnow = 0;

		// Keeps track of the MIS iteration.
		uint16_t iteration = 0;

		// The independent set for this round.
		Graph::VertexVector independentSet = Graph::VertexVector();

		// Vertices to find MIS in this round.
		#pragma omp parallel for reduction(+:toKnow)
		for (int64_t vertex = 0; vertex < sortedVertices.size(); vertex++)
		{
			if (graph.getColor(vertex) == 0)
			{
				vertices.at(vertex) = UNKNOWN;
				toKnow++;
			}
		}
		
		// Maximum Independent Set (MIS) main loop.
		while (known < toKnow && (iteration < MISiteratios || MISiteratios == ALL))
		{
			
			// Find local maxima and mark them LOCAL_MAXIMUM.
			#pragma omp parallel for reduction(+:known)
			for (int64_t vertex = 0; vertex < sortedVertices.size(); vertex++)
			{
				
				// Skip if already colored.
				if (vertices.at(vertex) == SKIP)
					continue;

				// Check if vertex is local max.
				Graph::Vertex vertexNumber = vertexNumbers.at(vertex);
				Graph::VertexVector neighbors = graph.getNeighbors(vertex);
				bool localMax = true;

				for (Graph::Vertex neighbor : neighbors)
				{
					if (vertexNumbers.at(neighbor) > vertexNumber && vertices.at(neighbor) != SKIP)
					{
						localMax = false;
						break;
					}
				}

				// If local max, mark vertex as LOCAL_MAX and add vertex to current round independent set.
				if (localMax)
				{
					vertices.at(vertex) = LOCAL_MAX; 
					known++;
				}

			}

			// Add LOCAL MAX vertices to the independent set.
			for (int64_t vertex = 0; vertex < vertices.size(); vertex++)
			{
				if (vertices.at(vertex) == LOCAL_MAX)
				{
					independentSet.push_back(vertex);
				}
			}

			// Find the neighbors of local maxima and mark them NOT_LOCAL_MAX.
			#pragma omp parallel for reduction(+:known)
			for (int64_t vertex = 0; vertex < sortedVertices.size(); vertex++)
			{
				Graph::VertexVector neighbors = graph.getNeighbors(vertex);
				
				for (Graph::Vertex neighbor : neighbors)
				{
					if (vertices.at(neighbor) == LOCAL_MAX)
					{
						vertices.at(vertex) = NOT_LOCAL_MAX;
						known++;
						break;
					}
				}
			}

			// Mark current LOCAL_MAX and NOT_LOCAL_MAX as SKIP for next MIS iteration.
			#pragma omp parallel for
			for (int64_t vertex = 0; vertex < vertices.size(); vertex++)
			{
				if (vertices.at(vertex) == LOCAL_MAX || vertices.at(vertex) == NOT_LOCAL_MAX)
				{
					vertices.at(vertex) = SKIP;
				}					
			}
				
			iteration++;
		}

		// Color independent set

		#pragma omp parallel for
		for (int64_t i = 0; i < independentSet.size(); i++)
		{
			graph.setColor(independentSet.at(i), round);
		}
			
		colored += independentSet.size();

	}
	
	// Verify and return.
	if (verify && !Colorer::verify())
		return -1;
		
	return round;
}