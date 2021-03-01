Quadtree on Python for fast collision detection
===============================================

This library is used for datavisualisation purposes.
It is the fastest implementation available on Python. It leverages parallelism and C++ while using numpy and pybind11 as the only depedencies.

On my machine, 5 millions points can be insert in a very tight space in just 4.5 seconds, which translates to 1.1 million points inserted per second.
Selecting a squared neighboorhood around each of the 5 millions points is done in 12.4 seconds, which translates to 400k queries per second.

Clone and use `pip install .` to install the library.

```python
from quadtree import Quadtree
import numpy as np

# generate 5 millions data points
N = 5000000
data = 100 * np.random.random(size=(N, 2))

# create quadtree
qt = Quadtree(0, 0, 100, 100, 5)

# bulk insert of all data points
qt.insert(data)

# get a neighborhood selection around each point in data, using a radius of r=0.1
r = .1
queries = qt.select_from(data, r)

print(queries[0])
```