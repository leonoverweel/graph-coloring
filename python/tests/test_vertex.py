import unittest

from models.vertex import Vertex

class TestVertex(unittest.TestCase):
    
    def test___init__(self):
        vertex0 = Vertex()
        self.assertIsInstance(vertex0, Vertex)
        self.assertEquals([], vertex0.adjacent_to)
        self.assertEquals(None, vertex0.data)
        
        vertex1 = Vertex([u'1', u'2'])
        self.assertEquals(2, len(vertex1.adjacent_to))
        self.assertIn(u'1', vertex1.adjacent_to)
        self.assertIn(u'2', vertex1.adjacent_to)
        
        vertex2 = Vertex([], 'Test string data')
        self.assertEquals('Test string data', vertex2.data)
        
        vertex3 = Vertex([], {'test': 'dictionary data'})
        self.assertEquals({'test': 'dictionary data'}, vertex3.data)
        
    def test_add_edge(self):
        vertex0 = Vertex()
        
        vertex0.add_edge(u'1')
        self.assertEquals(1, len(vertex0.adjacent_to))
        self.assertIn(u'1', vertex0.adjacent_to)
        
        vertex0.add_edge(u'2')
        self.assertEquals(2, len(vertex0.adjacent_to))
        self.assertIn(u'1', vertex0.adjacent_to)
        self.assertIn(u'2', vertex0.adjacent_to)
        
        vertex0.add_edge(u'2')
        self.assertEquals(2, len(vertex0.adjacent_to))
        
    def test_remove_edge(self):
        vertex0 = Vertex([u'1', u'2'])
        
        vertex0.remove_edge(u'1')
        self.assertEquals(1, len(vertex0.adjacent_to))
        self.assertNotIn(u'1', vertex0.adjacent_to)
        
        vertex0.remove_edge(u'1')
        self.assertEquals(1, len(vertex0.adjacent_to))