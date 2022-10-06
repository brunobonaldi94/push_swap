import itertools

permut = list(itertools.permutations([1, 2, 3,4,5]))
for x in permut:
	y = list(x)
	y = ' '.join(map(str, y))
	with open('4_n', 'a') as file:
		file.write('\n')
		file.write(y)