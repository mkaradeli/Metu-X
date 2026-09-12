import matplotlib.pyplot as plt
import numpy as np
from log_processor_lib import log_processor

# plt.figure(2)
# plt.xlabel('pressure')
# plt.ylabel("Force")
fig,ax= plt.subplots(2,2,sharex=True, sharey=True)
# fig.canvas.manager.set_window_title(filename)

# fig.tight_layout()
ax[0][0].set_ylabel('Force [N]')
ax[1][0].set_ylabel('Force [N]')
ax[1][0].set_xlabel('Pressure [Psi]')
ax[1][1].set_xlabel('Pressure [Psi]')
filenames = [
"LOG2470.bin",
"LOG2467.bin", 
"LOG2464.bin", 
"LOG2461.bin", 
]
myLogs = []
for filename in filenames:
	myLogs.append(log_processor(filename))

for i in range(4):
	myLogs[i].df = myLogs[i].df[myLogs[i].df["valveVelocity_2"]<50]
	myLogs[i].df = myLogs[i].df[myLogs[i].df["valveVelocity_2"]>-50]
	myLogs[i].df = myLogs[i].df[myLogs[i].df["valveAngle_2"]>50]

	ax[i//2][i%2].plot(myLogs[i].df["nozzle_pressure_2"], (myLogs[i].df['thrust_measured'])/1.87*9.80655)
	m,n = np.polyfit(myLogs[i].df["nozzle_pressure_2"], myLogs[i].df['thrust_measured']/1.87*9.80655, 1)
	print(f"force gain = {m} N/psi, or pressure gain = {1/m} psi/N")
	X = np.array([min(myLogs[i].df["nozzle_pressure_2"]), max(myLogs[i].df["nozzle_pressure_2"])])
	ax[i//2][i%2].plot(X,m*X+n)
	ax[i//2][i%2].grid(True)
	ax[i//2][i%2].set_title(f"ID = {i}, filenames[i], N/psi = {m:.5}")
	




plt.show()

