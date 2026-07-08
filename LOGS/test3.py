import numpy as np 
import matplotlib.pyplot as plt
C_eff = 0.9191
alpha = 50
k=2.03
theta = np.linspace(0,1080,1000) / 1080
Pm = 4000
dP = Pm * (1 - C_eff * ((1+alpha)*theta**k)/(1+(alpha*theta**k)))
Pnozzle = Pm - dP
print(Pnozzle)

par_1 = 150000*theta**2 



plt.figure()
plt.plot(theta*1080,Pnozzle)
plt.plot(theta*1080,par_1)


plt.grid(True)
# plt.xlim(0,1080)
plt.ylim(-200,4000)
plt.show()