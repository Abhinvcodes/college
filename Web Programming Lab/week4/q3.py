words = [input(f"Enter word {i+1}: ") for i in range(5)]

for i in range(len(words)):
	for j in range(len(words)):
		if words[j] > words[i]:
			words[j],words[i]=words[i],words[j]

print(words)
