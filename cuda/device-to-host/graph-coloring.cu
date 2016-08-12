#include <iostream>
#include <vector>

bool verbose = true;
int SIZE = 10;

__global__
void assign_state(uint8_t * states)
{
	states[threadIdx.x] = 42;
}

int main (int argc, char *argv[])
{

	// Create host states vector
	if (verbose) std::cout << "Creating host memory... ";

	std::vector<uint8_t> * states = new std::vector<uint8_t>(SIZE);
	int statesSize = states->size() * sizeof(uint8_t);
	
	if (verbose) std::cout << "Done\n";

	// Send data to device
	if (verbose) std::cout << "Sending graph to device... ";
	
	uint8_t * deviceStatesPointer;
	cudaMalloc((void**)&deviceStatesPointer, statesSize);
	cudaMemcpy(deviceStatesPointer, states, statesSize, cudaMemcpyHostToDevice);

	if (verbose) std::cout << "Done\n";

	// Assign states
	if (verbose) std::cout << "Assign states... ";

	dim3 dimBlock(SIZE, 1);
	dim3 dimGrid(1, 1);
	assign_state<<<dimGrid, dimBlock>>>(deviceStatesPointer);

	if (verbose) std::cout << "Done\n";

	// Get data back from device
	if (verbose) std::cout << "Getting data back from device...\n";

	cudaMemcpy(states, deviceStatesPointer, statesSize, cudaMemcpyDeviceToHost);

	if (verbose)
	{
		for (int i = 0; i < states->size(); i++)
		{
			std::cout << "\t" << i << ": " << states->at(i) << std::endl;

		}
	}

	if (verbose) std::cout << "Done\n";

	return 0;
}
