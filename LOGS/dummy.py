import matplotlib.pyplot as plt 
import numpy as np

X = np.linspace(0,9e3,1000)
Y = X//800 *100


plt.figure(1)
plt.plot(X/1000,Y)

rY = (9000//800 - X//800 ) *100

plt.plot(X/1000,rY)
# plt.plot(theta,y_simp- y_kaan)

plt.grid(1)
plt.show()
