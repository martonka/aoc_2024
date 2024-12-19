from functools import cache

data = open("input2.txt").read().strip().split('\n')
tovels = set(data[0].strip().split(", "))

@cache
def possible(des):
    if len(des) == 0:
        return 1
    res = 0
    for t in tovels:
        if des.endswith(t):
            res += possible(des[:-len(t)])
    return res
     
print(sum([possible(des) for des in data[2:]]))
