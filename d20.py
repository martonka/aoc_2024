from coords import Coord
from queue import PriorityQueue

data = open("input2.txt").read().strip().split('\n')
tovels = set(data[0].strip().split(", "))

Coord.maxX = len(data[0])
Coord.maxY = len(data)

walls = set()
start = None
stop = None

for y, s in enumerate(data):
    for x, f in enumerate(s):
        if f == '#':
            walls.add(Coord(x,y))    
        if f == 'S':
            start = Coord(x, y)
        if f == 'E':
            stop = Coord(x, y)

def dijk(walls, start, stop):
    queue = PriorityQueue()
    queue.put((0, start))
    visited = {}
    while not queue.empty():
        s, c = queue.get()
        if c in visited and visited[c] <= s:
            continue
        visited[c] = s
        if c == stop:
            return s, visited
        for d2 in Coord.d4():
            c2 = c + d2
            s2 = s + 1
            if not c2.valid() or c2 in walls:
                continue
            if c2 in visited and visited[c2] <= s2:
                continue
            queue.put((s2,c2))
    
    return None, visited
 
base, _ = dijk(walls, start, stop)
_, v1 = dijk(walls, start, Coord(1e6,1e6))
_, v2 = dijk(walls, stop, Coord(1e6,1e6))

res = 0
cl = 20
for c1, s1 in v1.items():
    for dx in range(-cl, cl+1):
        for dy in range(-cl + abs(dx), cl + 1 - abs(dx)):
            
            c2 = c1 + (dx,dy)
            if c2 not in v2:
                continue
            s2 = v2[c2]
            
            tt = s1 + s2 + abs(dx) + abs(dy)
            if tt <= base - 100:
                res +=1
        
print("Res:", res)
