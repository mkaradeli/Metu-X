# from copy import deepcopy
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from log_processor_lib import log_processor
import os

import sys


log1 = 'log0394.bin'
log2 = 'log0395.bin'

log1_name = "open loop pressure"
log2_name = "yuzey kaymasi duzeltilmis."
# log1_name = "f_speed = 300, Kff=0.8"
# log2_name = "f_speed = 400, Kff=0"

myLog1 = log_processor(filename=log1)
myLog2 = log_processor(filename=log2)


fig,ax= plt.subplots(3,sharex=True)

fig.tight_layout()

ax[0].set_title('pressure')
ax[0].grid(True)
ax[0].plot(myLog1.df.timestamp, myLog1.df.pressure_demand, label="P demand")
ax[0].plot(myLog1.df.timestamp, myLog1.df.nozzle_pressure, label="Pn "+ log1_name)
ax[0].plot(myLog2.df.timestamp, myLog2.df.nozzle_pressure, label="Pn "+ log2_name)
ax[0].plot(myLog2.df.timestamp, myLog2.df.manifold_pressure, label="Pman "+ log2_name)

ax[0].legend()



ax[1].set_title('position')
# ax[0].plot(myLog1.df.timestamp, myLog1.df.pos_ref, label="pos_ref")
ax[1].plot(myLog1.df.timestamp, myLog1.df.pos_ref_rate_limited, label="pos_ref rate_limited 1")
ax[1].plot(myLog2.df.timestamp, myLog2.df.pos_ref_rate_limited, label="pos_ref rate_limited 2")
ax[1].plot(myLog1.positionTime, myLog1.valveAngle, label="valveAngle " + log1_name)
# ax[0].plot(myLog1.positionTime, myLog1.valveAngleKalman, label="valveAngleKalman 1")
ax[1].plot(myLog2.positionTime, myLog2.valveAngle, label="valveAngle " + log2_name)
# ax[0].plot(myLog2.positionTime, myLog2.valveAngleKalman, label="valveAngleKalman 2")

ax[1].set_ylabel("deg")
# ax[0].plot(myLog.df.timestamp, myLog.df.angleRaw/13.7, label="angleRaw")

# ax[0].plot(myLog.df.timestamp, myLog.df.valveAngleKalman, label = "kalman")
ax[1].legend()
ax[1].grid(True)
ax[2].set_title('velocity')
ax[2].plot(myLog1.df.timestamp, myLog1.df.speedDemand/6, label="speedDemand " + log1_name)
ax[2].plot(myLog2.df.timestamp, myLog2.df.speedDemand/6, label="speedDemand " + log2_name)
# ax[2].plot(myLog1.df.timestamp, myLog1.df.speed_ref_rate_limited/6, label="speed demand rate_limited")
ax[2].plot(myLog1.positionTime, myLog1.valveVelocity/6, label = "speed feedback " + log1_name)
ax[2].plot(myLog2.positionTime, myLog2.valveVelocity/6, label = "speed feedback " + log2_name)
# ax[2].plot(myLog.positionTime[:-1], np.diff(myLog.valveAngle)*4000/6, label='np.diff')
ax[2].set_ylabel("RPM")
ax[2].legend()
# ax[2].plot(myLog.df.timestamp, myLog.df.encoderButt)
ax[2].grid(True)



# ax[1,1].plot(myLog.positionTime[:-1],np.diff(myLog.valveVelocity)/(1e-1,1/4))
# ax[1,1].set_ylabel("%")
# plt.subplots_adjust(bottom=0.25)
# plt.savefig(filename[:-4]+'.png')
plt.show()
# myLog.safe_csv()
# print(myLog.df.axes)