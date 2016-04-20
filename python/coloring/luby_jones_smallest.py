import random

class Coloring:

	def __init__(self, graph=None):
		self.graph = graph
		self.vertices = graph.vertices
		
	def color(self, verify=False, sort="id"):
		"""Color the graph and return how many unique colors were used."""
		
		colored = 0
		round = 0
		
		# Sort
		if sort == "id":
			sorted_vertices = sorted(self.vertices, key = lambda x : x)
		elif sort == "ascending":
			sorted_vertices = sorted(self.vertices, key = lambda x : len(self.vertices[x].adjacent_to))
		elif sort == "descending":
			sorted_vertices = sorted(self.vertices, key = lambda x : -len(self.vertices[x].adjacent_to))
		
		# Assign numbers
		for i in range(0, len(sorted_vertices)):
			self.graph.set_vertex_value(sorted_vertices[i], {'number': i})
		
		# Color all vertices
		while colored < len(self.graph.vertices):
			
			# Remove colored vertices
			sorted_vertices = [x for x in sorted_vertices if not 'color' in self.graph.get_vertex_value(x)]
			
			# Test if vertex needs to be colored this round
			for vertex in sorted_vertices:
				if 'color' in self.graph.get_vertex_value(vertex):
					continue
			
				vertex_number = self.graph.get_vertex_value(vertex)['number']
				neighbors = self.graph.neighbors(vertex)
				local_max = True
				
				# Check if local max
				for neighbor in neighbors:
					data_neighbor = self.graph.get_vertex_value(neighbor)
					if 'color' in data_neighbor and data_neighbor['color'] != round:
						continue
					if data_neighbor['number'] > vertex_number:
						local_max = False
				
				# Color if local max
				if local_max:
					color = 0
					while not self.set_vertex_color(vertex, color):
						color += 1
					colored += 1
								
			# Increment round
			round += 1
		
		# Verify
		correct = True
		if verify:
			for vertex in self.graph.vertices:
				neighbors = self.graph.neighbors(vertex)
				for neighbor in neighbors:
					if self.graph.get_vertex_value(vertex)['color'] == self.graph.get_vertex_value(neighbor)['color']:
						return -1
		
		return round

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
				
		return colors
				
	def get_vertex_color(self, id):
		"""Get the color of a vertex by id, if it exists."""
		data = self.graph.get_vertex_value(id)
		
		if data is not None and 'color' in data:
			return data['color']