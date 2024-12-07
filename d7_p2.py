import re
from  functools import cmp_to_key
data = open("input_pre2.txt").read()


def can_do(exp, sf, nums):
    if not nums:
        return sf == exp
    return can_do(exp, sf + nums[0], nums[1:]) \
        or can_do(exp, sf * nums[0], nums[1:]) \
        or can_do(exp, int(str(sf) + str(nums[0])), nums[1:]) 
    

rr = 0

for l in data.split('\n'):
    l = l.strip()
    if not l:
        continue

    exp, rem = l.split(':')
    nums= rem.split()
    exp = int(exp)
    nums = list(map(int,nums))
    if (can_do(exp, nums[0], nums[1:])):
        rr += exp

print(rr)

