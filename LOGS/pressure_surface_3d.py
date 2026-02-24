# from copy import deepcopy
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from log_processor_lib import log_processor
import os
from os import path

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

filename = "log0299.bin"
filename = "log0396.bin"

ax = plt.figure().add_subplot(projection='3d')
fig = plt.gcf()

# fig.canvas.manager.set_window_title(filename) 

# fig.tight_layout()

# valid_file_list = []
# for i in range(299, 400):
# 	filename = f"log0{i}.bin"

if path.exists(filename):
	myLog = log_processor(filename=filename)
	
	# valid_file_list.append(filename)
	color = np.abs(myLog.df_4kHz["valveVelocity"].to_numpy()[::4])
	ax.scatter(myLog.df_4kHz["valveAngle"][::4], myLog.df["manifold_pressure"], myLog.df["nozzle_pressure"],'.',c=color,cmap='viridis')

# print(valid_file_list)


ax.set_xlabel("valveAngle")
ax.set_ylabel("Pmanifold")
ax.set_zlabel("Pnozzle")


plt.show()