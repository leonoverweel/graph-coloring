import random

class Coloring:

	def __init__(self, graph=None):
		self.graph = graph
		self.vertices = graph.vertices
		
	def color(self, verify=False, sort="id"):
		"""Color the graph and return how many unique colors were used."""
		
		colored = 0
		round = 0
	
		if sort == "id":
			sorted_vertices = sorted(self.vertices, key = lambda x : x)
		elif sort == "ascending":
			sorted_vertices = sorted(self.vertices, key = lambda x : len(self.vertices[x].adjacent_to))
		elif sort == "descending":
			sorted_vertices = sorted(self.vertices, key = lambda x : -len(self.vertices[x].adjacent_to))
		
		# Color all vertices
		while colored < len(sorted_vertices):
			
			# Test if vertex needs to be colored this round
			for vertex in sorted_vertices:
				if 'color' in self.graph.get_vertex_value(vertex):
					continue
			
				neighbors = self.graph.neighbors(vertex)
				local_max = True
				
				# Check if local max
				for neighbor in neighbors:
					data_neighbor = self.graph.get_vertex_value(neighbor)
					if 'color' in data_neighbor and data_neighbor['color'] != round:
						continue
					if neighbor > vertex:
						local_max = False
				
				# Color if local  max
				if local_max:
					self.graph.set_vertex_value(vertex, {u'color': round})
					colored += 1
								
			# Increment round
			round += 1
		
		# Verify
		correct = True
		if verify:
			for vertex in sorted_vertices:
				neighbors = self.graph.neighbors(vertex)
				for neighbor in neighbors:
					if self.graph.get_vertex_value(vertex)['color'] == self.graph.get_vertex_value(neighbor)['color']:
						return -1
		
		return round