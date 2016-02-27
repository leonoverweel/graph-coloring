import random
import sys

from coloring import Coloring
from models.graph import Graph
from models.vertex import Vertex

def main():
    """Run graph coloring."""
    
    # Grab command line args
    file_name = sys.argv[1] if len(sys.argv) > 1 else None
    num_vertices = sys.argv[2] if len(sys.argv) > 3 else None
    num_edges = sys.argv[3] if len(sys.argv) > 3 else None
    
    # (1) Empty graph
    if file_name is None and num_vertices is None:
        graph = Graph()
    
    # (2) Graph from file
    elif file_name is not None and num_vertices is None:
        graph = Graph(file_name)
    
    # (3) Rendomly generated graph
    else:
        graph = Graph()            
        for i in range(0, int(num_vertices)):
            graph.add_vertex(unicode(i), Vertex())
        for i in range(0, int(num_edges)):
            while not graph.add_edge(random.choice(graph.vertices.keys()), random.choice(graph.vertices.keys())):
                pass
        
    # Color the graph
    coloring = Coloring(graph)
    colors = coloring.color(False)
        
    # Print graph info
    print 'GRAPH INFO:'
    print 'Vertices:', len(graph.vertices)
    print 'Edges:', num_edges
    print 'Colors:', colors
    
    # Write the graph back to the source file, if one was passed
    if file_name is not None:
        graph.write_file(file_name, True)
    
if __name__ == '__main__':
    main()