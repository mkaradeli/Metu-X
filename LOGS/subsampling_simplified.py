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





shifter_mean_array = np.empty(myLog.dataLen)
wasInMiddle = encoderData[0]< (2**16*0.75) and encoderData[0]>(2**16*0.25)
print(f"max = ({max(encoderData)})")
inMiddle = wasInMiddle
shifter = 0
# mean_array = np.empty(myLog.dataLen)

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
	# mean_array[timestamp] = mean
	if mean < (4096*0.75) and mean>(4096*0.25):
		inMiddle = True
	else:
		inMiddle = False
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
		if wasInMiddle:
			if mean < 2048: # entered the first quadrant from the second
				shifter += 1
			else:
				shifter -= 1
	wasInMiddle = inMiddle
	# shifter_array[timestamp] = shifter
	wrappedTicks = mean + shifter * 2048
	rawAngle = wrappedTicks / 4096
	shifter_mean_array[timestamp] = wrappedTicks









fig,ax = plt.subplots(2,sharex=True)
ax0 = ax[0]
ax1 = ax[1]
ax2 = ax[1]
ax0.plot(subSampleTime, encoderData,linewidth=0.5,label="24kHz encoder raw")


ax0.set_ylabel("raw")
ax0.grid(True)
ax2.plot(myLog.df['timestamp'],shifter_mean_array,'.')
ax2.grid(True)
ax2.set_ylabel("duty")
fig.tight_layout()
plt.show()
