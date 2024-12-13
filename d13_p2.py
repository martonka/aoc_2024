import numpy as np
import re

data = open("input1.txt").read().strip()
nums = np.array(list(map(int, re.findall("\\d+", data)))).reshape(-1,3,2)

answ = 0

for v1, v2, dest in nums:
    mat = np.transpose(np.array([v1,v2]))
    dest = dest + [10000000000000] * 2
    res = np.linalg.lstsq(mat, dest)[0]
    resI = np.rint(res)
    
    #with integers there should be no error
    if tuple(mat.dot(resI)) == tuple(dest): 
        x = resI.dot(np.array([3,1]))
        answ += int(x)
        
print(answ)        
    

    
    


