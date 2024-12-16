from queue import PriorityQueue
from collections import deque

data = open("input_pre2.txt").read().strip().split('\n')

all_dirs = [(1, 0), (0, 1), (-1, 0), (0, -1)]
walls = set()
start_pos = None
end_pos = None

def steps2(p,d,s):
    yield (p[0] + d[0], p[1] + d[1]), d, s + 1
    yield p, (d[1], d[0]), s + 1000
    yield p, (-d[1], -d[0]), s + 1000

def steps(p, d, s):
    for p2, d2, s2 in steps2(p, d, s):
        if p2 not in walls:
            yield p2, d2, s2  

def stepsRev(p,d,s):
    yield (p[0] - d[0], p[1] - d[1]), d, s - 1
    yield p, (d[1], d[0]), s - 1000
    yield p, (-d[1], -d[0]), s - 1000
    
for y, l in enumerate(data):
    for x, c in enumerate(l):
        if c == '#':
            walls.add((x,y))
        if c == 'S':
            start_pos = (x,y)
        if c == 'E':
            end_pos = (x,y)


best = {} # {pos, dir} => score
queue = PriorityQueue() # score, pos, dir
end_score = int(1e15)

# Dijkstra
best[(start_pos, (1,0))] = 0
queue.put((0, start_pos, (1,0)))
while not queue.empty():
    s, p, d = queue.get()
    for p2, d2, s2 in steps(p,d,s):
        if p2 == end_pos:
            end_score = min(end_score, s2)
        key = (p2,d2)
        if key not in best or best[key] > s2:
            queue.put((s2,p2,d2))
            best[key] = s2

print("Road score: ", end_score)

# Revers bfs on best paths
# Stats from end point and all optimal directions
checked = set() # {pos, dir}
queue = deque()
for d in all_dirs:
    key= (end_pos, d)
    if best[key] == end_score:
        queue.append((end_pos, d))
        checked.add((end_pos, d))

# "Reverse" BFS on (pos, dir) pairs that can lead to optimal end 
while queue:
    p,d = queue.pop()
    s = best[(p,d)]
    for p2, d2, s2 in stepsRev(p,d,s):
        key = (p2,d2)
        if key in best and s2 == best[key] and key not in checked:
            checked.add(key)
            queue.append(key)


# same pos different dir counts as one
print(len(set([p for p, d in checked])))                       


        

    
    


