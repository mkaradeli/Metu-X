# from copy import deepcopy
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from log_processor_lib import log_processor
import os

import sys


# from matplotlib.widgets import Slider


dirlist = sorted(os.listdir("."))
# logName = ""


for _ in dirlist:
	if "log" in _ and ".bin" in _:
		filename = _
# filename = 'log1260.bin'
if len(sys.argv) == 2:
	filename = sys.argv[1]
print(filename)
filename = "log2014.bin"
# myLog = log_processor(filename=filename)
# print(myLog.df.axes)
# test = pd.DataFrame([])

# print( test._dir_())
# exit()
# print(myLog.df.)
# aaa = np.diff(myLog.df.angleRaw, append=[myLog.df.angleRaw[myLog.dataLen-1]])

# for filename in dirlist:
# 	if "log" in filename and ".bin" in filename:
# 		print(filename)
# 		try:
myLog = log_processor(filename)




fig,ax= plt.subplots(3,4,sharex=True)
fig.canvas.manager.set_window_title(filename)

fig.tight_layout()

for i in range(4):
	ax[0][i].grid(True)
	ax[0][i].set_title(f"Nozzle Pressure {i}")

	ax[0][i].plot(myLog.df["timestamp"], myLog.df[f"nozzle_pressure_{i}"], label="Nozzle Pressure")
	ax[0][i].set_ylabel('Nozzle Pressure [Psi]')
	ax[0][i].legend()
	# ax[0][i].set_xlim(0,60)
	# ax[0][i].set_ylim(-10,4500)



	ax[1][i].set_title(f'Valve Position {i}')
	ax[1][i].plot(myLog.df.timestamp, myLog.df[f"pos_ref_{i}"], label="Position Referance")
	ax[1][i].plot(myLog.df.timestamp, myLog.df[f"valveAngle_{i}"], label="Position Feedback")
	# ax[1][i].set_ylim(-100,2000)

	ax[1][i].set_ylabel("Valve Angle [deg]")
	ax[1][i].legend()
	ax[1][i].grid(True)

	ax[2][i].plot(myLog.df.timestamp, myLog.df[f"current_demand_{i}"], label = "demand")
	ax[2][i].plot(myLog.df.timestamp, myLog.df[f"current_measured_{i}"], label="measured")
	ax[2][i].grid(True)
	ax[2][i].set_ylabel("current [A]")
	ax[2][i].set_xlabel("time [s]")


# ax[3].set_ylim(0,600)
plt.savefig(filename[:-4]+'.png')

fig2,ax2= plt.subplots(1,sharex=True)
fig2.canvas.manager.set_window_title(filename+" manifold")

fig2.tight_layout()

ax2.grid(True)
ax2.set_title('Manifold Pressure')
ax2.plot(myLog.df.timestamp, myLog.df.manifold_pressure, label="Manifold Pressure")
ax2.set_ylabel('Manifold Pressure [Psi]')
ax2.set_xlabel("time [s]")
ax2.legend()

fig3,ax3= plt.subplots(3,sharex=True)
fig3.canvas.manager.set_window_title(filename+" overlay")

fig3.tight_layout()

for i in range(4):
	ax3[0].plot(myLog.df.timestamp, myLog.df[f"nozzle_pressure_{i}"], label=f"Nozzle Pressure {i}")
	ax3[1].plot(myLog.df.timestamp, myLog.df[f"valveAngle_{i}"], label=f"Position Feedback {i}")
	ax3[2].plot(myLog.df.timestamp, myLog.df[f"current_measured_{i}"], label=f"Current {i}")

ax3[0].grid(True)
ax3[0].set_title("Nozzle Pressure")
ax3[0].set_ylabel('Nozzle Pressure [Psi]')
ax3[0].legend()

ax3[1].grid(True)
ax3[1].set_title('Valve Position')
ax3[1].set_ylabel("Valve Angle [deg]")
ax3[1].legend()

ax3[2].grid(True)
ax3[2].set_title('Current')
ax3[2].set_ylabel("current [A]")
ax3[2].set_xlabel("time [s]")
ax3[2].legend()

plt.show()
plt.figure()
plt.plot(1e3*np.diff(myLog.df.timestamp),'.')
plt.ylabel("entry period [ms]")
plt.xlabel("entry id")
plt.grid(1)
plt.show()
print(f"logging period std= {np.std(1e6*np.diff(myLog.df.timestamp)):.3} us")
print(f"logging period mean= 1.0 ms + {-1000+np.mean(1e6*np.diff(myLog.df.timestamp))} us")

print(myLog.struct_size)
# plt.show()
		# except:
		# 	continue

# print(myLog.df["manifold_pressure"][0])

# print(myLog.df.axes)
