import os

from models.graph import Graph
from models.vertex import Vertex

def read_out_file(file_path, verbose=False):
    """Read a graph from an out file."""

    graph = Graph()
    edges = []

    # Open file.
    if verbose:
        print "Opening file", file_path

    with open(file_path + '\\out.' + os.path.basename(file_path)) as f:
        for line in f:
            if line.startswith('%'):
                continue
            edges.append([int(x) for x in line.split()])
    
    # Add all vertices
    if verbose:
        print "Adding all vertices"
    for edge in edges:
        graph.add_vertex(edge[0], Vertex())
        graph.add_vertex(edge[1], Vertex())

    # Add all edges
    for edge in edges:
        graph.add_edge(edge[0], edge[1])
    
    return graph