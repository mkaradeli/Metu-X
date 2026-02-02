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
# filename = 'log0245.bin'
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





fig,ax= plt.subplots(2,sharex=True)
# fig.canvas.manager.set_window_title(filename) 

fig.tight_layout()



ax[0].grid(True)
ax[0].plot(myLog.currentTime, myLog.current_subsample, label='current feedback')
ax[0].plot(myLog.df.timestamp, myLog.df.current_demand, label= "current demand")
ax[0].set_ylabel("A")
ax[0].legend()
# ax[0].set_yticks(np.arange(-10,10,1))

ax[1].grid(True)
ax[1].plot(myLog.currentTime, myLog.duty_subsample*100)
# ax[1].plot(myLog.positionTime[:-1],np.diff(myLog.valveVelocity)/(1e-1/4))
ax[1].set_ylabel("%")
# plt.subplots_adjust(bottom=0.25)
plt.savefig(filename[:-4]+'.png')
plt.show()
myLog.safe_csv()
print(myLog.df.axes)