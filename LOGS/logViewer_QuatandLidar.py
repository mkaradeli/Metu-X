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
# filename = 'log0382.bin'
if len(sys.argv) == 2:
	filename = sys.argv[1]
print(filename)
# filename = "log0386.bin"
myLog = log_processor(filename=filename)
# print(myLog.df.axes)
# test = pd.DataFrame([])

# print( test.__dir__())
# exit()
# print(myLog.df.)
# aaa = np.diff(myLog.df.angleRaw, append=[myLog.df.angleRaw[myLog.dataLen-1]])



print(myLog.valveVelocity)

fig,ax= plt.subplots(4,sharex=True)
fig.canvas.manager.set_window_title(filename) 

fig.tight_layout()

ax[0].set_title('quaternion')
print(myLog.valveAngle)
ax[0].plot(myLog.df.timestamp, myLog.df["quaternion_i"], label="Q_i")
ax[0].plot(myLog.df.timestamp, myLog.df["quaternion_j"], label="Q_j")
ax[0].plot(myLog.df.timestamp, myLog.df["quaternion_k"], label="Q_k")
ax[0].plot(myLog.df.timestamp, myLog.df["quaternion_r"], label="Q_r")


# ax[0].set_ylabel("deg")
# ax[0].plot(myLog.df.timestamp, myLog.df.angleRaw/13.7, label="angleRaw")

# ax[0].plot(myLog.df.timestamp, myLog.df.valveAngleKalman, label = "kalman")
ax[0].legend()
ax[0].grid(True)
ax[1].set_title('lidar')
ax[1].plot(myLog.df.timestamp, myLog.df["lidar_height"], "-o", label="lidar_height")
ax[1].set_ylim([0,10000])
# ax[1].plot(myLog.df.timestamp, myLog.df["lidar_strength"], label="lidar_strength")

# ax[1].plot(myLog.df.timestamp, myLog.df.speed_ref_rate_limited*180/np.pi/6, label="speed demand rate_limited")
# ax[1].plot(myLog.positionTime, myLog.valveVelocity/6, label = "speed feedback")
# ax[1].plot(myLog.positionTime[:-1], np.diff(myLog.valveAngle)*4000/6, label='np.diff')
ax[1].set_ylabel("mm")
ax[1].legend()
# ax[1].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[1].grid(True)

ax[2].set_title('lidar')
# ax[2].plot(myLog.df.timestamp, myLog.df["lidar_height"], label="lidar_height")
ax[2].plot(myLog.df.timestamp, myLog.df["lidar_strength"], label="lidar_strength")

# ax[2].plot(myLog.df.timestamp, myLog.df.speed_ref_rate_limited*180/np.pi/6, label="speed demand rate_limited")
# ax[2].plot(myLog.positionTime, myLog.valveVelocity/6, label = "speed feedback")
# ax[2].plot(myLog.positionTime[:-1], np.diff(myLog.valveAngle)*4000/6, label='np.diff')
ax[2].set_ylabel("mm")
ax[2].legend()
# ax[2].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[2].grid(True)


ax[3].set_title('acceleration')
# ax[3].plot(myLog.df.timestamp, myLog.df["lidar_height"], label="lidar_height")
ax[3].plot(myLog.df.timestamp, myLog.df["accel_x"], label="a_x")
ax[3].plot(myLog.df.timestamp, myLog.df["accel_y"], label="a_y")
ax[3].plot(myLog.df.timestamp, myLog.df["accel_z"], label="a_z")

# ax[3].plot(myLog.df.timestamp, myLog.df.speed_ref_rate_limited*180/np.pi/6, label="speed demand rate_limited")
# ax[3].plot(myLog.positionTime, myLog.valveVelocity/6, label = "speed feedback")
# ax[3].plot(myLog.positionTime[:-1], np.diff(myLog.valveAngle)*4000/6, label='np.diff')
ax[3].set_ylabel("mm")
ax[3].legend()
# ax[3].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[3].grid(True)


# plt.subplots_adjust(bottom=0.25)
plt.savefig(filename[:-4]+'.png')
plt.show()

print(myLog.df.axes)