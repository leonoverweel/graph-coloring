import json

from vertex import Vertex

class Graph:
    
    def __init__(self, file_name=None):
        """Initializes a new Graph from a file."""
        
        # Initialize instance variables
        self.vertices = {}
        
        # Read graph
        if file_name != None:
            self.read_file(file_name)
    
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
            return False
            
        # Check if the vertices are the same
        if x == y:
            return False
        
        # Add edge to both vertices
        self.vertices[x].add_edge(y)
        self.vertices[y].add_edge(x)
        return True
        
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
            
        return {}
        
    def set_vertex_value(self, x, data):
        """Adds data dict to the vertex x.
        
        If a key in data has value None, that key is deleted from the vertex's data. 
        """
        if x in self.vertices and data is not None:
            for i in data:
                if data[i] is not None:
                    self.vertices[x].data[i] = data[i]
                elif i in self.vertices[x].data:
                    del self.vertices[x].data[i]
    
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
                    print 1, i, j
                    return False
                    
                # Check for case 2
                if not self.adjacent(j, i):
                    print 2, i, j
                    return False
                    
                # Check for case 3
                if j == i:
                    print 3, i, j
                    return False
        
        return True
    
    def read_file(self, file_name):
        """Reads a Graph from a .json file.
        
        If the .json file is valid, self.vertices is updated; if not, it's not.
        """
        
        # Open the file
        with open(file_name) as data_file:
            data = json.load(data_file)
        
        # Add each vertex
        for i in data['adjacency_list']:
            self.vertices[i] = Vertex(sorted(data['adjacency_list'][i]), data['data'][i])
            
        # Validate resulting graph
        if not self.validate():
            self.vertices = {}
            
    def write_file(self, file_name, pretty=False):
        """Writes a Graph to a .json file."""
        
        # Set up and fill adjacency list and data dicts
        adjacency_list = {}
        data = {}
        
        for i in self.vertices:
            adjacency_list[i] = self.vertices[i].adjacent_to
            data[i] = self.vertices[i].data
        
        # Create final dict to write to file
        file_data = {
            'adjacency_list': adjacency_list,
            'data': data
        }

        # Write to file
        with open(file_name, 'w') as outfile:
            if pretty:
                outfile.write(json.dumps(file_data, indent=4, sort_keys=True))
            else:
                outfile.write(json.dumps(file_data, sort_keys=True))