import matplotlib.pyplot as plt
import numpy as np

P0 = 500
P1 = 4400

if False: # TEST 1
	Q0 = 18902
	Q1 = 64406
	referances = [100, 300, 500, 1100, 1500, 2100, 2500, 3100, 3500, 4100, 4300, 4400]
	readings = [105, 310, 500, 1103, 1505, 2096, 2500, 3098, 3495, 4104, 4290, 4400]
else : # TEST 2
	Q0 = 18998
	Q1 = 64330
	referances = [100, 300, 500, 1100, 1500, 2100, 2500, 3100, 3500, 4100, 4300, 4400]
	readings = [101, 300, 500, 1088, 1488, 2073, 2479, 3093, 3485, 4098, 4284, 4400]



def linearMap(raw):
	return ((raw - Q0) * P1 + (Q1 - raw) * P0) / (Q1 - Q0)
	
def revert(press):
	# press = ((raw - Q0) * P1 + (Q1 - raw) * P0) / (Q1 - Q0)
	# press * (Q1 - Q0) = (raw - Q0) * P1 + (Q1 - raw) * P0
	# press * (Q1 - Q0) + Q0*P1 + Q1*P0 = raw * P1 - raw * P0
	# press * (Q1 - Q0) + Q0*P1 + Q1*P0 = raw * (P1 - P0)
	raw = (press * (Q1 - Q0) + Q0*P1 - Q1*P0) / (P1 - P0)
	return raw

raw_readings = revert(np.array(readings))
m, b= np.polyfit(raw_readings, referances, 1)
print(m, b)




plt.figure()
addPoint = lambda x: plt.scatter(x,linearMap(x),marker='.',c='b')


x = np.linspace(13000,65536,3)
y = linearMap(x)
plt.plot(x,y, label = '2 point fit')
plt.plot(x, m*x+b , label= "regression")



plt.scatter(Q0,P0,c="b",marker="o",s=100)
plt.scatter(Q1,P1,c="b",marker="o",s=100)



for ref, read in zip(referances, readings):
	plt.scatter(revert(read),ref, c='r', marker = '+',s=99)




plt.grid(True)
plt.show()