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
# filename = 'log0260.bin'
if len(sys.argv) == 2:
	filename = sys.argv[1]
print(filename)
# filename = "log1029.bin"
# myLog = log_processor(filename=filename)
# print(myLog.df.axes)
# test = pd.DataFrame([])

# print( test.__dir__())
# exit()
# print(myLog.df.)
# aaa = np.diff(myLog.df.angleRaw, append=[myLog.df.angleRaw[myLog.dataLen-1]])

# for filename in dirlist:
# 	if "log" in filename and ".bin" in filename:
# 		print(filename)
# 		try:
myLog = log_processor(filename)




fig,ax= plt.subplots(4,sharex=True)
fig.canvas.manager.set_window_title(filename) 

fig.tight_layout()

ax[0].grid(True)
ax[0].set_title("pressure")

# try:
	# ax[0].plot(myLog.df["timestamp"], myLog.df["pressure_demand"], label="pressure_demand")
# except:
	# pass
ax[0].plot(myLog.df["timestamp"], myLog.df["manifold_pressure"], label="manifold_pressure")
ax[0].plot(myLog.df["timestamp"], myLog.df["nozzle_pressure_0"], label="nozzle_pressure")

ax[0].legend()
# ax[0].set_xlim(0,60)
# ax[0].set_ylim(-10,4500)



ax[1].set_title('position')
# print(myLog.valveAngle)
ax[1].plot(myLog.df.timestamp, myLog.df.pos_ref_0, label="pos_ref")
ax[1].plot(myLog.df.timestamp, myLog.df.pos_ref_rate_limited_0, label="pos_ref rate limited")
ax[1].plot(myLog.df.timestamp, myLog.df.valveAngle_0, label="valveAngle")
ax[1].plot(myLog.df.timestamp, myLog.df.valveAngleKalman_0, label="valveAngleKalman")
# ax[1].set_ylim(-100,2000)

ax[1].set_ylabel("deg")
# ax[1].plot(myLog.df.timestamp, myLog.df.angleRaw/13.7, label="angleRaw")

# ax[1].plot(myLog.df.timestamp, myLog.df.valveAngleKalman, label = "kalman")
ax[1].legend()
ax[1].grid(True)
ax[2].set_title('velocity')
ax[2].plot(myLog.df.timestamp, myLog.df.speedDemand_0/6, label="speedDemand")
ax[2].plot(myLog.df.timestamp, myLog.df.speed_ref_rate_limited_0/6, label="speed demand rate_limited")
ax[2].plot(myLog.df.timestamp, myLog.df.valveVelocity_0/6, label = "speed feedback")
ax[2].set_ylabel("RPM")
# ax[2].set_ylim(-500,500)
ax[2].legend()
# ax[2].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[2].grid(True)
ax[3].plot(myLog.df.timestamp, myLog.df['thrust_measured']*9.80655,label="thrust_measured")
ax[3].grid(True)
ax[3].set_ylabel("measured force (N)")
# ax[3].set_ylim(0,600)
plt.savefig(filename[:-4]+'.png')
plt.show()
plt.figure()
plt.plot(myLog.df.timestamp)
plt.show()
print(myLog.struct_size)
# plt.show()
		# except:
		# 	continue

# print(myLog.df["manifold_pressure"][0])

# print(myLog.df.axes)