

with open("input.txt") as inp:
    data = inp.read()

res = 0


def good(a1):
    if len(a1) <=1:
        return -1
    
    dec1 = a1[0] < a1[1]

    for idx in range(len(a1)-1):
        x = a1[idx]
        y = a1[idx + 1]
        if (x < y) != dec1 or x == y or abs(x-y) > 3:
            return idx

    return -1

for l in data.split('\n'):
    l = l.strip()
    if not l:
        continue
    a1 = list(map(int, l.split()))
    
    if good(a1) == -1 or good(a1[1:]) == -1 or good(a1[:1] + a1[2:]) == -1:
        res += 1
        continue

    idx = good(a1)

    if good(a1[:idx] + a1[idx+1:]) == -1 or good(a1[:idx+1] + a1[idx+2:]) == -1:
        res += 1
        continue
    

print(res)

