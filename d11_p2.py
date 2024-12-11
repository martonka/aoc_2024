import re
from  functools import cmp_to_key
from functools import cache
data = open("input_pre2.txt").read()

nums = list(map( int, data.split()))

@cache
def f(num, depth):
    if depth == 0:
        return 1
    if num == 0:
        return f(1, depth -1)
    if len(str(num)) % 2 == 0:
        x = str(num)
        return f(int(x[:len(x)//2]), depth -1) \
         + f(int(x[len(x)//2:].lstrip("0") or "0"), depth -1)
    return f(num * 2024, depth -1)

print(sum([f(x, 75) for x in nums ]))
