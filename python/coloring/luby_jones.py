import random

class Coloring:

	graph = None
    
	def __init__(self, graph=None):
		self.graph = graph
		
	def color(self, verify=False):
		"""Color the graph and return how many unique colors were used."""
		
		vertices = self.graph.vertices
		numbers = range(0, len(vertices))
		random.shuffle(numbers)
		
		# Assign number
		for vertex in vertices:
			self.graph.set_vertex_value(vertex, {'number': numbers.pop()})
		
		colored = 0
		round = 0
		
		# Color all vertices
		while colored < len(vertices):
			
			# Test if vertex needs to be colored this round
			for vertex in vertices:
				if 'color' in self.graph.get_vertex_value(vertex):
					continue
			
				neighbors = self.graph.neighbors(vertex)
				#min = vertex
				max = vertex
				
				# Check if local min or max
				for neighbor in neighbors:
					data_neighbor = self.graph.get_vertex_value(neighbor)
					data_max = self.graph.get_vertex_value(max)
					#data_min = self.graph.get_vertex_value(min)
					
					if not 'color' in data_max and data_neighbor['number'] > data_max['number']:
						max = neighbor

					#if not 'color' in data_min and data_neighbor['number'] < data_min['number']:
					#	min = neighbor
			
				# Color if local min or max
				if max == vertex: #or min == vertex:
					self.graph.set_vertex_value(vertex, {u'color': round})
					colored += 1
			
			# Increment round
			round += 1
		
		# Vertify
		correct = True
		if verify:
			for vertex in vertices:
				#pass
				#neighbors = self.graph.neighbors(vertex)
				print self.graph.get_vertex_value(vertex)				
				#for neighbor in neighbors:
					#if self.graph.get_vertex_value(vertex)['color'] == self.graph.get_vertex_value(neighbor)['color']:
						#return -1
		
		return round + 1