import sys

from coloring import Coloring
from models.graph import Graph
from models.vertex import Vertex

def main():
    
    file_name = sys.argv[1] if len(sys.argv) > 1 else None
    graph = Graph(file_name) if file_name is not None else Graph()
    
    for i in graph.vertices:
        print i, graph.vertices[i].data, graph.vertices[i].adjacent_to
    
    graph.write_file('data/graph0.json', True)
    
if __name__ == '__main__':
    main()