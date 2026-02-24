from numpy import linspace
from numpy import sin,cos,pi
import matplotlib.pyplot as plt 


r0 = 3
alpha = 40/180*pi

A = pi/sin((pi-alpha)/2) *sin(alpha)
B = sin(alpha)/2

Aeff = lambda s: A*s*(r0-s*B)

s = linspace(0,3,100)

Area = Aeff(s)

for i in range(100):
	Area[i] = Aeff(s[i])


plt.figure()
plt.plot(s,Area)
plt.plot(s,s*4.4)
plt.grid()
plt.show()