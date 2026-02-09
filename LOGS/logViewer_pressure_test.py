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
# filename = "log"
myLog = log_processor(filename=filename)
# print(myLog.df.axes)
# test = pd.DataFrame([])

# print( test.__dir__())
# exit()
# print(myLog.df.)
# aaa = np.diff(myLog.df.angleRaw, append=[myLog.df.angleRaw[myLog.dataLen-1]])

for filename in dirlist:
	if "log" in filename and ".bin" in filename:
		log_processor(filename)





fig,ax= plt.subplots(3,sharex=True)
fig.canvas.manager.set_window_title(filename) 

fig.tight_layout()

ax[0].grid(True)
ax[0].set_title("pressure")
ax[0].plot(myLog.df["timestamp"], myLog.df["manifold_pressure"], label="manifold_pressure")
ax[0].plot(myLog.df["timestamp"], myLog.df["nozzle_pressure"], label="nozzle_pressure")




ax[1].set_title('position')
print(myLog.valveAngle)
ax[1].plot(myLog.df.timestamp, myLog.df.pos_ref, label="pos_ref")
ax[1].plot(myLog.df.timestamp, myLog.df.pos_ref_rate_limited, label="pos_ref rate limited")
ax[1].plot(myLog.positionTime, myLog.valveAngle, label="valveAngle")
ax[1].plot(myLog.positionTime, myLog.valveAngleKalman, label="valveAngleKalman")

ax[1].set_ylabel("deg")
# ax[1].plot(myLog.df.timestamp, myLog.df.angleRaw/13.7, label="angleRaw")

# ax[1].plot(myLog.df.timestamp, myLog.df.valveAngleKalman, label = "kalman")
ax[1].legend()
ax[1].grid(True)
ax[2].set_title('velocity')
ax[2].plot(myLog.df.timestamp, myLog.df.speedDemand/6, label="speedDemand")
ax[2].plot(myLog.df.timestamp, myLog.df.speed_ref_rate_limited/6, label="speed demand rate_limited")
ax[2].plot(myLog.positionTime, myLog.valveVelocity/6, label = "speed feedback")
ax[2].set_ylabel("RPM")
ax[2].legend()
# ax[2].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[2].grid(True)
plt.savefig(filename[:-4]+'.png')
plt.show()

print(myLog.df.axes)