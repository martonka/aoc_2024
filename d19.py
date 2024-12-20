from functools import cache

data = open("input2.txt").read().strip().split('\n')
tovels = set(data[0].strip().split(", "))

@cache
def possible(des):
    if len(des) == 0:
        return 1
    return sum([possible(des[len(t):]) for t in tovels if des.startswith(t)])
     
print(sum([possible(des) for des in data[2:]]))
