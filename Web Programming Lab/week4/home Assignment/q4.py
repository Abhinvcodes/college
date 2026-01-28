string = input()
stack = []

for c in string:
	if c == '(' or c == '[' or c == '{':
		stack.append(c)
	elif c == ')': 
		seek = stack[-1]
		if seek == '(':
			stack.pop()
			continue
		else:
			print('invalid')
			exit()
	if c == ']':
		seek = stack[-1]
		if seek == '[':
			stack.pop()
			continue
		else:
			print('invalid')
			exit()
	if c == '}':
		seek = stack[-1]
		if seek == '{':
			stack.pop()
			continue
		else:
			print('invalid')
			exit()
print('valid')
