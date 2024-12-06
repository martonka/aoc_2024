

with open("input.txt") as inp:
    data = inp.read()

res = 0

for l in data.split('\n'):
    l = l.strip()
    if not l:
        continue
    a1 = list(map(int, l.split()))
    if len(a1) == 1:
        res += 1
        continue
    
    good = True

    dec1 = a1[0] < a1[1]

    for x, y in zip(a1[:-1], a1[1:]):
        if (x < y) != dec1 or x == y or abs(x-y) > 3:
            good = False
            break
        
    
    if good:
        res += 1


print(res)

