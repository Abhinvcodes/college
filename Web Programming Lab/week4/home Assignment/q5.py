class reverse:
	def rev(self,string):
		reversed_text = " ".join(string.split()[::-1])
		print(reversed_text)
obj = reverse()
string = input('enter a sentence ')
obj.rev(string)
