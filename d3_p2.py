import re

data = open("input.txt").read()
gg = re.findall("mul\\((\\d+),(\\d+)\\)|(do)\\(\\)|(don)'t\\(\\)", data) 

enabled = True
res = 0

for x in gg:
    enabled = x[2] or enabled and not x[3]
    if x[0] and enabled:
        res += int(x[0]) * int(x[1])

print(res)
