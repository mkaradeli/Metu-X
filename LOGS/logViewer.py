# from copy import deepcopy
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from log_processor_lib import log_processor
import os

# from matplotlib.widgets import Slider


dirlist = sorted(os.listdir("."))
# logName = ""


for _ in dirlist:
	if "log" in _ and ".bin" in _:
		filename = _
# filename = 'log0163.bin'

print(filename)

myLog = log_processor(filename=filename)
# print(myLog.df.axes)
# test = pd.DataFrame([])

# print( test.__dir__())
# exit()
# print(myLog.df.)
# aaa = np.diff(myLog.df.angleRaw, append=[myLog.df.angleRaw[myLog.dataLen-1]])





fig,ax= plt.subplots(4,sharex=True)
fig.tight_layout()

ax[0].set_title('position')
print(myLog.valveAngle)
ax[0].plot(myLog.positionTime, myLog.valveAngle, label="valveAngle")
ax[0].plot(myLog.positionTime, myLog.valveAngleKalman, label="valveAngleKalman")
ax[0].plot(myLog.df.timestamp, myLog.df.pos_ref, label="pos_ref")
ax[0].set_ylabel("deg")
# ax[0].plot(myLog.df.timestamp, myLog.df.angleRaw/13.7, label="angleRaw")

# ax[0].plot(myLog.df.timestamp, myLog.df.valveAngleKalman, label = "kalman")
ax[0].legend()
ax[0].grid(True)
ax[1].set_title('velocity')
ax[1].plot(myLog.positionTime, myLog.valveVelocity/6, label = "speed feedback")
ax[1].plot(myLog.df.timestamp, myLog.df.speedDemand/6, label="speedDemand")
ax[1].set_ylabel("RPM")
ax[1].legend()
# ax[1].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[1].grid(True)


ax[2].grid(True)
ax[2].plot(myLog.currentTime, myLog.current_subsample, label='current feedback')
ax[2].plot(myLog.df.timestamp, myLog.df.current_demand, label= "current demand")
ax[2].set_ylabel("A")
ax[2].legend()
# ax[2].set_yticks(np.arange(-10,10,1))

ax[3].grid(True)
ax[3].plot(myLog.currentTime, myLog.duty_subsample*100)
ax[3].set_ylabel("%")
# plt.subplots_adjust(bottom=0.25)
plt.savefig(filename[:-4]+'.png')
plt.show()
myLog.safe_csv()
print(myLog.df.axes)