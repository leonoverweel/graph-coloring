import json

from vertex import Vertex

class Graph:
    vertices = {}
    
    def __init__(self, file=None):
        """Initializes a new Graph from a file."""
        if file != None:
            self.read_file(file)
    
    def add_vertex(self, id, vertex):
        """Adds a vertex with given id, if no vertex with given id exists yet."""
        
        # Check if vertex with given id already exists.
        if id in self.vertices:
            return
            
        # Check if each vertex in adjacent_to exists.
        for i in vertex.adjacent_to:
            if not i in self.vertices:
                return
            
        # Add given vertex at given id.
        self.vertices[id] = vertex
        
        # Add id to adjacent_to of each vertex in vertex's adjacent_to.
        for i in vertex.adjacent_to:
            self.vertices[i].add_edge(id)
            
    def remove_vertex(self, id):
        """Removes vertex with given id, if it exists."""
        
        # Check if vertex with given id exists
        if not id in self.vertices:
            return
        
        # Remove edges going to the vertex with the given id
        for i in self.vertices[id].adjacent_to:
            self.vertices[i].remove_edge(id)
        
        # Remove the vertex
        del self.vertices[id]
        
    def add_edge(self, x, y):
        """Adds the edge from x to y (and y to x), if it is not there."""
        
        # Check if both vertices exist
        if not x in self.vertices or not y in self.vertices:
            return
        
        # Add edge to both vertices
        self.vertices[x].add_edge(y)
        self.vertices[y].add_edge(x)
        
    def remove_edge(self, x, y):
        """Removes the edge from x and y, if it exists."""
        
        # Check if both vertices exist
        if not x in self.vertices or not y in self.vertices:
            return
            
        # Remove edge from both vertices
        self.vertices[x].remove_edge(y)
        self.vertices[y].remove_edge(x)
            
    def adjacent(self, x, y):
        """Tests whether there is an edge from x to y."""
        return y in self.vertices[x].adjacent_to
    
    def neighbors(self, x):
        """Lists the ids of all vertices y that are adjacent to x."""
        return self.vertices[x].adjacent_to
        
    def get_vertex_value(self, x):
        """Returns the value associated with the vertex x."""
        if x in self.vertices:
            return self.vertices[x].data
            
        return None
        
    def set_vertex_value(self, x, data):
        """Sets the value associated with the vertex x."""
        if x in self.vertices:
            self.vertices[x].data = data
    
    def validate(self):
        """Makes sure graph doesn't contain invalid edges.
        
        An invalid edge occurs if:
        (1) one of the edge's ids is not a vertex in the graph,
        (2) an edge is not undirected, or
        (3) a vertex has an edge to itself.
        """
        
        for i in self.vertices:
            for j in self.vertices[i].adjacent_to:
            
                # Check for case 1
                if not j in self.vertices:
                    return False
                    
                # Check for case 2
                if not self.adjacent(j, i):
                    return False
                    
                # Check for case 3
                if j == i:
                    return False
        
        return True
    
    def read_file(self, file):
        """Reads a Graph from a .json file.
        
        If the .json file is valid, self.vertices is updated; if not, it's not.
        """
        
        # Open the file
        with open(file) as data_file:
            data = json.load(data_file)
        
        # Add each vertex
        for i in data:
            self.vertices[i] = Vertex(sorted(data[i]), None)
            
        # Validate resulting graph
        if not self.validate():
            self.vertices = {}
            
    
    def write_file(self, file):
        """Writes a Graph to a .json file."""
        pass