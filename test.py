from quadtree import Quadtree
import numpy as np
import time


np.random.seed(5)

p = Quadtree(0, 0, 100, 100, 5)

N = 5000000
data = 100 * np.random.random(size=(N, 2))
data = data.astype(np.float32)

start = time.time()
p.insert(data)
print(time.time() - start)


start = time.time()
r = .1
d = p.select_from(data, r)
print(time.time() - start)

print(d[0])
print()
