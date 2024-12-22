from coords import Coord

from functools import cache
from sortedcontainers import SortedDict
from itertools import permutations

data = open("input2.txt").read().strip().split('\n')


class NumBorad:
    
    @staticmethod
    def cc(p):
        if p == '0':
            return Coord(1,3)
        if p == 'A':
            return Coord(2,3)
        if p == '1':
            return Coord(0,2)
        if p == '2':
            return Coord(1,2)
        if p == '3':
            return Coord(2,2)
        if p == '4':
            return Coord(0,1)
        if p == '5':
            return Coord(1,1)
        if p == '6':
            return Coord(2,1)
        if p == '7':
            return Coord(0,0)
        if p == '8':
            return Coord(1,0)
        if p == '9':
            return Coord(2,0)
    
    @staticmethod
    def get2(p1, p2):
        c1 = NumBorad.cc(p1)
        c2 = NumBorad.cc(p2)
        
        
       
         
        if c2.y > c1.y:
            ver =  "v" * (c2.y - c1.y)
        else:
            ver = "^" * (c1.y - c2.y)
        if c2.x > c1.x:
            hor = ">" * (c2.x - c1.x)
        else:
            hor = "<" * (c1.x - c2.x)
        
        resC = [''.join(x) for x in permutations(hor + ver)]
        
        res = []
        
        for c in resC:
            if c1.y == 3:
                if c1.x == 1 and c.startswith('<'):
                    continue
                if c1.x == 2 and c.startswith('<<'):
                    continue
        
            if c1.x == 0:
                if c1.y == 2 and c.startswith('v'):
                    continue
                if c1.y == 1 and c.startswith('vv'):
                    continue
                if c1.y == 0 and c.startswith('vvv'):
                    continue
            res.append(c)

        return res        

    @staticmethod        
    def get(p1, p2):
        return [x + 'A' for x in NumBorad.get2(p1,p2)]
    

    
class DirBoard:
    
    @staticmethod
    def get2(p1, p2):
        if p1 == '<':
            if p2 == '<':
                return [""]
            if p2 == 'v':
                return [">"]
            if p2 == '^':
                return [">^"]
            if p2 == '>':
                return [">>"]
            if p2 == 'A':
                return [">>^", ">^>"]
            
        if p1 == 'v':
            if p2 == '<':
                return ["<"]
            if p2 == 'v':
                return [""]
            if p2 == '^':
                return ["^"]
            if p2 == '>':
                return [">"]
            if p2 == 'A':
                return [">^","^>"]
        
        if p1 == '>':
            if p2 == '<':
                return ["<<"]
            if p2 == 'v':
                return ["<"]
            if p2 == '^':
                return ["<^", "^<"]
            if p2 == '>':
                return [""]
            if p2 == 'A':
                return ["^"]

        if p1 == '^':
            if p2 == '<':
                return ["v<"]
            if p2 == 'v':
                return ["v"]
            if p2 == '^':
                return [""]
            if p2 == '>':
                return ["v>", ">v"]
            if p2 == 'A':
                return [">"]
            
        if p1 == 'A':
            if p2 == '<':
                return ["v<<", "<v<"]
            if p2 == 'v':
                return ["<v", "v<"]
            if p2 == '^':
                return ["<"]
            if p2 == '>':
                return ["v"]
            if p2 == 'A':
                return [""]
    
    @staticmethod
    def get(p1, p2):
        return [x + 'A' for x in DirBoard.get2(p1,p2)] 
     

        
def wayN(text):
    t2 = 'A' + text
    sf = [""]
    for f,t in zip(t2, t2[1:]):
        sf = [ss + w for w in NumBorad.get(f,t) for ss in sf] 
    
    return sf 

def wayD(text):
    t2 = 'A' + text
    sf = [""]
    for f,t in zip(t2, t2[1:]):
        sf = [ss + w for w in DirBoard.get(f,t) for ss in sf] 
    return sf

aa = set()
@cache
def cost(text_na, depth):
    aa.add(text_na)
    if depth == 0:
        return len(text_na) + 1
    
    posW = wayD(text_na + "A")
    
    bc = []
    for w in posW:
        wl = w[:-1].split('A')
        cc = 0
        for w2 in wl:
            cc += cost(w2, depth -1)
        bc.append(cc)
        
    return min(bc)          
    
def calc(text):
    lim = 25
    ws = wayN(text)
    print('\n'.join(ws))
    best = []
        
    for w2 in ws:
        cc = 0
        for w in w2[:-1].split('A'):
            cc += cost(w, lim)
       
        best.append(cc) 
            
    return min(best)       

rr = 0

for l in data:
    ll = calc(l)
    rr += ll * int(l[:-1])
    print(ll)
       
print("Res:",rr) 

print(aa)
        
print(cost("",0))  