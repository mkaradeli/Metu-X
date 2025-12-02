# from os import times
from datetime import time
import matplotlib.pyplot as plt
import numpy as np
# from numpy._core.defchararray import encode

# import log_processor
import log_processor_lib



filename = 'log0010.bin'
filename = 'log0049.bin'
# filename = 'log0064.bin'

myLog = log_processor_lib.log_processor(filename)


CHUNK =119
CHUNK =119
# CHUNK =126

RATIO = 13.7
SUBSAMPLE_COUNT = myLog.SUBSAMPLE_COUNT

encoderData = np.concat(myLog.df["encoder_48"].to_numpy())
currentData = np.concat(myLog.df["current_48"].to_numpy())
# print(myLog.df["encoder_48"][0])
print(type(encoderData))
print(encoderData.shape)
# aa = np.concat(encoderData.to_numpy())



subSampleTime = np.linspace(0,myLog.df['timestamp'][myLog.dataLen-1]+1e-3,SUBSAMPLE_COUNT * myLog.dataLen)

encoderWrapped = np.empty(SUBSAMPLE_COUNT * myLog.dataLen)
encoderEffective = np.empty(myLog.dataLen)
# angle_averaged = np.empty(myLog.dataLen)


normalCounter = 0
shiftedCounter = 0
useNormal = True
wasInMiddle = encoderData[0]< (2**16*0.75) and encoderData[0]>(2**16*0.25)
inMiddle = wasInMiddle
shifter = 0
for timestamp in range(myLog.dataLen):
	encoderBuffer = encoderData[timestamp*SUBSAMPLE_COUNT:timestamp*SUBSAMPLE_COUNT + SUBSAMPLE_COUNT]
	# print(len(encoderData),timestamp*SUBSAMPLE_COUNT, timestamp*SUBSAMPLE_COUNT + SUBSAMPLE_COUNT)
	# print(encoderBuffer)
	middleCounter = 0
	for index in range(SUBSAMPLE_COUNT):
		# print(encoderBuffer.shape)
		# if encoderBuffer.shape == (18,):
			# print(encoderBuffer, timestamp, myLog.dataLen)
		if encoderBuffer[index]< (2**16*0.75) and encoderBuffer[index]>(2**16*0.25):
			middleCounter += 1
		else:
			middleCounter -= 1
	# print(encoderBuffer)
	# if middleCounter < 20 and middleCounter > -20:
	#  	print(middleCounter)
	inMiddle = middleCounter > 0

	if inMiddle:
		encoderEffective[timestamp] = np.average(encoderBuffer)
		if not wasInMiddle:
			if encoderEffective[timestamp] < 2**15: # entered the first quadrant
				shifter += 1
			else:
				shifter -= 1
	else:
		encoderBuffer += 2**15
		encoderBuffer %= 2**16
		encoderEffective[timestamp] = np.average(encoderBuffer)
		if wasInMiddle:
			if encoderEffective[timestamp] > 2**15: # entered the first quadrant from the second
				shifter -= 1
			else:
				shifter += 1
	wasInMiddle = inMiddle
	encoderWrapped[timestamp*SUBSAMPLE_COUNT: timestamp*SUBSAMPLE_COUNT + SUBSAMPLE_COUNT] = encoderBuffer +shifter * 2**15
	# angle_averaged[timestamp] = np.average(encoderBuffer + shifter * 2**15)

# angle = encoderWrapped / 2**16 * 360
# angle_averaged *= 360 / 2**16
# 

# print(encoderEffective.shape, 9999*48)
# print(myLog.df["timestamp"][0], myLog.df["timestamp"][myLog.dataLen-1])
# print(encoderData.shape)
# print(subSampleTime[0], subSampleTime[-1])

# exit()



fig,ax = plt.subplots(3,sharex=True)

# ax[0].vlines(np.arange(0,len(encoderData),SUBSAMPLE_COUNT),0,4096*16,colors='black',linestyles="dashed")
ax[0].plot(subSampleTime, encoderData,linewidth=0.5)
ax[0].vlines(myLog.df['timestamp'], encoderEffective-1e4, encoderEffective+1e4, color='black')
# ax[0].plot(subSampleTime, encoderShifted)

# ax[1].plot(subSampleTime, encoderEffective)


ax[0].set_ylabel("raw")
ax[0].grid(True)
ax[0].plot(myLog.df["timestamp"] - 1e-3/2,encoderEffective,'.',linewidth=0.5)

# ax[1].plot(subSampleTime, encoderWrapped,linewidth=0.5)
# ax[1].grid(True)
# ax[1].set_ylabel('encoderWrapped')

ax[1].plot(subSampleTime, encoderWrapped * 360 / (2**16) ,linewidth=0.5)
ax[1].grid(True)
ax[1].set_ylabel('angle [deg]')

ax[2].plot(myLog.df['timestamp'], myLog.df['motor_duty'])
ax[2].grid(True)
ax[2].set_ylabel("duty")
# ax[2].set_ylabel("angle")
# ax[2].plot(subSampleTime, angle)

# ax[2].plot(myLog.df["timestamp"], angle_averaged,'.')
# ax[2].grid(True)
# ax[1].plot(encoderData,'.')
# ax[1].vlines(np.arange(0,len(encoderData),SUBSAMPLE_COUNT),0,4096*16,colors='black',linestyles="dashed")
# ax[1].set_ylabel("encoder")
# ax[2].plot(angle)
# ax[2].set_ylabel('angle [deg]')
# exit()
# print(subSampleTime.__len__())
# print(encoderData.__len__())
# print('here')
# exit()
data=np.array([subSampleTime,encoderData,currentData, encoderWrapped]).transpose()

df = log_processor_lib.pd.DataFrame(data,columns=["timestamp","encoderData", "currentData", "encoderWrapped"])
df.to_csv(filename[:-4] + "_subSampling.csv",index=False)
fig.tight_layout()
plt.show()
