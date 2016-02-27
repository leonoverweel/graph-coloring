import sys

from models.graph import Graph
from models.vertex import Vertex

def main():
    
    graph = Graph()
    if len(sys.argv) > 1:
        graph = Graph(sys.argv[1])
        
    for i in graph.vertices:
        print i, graph.vertices[i].data, graph.vertices[i].adjacent_to
    
if __name__ == '__main__':
    main()