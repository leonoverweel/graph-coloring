class Vertex:
    
    def __init__(self, adjacent_to=None, data=None):
        self.adjacent_to = adjacent_to if adjacent_to is not None else []
        self.data = data if data is not None else {}
                
    def add_edge(self, id):
        if not id in self.adjacent_to:
            self.adjacent_to.append(id)
            self.adjacent_to.sort()
        
    def remove_edge(self, id):
        if id in self.adjacent_to:
            self.adjacent_to.remove(id)