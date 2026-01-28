class power:
	def pow(self,n,p):
		prod = n
		for i in range(p):
			prod *= n
		return prod
		
obj = power()
num = int(input('enter number: '))
powr = int(input('enter power: '))
print(f'pow({num},{powr}): ',pow(num,powr))
