from coords import Coord

from functools import cache
from sortedcontainers import SortedDict
from itertools import permutations
from collections import deque
from pprint import pprint

data = open("input2.txt").read().strip().split('\n')

keys = []
locks = []

ll = []
for l in data:
    l = l.strip()
    if not l:
        continue
    ll.append(l)
    if len(ll) == 7:
        if ll[0] == "#####":
            kk=[]
            for idx in range(5):
                for d in range(7):
                    if ll[d][idx] == ".":
                        kk.append(d)
                        break
            locks.append(kk)
        else:
            kk=[]
            for idx in range(5):
                for d in range(7):
                    if ll[6-d][idx] == ".":
                        kk.append(d)
                        break
            keys.append(kk)
            
        ll = []

res = 0

def fits(k,l):
    for idx in range(5):
        if k[idx] + l[idx] >7:
            return False
    return True

for k in keys:
    for l in locks:
        if fits(k, l):
            res +=1   

print(res)