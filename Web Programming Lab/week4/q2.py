import random as rd

nums = []
for _ in range(10):
	nums.append(round(rd.random()*10,2))
nums.sort()
print('nums: ',nums)
print('enter target')
target = float(input())
def binarySearch(left,right):
	mid = left + (right-left)//2
	if nums[mid] == target:
		return mid
	if nums[mid] > target:
		return binarySearch(left,mid-1)
	elif nums[mid] < target:
		return binarySearch(mid+1,right)
	return -1
index = binarySearch(0,len(nums))
print(f'found {target} at index: {index}')

