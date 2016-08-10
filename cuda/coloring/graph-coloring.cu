#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> readFile( const std::string& path )
{
	// Open the file and make sure it exists
	std::ifstream source;
	source.open(path.c_str());

	// Iterate over the file's lines
	std::vector<std::string> lines;
	std::string line;

	if( !source ) return lines;

	while( std::getline(source, line) )
	{
		std::cout << line << std::endl;
		lines.push_back(line);
	}

	return lines;
}

int main( int argc, char *argv[] )
{

	// Make sure a graph is passed
	if( argc != 2)
	{
		std::cout << "No graph provided!\n";
		return 1;
	}

	// Read the graph
	std::string path(argv[1]);
	std::vector<std::string> lines = readFile(path);

	return 0;
}
