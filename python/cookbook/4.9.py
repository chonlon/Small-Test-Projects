from itertools import combinations, permutations

items = ['a','b','c']
for p in permutations(items):
    print(p)

for c in combinations(items, 2):
    print(c)