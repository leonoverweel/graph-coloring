class Coloring:

    graph = None
    sorted_vertex_ids = None
    
    def __init__(self, graph=None):
        self.graph = graph

    def color(self, ascending=False):
        """Color the graph and return how many unique colors were used.
        
        Keyword arguments:
        ascending -- the direction of the vertex sort by number of edges
        """
        
        # Sort the vectors by how many edges they have
        self.sort_vertex_ids(ascending)
        
        # Clear the previous colors
        for i in self.sorted_vertex_ids:
            self.set_vertex_color(i, None)
        
        # Color the graph
        colors = 0
        for i in self.sorted_vertex_ids:
            color = 0
            while not self.set_vertex_color(i, color):
                color += 1
            if color > colors:
                colors = color
        
        return colors + 1

    def get_vertex_color(self, id):
        """Get the color of a vertex by id, if it exists."""
        data = self.graph.get_vertex_value(id)
    
        if data is not None and 'color' in data:
            return data['color']
        
    def set_vertex_color(self, id, color):
        """Set the color of a vertex by id, if it exists and the color is allowed. Return True if successful, False if not."""
        
        # Check if the vertex exists
        if not id in self.graph.vertices:
            return False
            
        # Check if the color is valid
        if color in self.get_neighboring_colors(id):
            return False
        
        # Set the color
        self.graph.set_vertex_value(id, {u'color': color})
        return True
        
    def get_neighboring_colors(self, id):
        """Get an ascending sorted list of the unique colors of a vertex's neighbors by its id"""
        
        neighbors = self.graph.neighbors(id)
        colors = []
        
        for i in neighbors:
            color = self.get_vertex_color(i)
            if color is not None and not color in colors:
                colors.append(color)
                
        return sorted(colors)
            
    def sort_vertex_ids(self, ascending=False):
        """"Create and return list of vertex ids sorted by the number of edges connecting to each node."""
        vertices = self.graph.vertices
        if ascending:
            self.sorted_vertex_ids = sorted(vertices, key = lambda x : len(vertices[x].adjacent_to))
        else:
            self.sorted_vertex_ids = sorted(vertices, key = lambda x : -len(vertices[x].adjacent_to))
        return self.sort_vertex_ids