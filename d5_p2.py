import re

data = open("input_pre2.txt").read()

alma = set()

res = 0

for l in data.split('\n'):
    l = l.strip()
    if not l:
        continue

    if '|' in l:
        alma.add(l)
        continue

    nums = l.split(',')
    good = True



    for x in range(len(nums)-1):
        for y in range(x+1, len(nums)):
            s = f"{nums[y]}|{nums[x]}"
            if s in alma:
                nums[x], nums[y] = nums[y], nums[x]
                good = False
                continue

    if not good:
        print(' '.join(nums))                
        print(nums[len(nums) // 2])
        res += int(nums[len(nums) // 2])

print(res)