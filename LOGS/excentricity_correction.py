from copy import deepcopy
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from log_processor_lib import log_processor

from matplotlib.widgets import Slider

filename = 'log0054.bin'

myLog = log_processor(filename=filename)

MAX_ADC = 2**16

# print(58490 / 60 * 360 / 1e3)
MAX_SPEED = 10e3 # RPM


max_possible_angle_change = MAX_SPEED / 60 * 360 / 1e3 / 48
print("max_possible_angle_change",max_possible_angle_change)
max_possible_encoder_change = max_possible_angle_change /360 * MAX_ADC
print(max_possible_encoder_change)

# df = myLog.df_subsample

# encoder = df["encoderButt"]
# encoder = df["encoder_48"]
encoder = myLog.df_subsample['encoder']

# print(encoder.shape)
encoder = np.convolve(encoder,np.ones(10)/10,'same')
# print(encoder.shape)
# exit()

# encoder = np.concat(myLog.df["encoder_48"].to_numpy())
# subSampleTime = np.linspace(0,myLog.df['timestamp'][myLog.dataLen-1]+1e-3,myLog.SUBSAMPLE_COUNT * myLog.dataLen)


print(encoder)
# print(encoder)

DATA_LEN = len(encoder)

def calcSpeedFromEncoder(encoder):
	angle_raw = encoder/MAX_ADC * 360
	angle_wrapped = deepcopy(angle_raw)
	angle_wrapped[0]=0


	angle_raw_duplicate = deepcopy(angle_raw)
	angle_raw_duplicate += 360/2
	angle_raw_duplicate %= 360



	old_angle = angle_raw[0]
	old_angle_shifted = angle_raw_duplicate[0]

	middle_count = 0
	middle_count_shifted=0
	use_non_shifted = 1
	effective_angle=[0]
	old_delta = 0
	out_of_bounds = False
	for i in range(1,DATA_LEN):
		middle_count = middle_count+1 if (angle_raw[i]<=270 and angle_raw[i]>=90) else 0
		middle_count_shifted = middle_count_shifted+1 if angle_raw_duplicate[i]<=270 and angle_raw_duplicate[i]>=90 else 0
		if middle_count>=2:
			use_non_shifted = 1
		elif middle_count_shifted>=2:
			use_non_shifted = 0
		if use_non_shifted:
			delta = angle_raw[i] - old_angle
			effective_angle.append(angle_raw[i])
		else:
			delta = angle_raw_duplicate[i] - old_angle_shifted
			effective_angle.append(angle_raw_duplicate[i])
		old_angle = angle_raw[i]
		old_angle_shifted = angle_raw_duplicate[i]
		old_delta = delta


		angle_wrapped[i] = angle_wrapped[i-1] + delta

	speed = deepcopy(angle_raw)
	for i in range(1,DATA_LEN):
		speed[i] = (angle_wrapped[i] - angle_wrapped[i-1])*48e3 /360 *60
	return speed, effective_angle, angle_raw, angle_raw_duplicate

def calcCorrectedSpeed(encoder,amp,phase):
	np_encoder = np.array(encoder)

	corrected_encoder =  np_encoder + amp * np.sin((np_encoder + phase)/2**16 *4*np.pi)
	return calcSpeedFromEncoder(corrected_encoder)


speed, effective_angle, angle_raw, angle_raw_duplicate = calcCorrectedSpeed(encoder,10,0)


fig,ax= plt.subplots(2,sharex=True)
plt.subplots_adjust(bottom=0.25)


(speed_line,) = ax[0].plot(myLog.df_subsample['timestamp'], speed)
ax[0].grid(True)
ax[0].set_ylim([-10e3,10e3])
ax[0].set_title('speed [rpm]')


(angle_raw_line,) = ax[1].plot(myLog.df_subsample['timestamp'], angle_raw, label="nominal")
(angle_raw_dup_line,) = ax[1].plot(myLog.df_subsample['timestamp'], angle_raw_duplicate, label="shifted")
(angle_line,) = ax[1].plot(myLog.df_subsample['timestamp'], effective_angle, '.-', label='active')
ax[1].grid(True)
ax[1].legend()
ax[1].set_title('encoder angle [deg]')

ax[1].set_yticks([0,90,180,270,360])

# (sin_line,) = ax[1].plot(df['timestamp'], 120*np.sin((np.array(encoder) +2019)/4096*4*np.pi)+180)




ax_amp = plt.axes([0.2, 0.15, 0.7, 0.03])   # [left, bottom, width, height]

ax_phase = plt.axes([0.2, 0.08, 0.7, 0.03])
amp0 = 0
phase0 = 2019
slider_amp = Slider(ax_amp, "amp", 0, 400, valinit=amp0)

slider_phase = Slider(ax_phase, "phase", 0, 4096, valinit=phase0)

def update(val):
	amp = slider_amp.val
	phase = slider_phase.val
	speed, effective_angle, angle_raw, angle_raw_duplicate = calcCorrectedSpeed(encoder,amp,phase)
	speed_line.set_ydata(speed)   # update plot
	angle_line.set_ydata(effective_angle)
	angle_raw_line.set_ydata(angle_raw)
	angle_raw_dup_line.set_ydata(angle_raw_duplicate)
	# sin_line.set_ydata(amp*np.sin((np.array(encoder) +phase)/4096*4*np.pi)+180)

	fig.canvas.draw_idle()

slider_amp.on_changed(update)
slider_phase.on_changed(update)
update(1)

# plt.figure(3)
# plt.plot(myLog.df['motor_duty'])
plt.show()

