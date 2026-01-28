class Subsetter:
    def get_subsets(self, nums):
        result = []
        self._backtrack(sorted(nums), 0, [], result)
        return result

    def _backtrack(self, nums, start, path, result):
        result.append(list(path))
        
        for i in range(start, len(nums)):
            path.append(nums[i])
            
            self._backtrack(nums, i + 1, path, result)
            
            path.pop()

solver = Subsetter()
input_list = [int(input(f'enter {i+1} num ')) for i in range(4)]
output = solver.get_subsets(input_list)

print(f"Input: {input_list}")
print(f"Output: {output}")
