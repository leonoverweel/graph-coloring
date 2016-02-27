class Vertex:
    
    adjacent_to = []
    data = None
    
    def __init__(self, adjacent_to=[], data=None):
        self.adjacent_to = adjacent_to
        self.data = data
        
    def add_edge(self, id):
        if not id in self.adjacent_to:
            self.adjacent_to.append(id)
            self.adjacent_to.sort()
        
    def remove_edge(self, id):
        if id in self.adjacent_to:
            self.adjacent_to.remove(id)