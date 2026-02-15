import matplotlib.pyplot as plt 
import numpy as np

alpha = 51.8534
C_max = 0.9197
P_m = 1000

def dP(theta, p_manifold, k):



	theta_norm = theta / 1080
	numerator = (1 + alpha) * (theta_norm ** k)
	denominator = 1 + alpha * (theta_norm ** k)
	transmission = numerator / denominator
	return p_manifold * (1 - C_max * transmission)




# dP = lambda theta, k: P_m *(1- C_max * (((theta/1080)**k) / (1+alpha * ((theta/1080)**k))))


theta = np.linspace(0, 2000, 1000)

y_kaan = dP(theta, P_m, 2.027)
y_simp = dP(theta, P_m, 2)

plt.figure(1)
plt.plot(theta,y_kaan)
plt.plot(theta,y_simp)
plt.xlabel("theta")
plt.ylabel("dP")

# plt.plot(theta,y_simp- y_kaan)

plt.grid(1)
plt.show()

print(dP(0,4000,2))
