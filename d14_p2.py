import numpy as np
import re
from PIL import Image

data = open("input1.txt").read().strip()
nums = np.array(list(map(int, re.findall("-?\\d+", data)))).reshape(-1,2,2)




size = np.array([11,7], dtype=np.int64)
size = np.array([101,103], dtype=np.int64)
tc = 500

quads = np.array([0]*4, dtype=np.int64)

for t in range(tc):
    table = [[" "] * size[0] for x in range(size[1])] 

    ## X points are around the center at 11 + k*101
    t2 = 11 + t * size[0]
    
    for pos, v in nums:
        pos2 = pos + v * t2
        pos2 = pos2 % size
        table[pos2[1]][pos2[0]] = 'X' 

    print("\n".join(["".join(r) for r in table]))
    
    print("t ======== ", t2)
    input("Press Enter to continue...")    


    
    


