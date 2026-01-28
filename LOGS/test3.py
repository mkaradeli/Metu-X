# mean =  * 65536

amper = lambda mean: (mean / 65536 * 3.3 - 2.5) / 0.066


import matplotlib.pyplot as plt 
import numpy as np 

means = np.linspace(0,65536,1000)

current = amper(means)


plt.figure(1)
plt.plot(means/65536*3.3,-current)
plt.grid(1)
plt.show()