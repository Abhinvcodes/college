import math as m
class Circle:
	def __init__(self,radius):
		self.r = radius
	def getArea(self):
		return m.pi * self.r ** 2
	def getCircumference(self):
		return 2 * m.pi * self.r
radius = int(input('enter radius '))
obj = Circle(radius)
print('area of circle',obj.getArea(),'circumference',obj.getCircumference())
