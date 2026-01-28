# from os import times
from copy import deepcopy
from datetime import time
# from datetime import time
# from os import times
# from matplotlib.lines import lineStyles
import matplotlib.pyplot as plt
import numpy as np
# from numpy._core.defchararray import encode
# from numpy._core.defchararray import encode

# import log_processor
import log_processor_lib



filename = 'log0010.bin'
filename = 'log0053.bin'
filename = 'log0053.bin'
filename = 'log0042.bin'

numberForStability = 4
tickLimitForStability = 100

myLog = log_processor_lib.log_processor(filename)

print(myLog.df["timestamp"])
print(myLog.dataLen)

CHUNK =119
CHUNK =119
# CHUNK =126

RATIO = 13.7
SUBSAMPLE_COUNT = myLog.SUBSAMPLE_COUNT

encoderData = np.concat(myLog.df["encoder_48"].to_numpy())
currentData = np.concat(myLog.df["current_48"].to_numpy())



subSampleTime = np.linspace(-1e-3,myLog.df['timestamp'][myLog.dataLen-1],SUBSAMPLE_COUNT * (myLog.dataLen))


encoderWrapped = np.empty(SUBSAMPLE_COUNT * myLog.dataLen)
encoderEffective = np.empty(myLog.dataLen)
encoderDelta = np.empty(myLog.dataLen)
shifter_array = np.empty(myLog.dataLen)
inMiddle_array = np.empty(myLog.dataLen)
shifter_mean_array = np.empty(myLog.dataLen)
# angle_averaged = np.empty(myLog.dataLen)


normalCounter = 0
shiftedCounter = 0
useNormal = True
wasInMiddle = encoderData[0]< (2**16*0.75) and encoderData[0]>(2**16*0.25)
print(f"max = ({max(encoderData)})")
inMiddle = wasInMiddle
shifter = 0
mean_array = np.empty(myLog.dataLen)

totalNonStableCount = 0
for timestamp in range(myLog.dataLen):
	nonStableCount = 0
	encoderBuffer = deepcopy(encoderData[timestamp*SUBSAMPLE_COUNT:timestamp*SUBSAMPLE_COUNT + SUBSAMPLE_COUNT])
	
	index = SUBSAMPLE_COUNT - numberForStability
	for index in np.arange(SUBSAMPLE_COUNT - numberForStability, 0, - numberForStability):
		subBuffer = encoderBuffer[index:index+numberForStability]

		if max(subBuffer) - min(subBuffer) < tickLimitForStability:
			break

		nonStableCount +=1
		totalNonStableCount += 1
		print(f"nonStableCount {nonStableCount } {totalNonStableCount}. timestamp = {timestamp}")
		# index -= numberForStability
	else:
		print('aaaaaaaaaaaaaaaaaaa')
		subBuffer = encoderBuffer[SUBSAMPLE_COUNT - numberForStability:SUBSAMPLE_COUNT]
		break


	mean = np.average(subBuffer)
	mean_array[timestamp] = mean
	if mean < (4096*0.75) and mean>(4096*0.25):
		inMiddle = True
	else:
		inMiddle = False

	# inMiddle_array[timestamp] = inMiddle


	if inMiddle:
		# mean = np.average(encoderBuffer)
		if not wasInMiddle:
			if mean < 2048: # entered the first quadrant
				shifter += 1
			else:
				shifter -= 1
	else:
		mean += 2048
		mean %= 4096
		# mean = np.average(mean)
		if wasInMiddle:
			if mean < 2048: # entered the first quadrant from the second
				shifter += 1
			else:
				shifter -= 1
	# encoderDelta[timestamp] = max(encoderBuffer) - min(encoderBuffer)
	wasInMiddle = inMiddle
	shifter_array[timestamp] = shifter
	shifter_mean_array[timestamp] = mean + shifter * 2048
	if inMiddle:
		encoderWrapped[timestamp*SUBSAMPLE_COUNT: timestamp*SUBSAMPLE_COUNT + SUBSAMPLE_COUNT] = encoderBuffer +shifter * 2048
	else:
		encoderWrapped[timestamp*SUBSAMPLE_COUNT: timestamp*SUBSAMPLE_COUNT + SUBSAMPLE_COUNT] = (encoderBuffer+2048)%4096 +shifter * 2048




fig,ax = plt.subplots(2,sharex=True)
ax0 = ax[0]
ax1 = ax[1]
ax2 = ax[1]
# print(len(subSampleTime))
# print(len(encoderData))
# ax0.vlines(myLog.df['timestamp'],0,4096,colors='black',linestyles="dashed")
ax0.plot(subSampleTime, encoderData,linewidth=0.5,label="24kHz encoder raw")
# ax0.vlines(myLog.df['timestamp'], encoderEffective-1e4, encoderEffective+1e4, color='black')
# ax0.plot(subSampleTime, encoderShifted)

# ax[1].plot(subSampleTime, encoderEffective)


ax0.set_ylabel("raw")
ax0.grid(True)
ax1.plot(subSampleTime, encoderWrapped)
ax2.plot(myLog.df['timestamp'],shifter_mean_array,'.')
ax2.grid(True)
ax2.set_ylabel("duty")
data=np.array([subSampleTime,encoderData,currentData, encoderWrapped]).transpose()

myLog.safe_csv()
df = log_processor_lib.pd.DataFrame(data,columns=["timestamp","encoderData", "currentData", "encoderWrapped"])
df.to_csv(filename[:-4] + "_subSampling.csv",index=False)
fig.tight_layout()
plt.show()
