from json import encoder
import matplotlib.pyplot as plt
import numpy as np

import log_processor_lib



filename = 'log0010.bin'
filename = 'log0054.bin'
filename = 'log0064.bin'

myLog = log_processor_lib.log_processor(filename)



df = myLog.df
dataLen = myLog.dataLen
SUBSAMPLE_COUNT = myLog.SUBSAMPLE_COUNT

encoderData = np.empty(dataLen*SUBSAMPLE_COUNT)
currentData = np.empty(dataLen*SUBSAMPLE_COUNT)

for timestep in range(dataLen):
	for subSampleId in range(SUBSAMPLE_COUNT):
		encoderData[SUBSAMPLE_COUNT * timestep + subSampleId] = df[f"encoder_{subSampleId}"][timestep]
		currentData[SUBSAMPLE_COUNT * timestep + subSampleId] = df[f"current_{subSampleId}"][timestep]
encoderData *= 360 / 2**16

# exit()
fig,ax = plt.subplots(3,sharex=True)

ax[0].vlines(np.arange(0,len(encoderData),SUBSAMPLE_COUNT),0,4096*16,colors='black',linestyles="dashed")
ax[0].plot(currentData,'.')
ax[0].set_ylabel("current")
ax[1].plot(encoderData,'.')
# ax[1].vlines(np.arange(0,len(encoderData),SUBSAMPLE_COUNT),0,4096*16,colors='black',linestyles="dashed")
ax[1].set_ylabel("encoder")
ax[1].set_yticks([0,90,180,270,360])
ax[1].grid(True)
ax[2].plot(np.arange(0,len(encoderData),SUBSAMPLE_COUNT),df["motor_duty"])  
ax[2].set_ylabel("duty")
# plt.figure(2)
# plt.plot(df["motor_duty"])
# plt.plot(df["encoder_1"])

plt.show()
