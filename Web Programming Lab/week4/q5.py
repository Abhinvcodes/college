class findPair:
	def find(self,arr,target):
		for i in range(len(arr)-1):
			for j in range(i+1,len(arr)):
				if arr[i] + arr[j] == target:
					return i,j
		return None
n = int(input('how many numbers '))
numbers = [int(input(f'enter {i+1} num ')) for i in range(n)]
obj = findPair()
target = int(input('enter target '))
i,j = obj.find(numbers,target)
print(i,',',j)
