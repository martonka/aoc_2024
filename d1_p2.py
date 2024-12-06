from collections import Counter


with open("input.txt") as inp:
    data = inp.read()

a1 = []
a2 = []

for l in data.split('\n'):
    l = l.strip()
    if not l:
        continue
    x1, x2 = list(map(int, l.split()))
    a1.append(x1)
    a2.append(x2)

a1.sort()
a2.sort()

res = 0

cc = Counter(a2)

for x in a1:
    res += x * cc[x]


print(res)

