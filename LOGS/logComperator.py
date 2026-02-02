# from copy import deepcopy
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from log_processor_lib import log_processor
import os

import sys


# from matplotlib.widgets import Slider


log1 = 'log0249.bin'
log2 = 'log0250.bin'

log1_name = "filter = 0.05"
log2_name = "filter = 0.01"


log1 = 'log0252.bin'
log2 = 'log0253.bin'

log1_name = "gain = 2"
log2_name = "gain = 1.5"

log1 = 'log0251.bin'
log2 = 'log0255.bin'

log1_name = "z=0.8589, g=11.247,p=0.9206"
log2_name = "z=0.8556, g=10.048,p=0.9637"



log1 = 'log0260.bin'
log2 = 'log0266.bin'

log1_name = "Kp = 1"
log2_name = "Kp = 1.5"

myLog1 = log_processor(filename=log1)
myLog2 = log_processor(filename=log2)


fig,ax= plt.subplots(4,sharex=True)

fig.tight_layout()

ax[0].set_title('position')
# ax[0].plot(myLog1.df.timestamp, myLog1.df.pos_ref, label="pos_ref")
ax[0].plot(myLog1.df.timestamp, myLog1.df.pos_ref, label="pos_ref rate_limited 1")
ax[0].plot(myLog2.df.timestamp, myLog2.df.pos_ref, label="pos_ref rate_limited 2")
ax[0].plot(myLog1.positionTime, myLog1.valveAngle, label="valveAngle " + log1_name)
# ax[0].plot(myLog1.positionTime, myLog1.valveAngleKalman, label="valveAngleKalman 1")
ax[0].plot(myLog2.positionTime, myLog2.valveAngle, label="valveAngle " + log2_name)
# ax[0].plot(myLog2.positionTime, myLog2.valveAngleKalman, label="valveAngleKalman 2")

ax[0].set_ylabel("deg")
# ax[0].plot(myLog.df.timestamp, myLog.df.angleRaw/13.7, label="angleRaw")

# ax[0].plot(myLog.df.timestamp, myLog.df.valveAngleKalman, label = "kalman")
ax[0].legend()
ax[0].grid(True)
ax[1].set_title('velocity')
ax[1].plot(myLog1.df.timestamp, myLog1.df.speedDemand/6, label="speedDemand " + log1_name)
ax[1].plot(myLog2.df.timestamp, myLog2.df.speedDemand/6, label="speedDemand " + log2_name)
# ax[1].plot(myLog1.df.timestamp, myLog1.df.speed_ref_rate_limited/6, label="speed demand rate_limited")
ax[1].plot(myLog1.positionTime, myLog1.valveVelocity/6, label = "speed feedback " + log1_name)
ax[1].plot(myLog2.positionTime, myLog2.valveVelocity/6, label = "speed feedback " + log2_name)
# ax[1].plot(myLog.positionTime[:-1], np.diff(myLog.valveAngle)*4000/6, label='np.diff')
ax[1].set_ylabel("RPM")
ax[1].legend()
# ax[1].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[1].grid(True)


ax[2].grid(True)
ax[2].set_title("current")
ax[2].plot(myLog1.df.timestamp, myLog1.df.current_demand, label= "current demand")
ax[2].plot(myLog1.currentTime, myLog1.current_subsample, label='current feedback ' + log1_name)
ax[2].plot(myLog2.currentTime, myLog2.current_subsample, label='current feedback ' + log2_name)
# ax[2].plot(myLog2.df.timestamp, myLog2.df.current_demand, label= "current demand 2")
ax[2].set_ylabel("A")
ax[2].legend()
# ax[2].set_yticks(np.arange(-10,10,1))

ax[3].grid(True)
ax[3].set_title("duty")
ax[3].plot(myLog1.currentTime, myLog1.duty_subsample*100, label = "duty " + log1_name)
ax[3].plot(myLog2.currentTime, myLog2.duty_subsample*100, label = 'duty ' + log2_name)
ax[3].legend()

# ax[3].plot(myLog.positionTime[:-1],np.diff(myLog.valveVelocity)/(1e-3/4))
ax[3].set_ylabel("%")
# plt.subplots_adjust(bottom=0.25)
# plt.savefig(filename[:-4]+'.png')
plt.show()
# myLog.safe_csv()
# print(myLog.df.axes)