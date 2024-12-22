from coords import Coord

from functools import cache
from sortedcontainers import SortedDict
from itertools import permutations
from collections import deque
from pprint import pprint

data = open("input2.txt").read().strip().split('\n')

magic_mod = 16777216

def nx(x):
    x = ((x * 64) ^ x) % magic_mod
    x = ((x // 32) ^ x) % magic_mod
    x = ((x * 2048) ^ x) % magic_mod
    return x

def cc(nums):
    assert(len(nums) == 5)
    return tuple([int(y-x) for x,y in zip(nums,nums[1:])])

dd = {}

tk = (-2,1,-1,3)
res1 = 0
for ppl in data:
    ppl = int(ppl)
    nums = [ppl]
    for i in range(2000):
        nums.append(nx(nums[-1]))
    
    res1 += nums[-1]
    nums = [x % 10 for x in nums]
    keys = set()
    for i in range(len(nums)-4):
        p = nums[i+4]
        key = cc(nums[i:i+5])
        if key in keys:
            continue
        keys.add(key)
        if key not in dd:
            dd[key] = 0
        
        dd[key] = dd[key] + p
        if key == tk:
            print(ppl, p) 

print(res1)
print(max(dd.values()))