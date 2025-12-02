from copy import deepcopy
import matplotlib.pyplot as plt
from matplotlib import axes, figure
import pandas as pd

MAX_ADC = 4096

# print(58490 / 60 * 360 / 1e3)
MAX_SPEED = 10e3 # RPM

PREDICTIVE_ERROR_CORRECTION = False

max_possible_angle_change = MAX_SPEED / 60 * 360 / 1e3
print("max_possible_angle_change",max_possible_angle_change)
max_possible_encoder_change = max_possible_angle_change /360 * MAX_ADC
# print(max_possible_encoder_change)


filename = 'log0016.csv'
df = pd.read_csv(filename)
print(df)

# crop around 5.76 and 6 seconds
# df = df[(df['timestamp']>5.76) & (df['timestamp'] < 5.82)]
# df = df[(df['timestamp']>2.4) & (df['timestamp'] < 2.6)]
# df =df.reset_index()

encoder = df["encoderButt"]


DATA_LEN = len(encoder)

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
	
	if middle_count>2:
		use_non_shifted = 1
	elif middle_count_shifted>2:
		use_non_shifted = 0


	if use_non_shifted:
		delta = angle_raw[i] - old_angle
		effective_angle.append(angle_raw[i])
	else:
		delta = angle_raw_duplicate[i] - old_angle_shifted
		effective_angle.append(angle_raw_duplicate[i])


	# predict possible angle
	if PREDICTIVE_ERROR_CORRECTION:
		if not out_of_bounds:
			if abs(delta) > max_possible_angle_change:
				effective_angle[-1] += old_delta -delta
				delta = old_delta
				old_angle +=delta
				old_angle_shifted+=delta
				out_of_bounds = True
			else:
				old_angle = angle_raw[i]
				old_angle_shifted = angle_raw_duplicate[i]
				old_delta = delta
		else:
			out_of_bounds=False
			old_angle = angle_raw[i]
			old_angle_shifted = angle_raw_duplicate[i]
			old_delta = delta
			# effective_angle[-1] 
	else:
		# if abs(delta) > max_possible_angle_change:
			# effective_angle[-1] -= delta
			# delta = 0
			# old_angle +=delta
			# old_angle_shifted+=delta
			# out_of_bounds = True
		# else:
			old_angle = angle_raw[i]
			old_angle_shifted = angle_raw_duplicate[i]
			old_delta = delta


	angle_wrapped[i] = angle_wrapped[i-1] + delta



# plt.figure(1)

speed = deepcopy(angle_raw)
for i in range(1,DATA_LEN):
	speed[i] = (angle_wrapped[i] - angle_wrapped[i-1])*1e3


angle_delta = [0]
for i in range(1,DATA_LEN):
	angle_delta.append(angle_wrapped[i]-angle_wrapped[i-1])

accel = [0]
for i in range(1,DATA_LEN):
	accel.append(speed[i] - speed[i-1])
# plt.plot(speed)
# plt.grid(True)
# plt.title("speed [rpm]")


fig,ax= plt.subplots(3,sharex=True)
ax0 :axes.Axes= ax[0]
ax1 : axes.Axes = ax[1]
ax2 : axes.Axes = ax[2]

ax0.plot(df['timestamp'],angle_raw)

ax0.plot(df['timestamp'],angle_raw_duplicate)
ax0.grid(True)
ax0.set_yticks([0,90,180,270,360])
ax0.plot(df['timestamp'],effective_angle, '.-', linewidth=2)
ax0.vlines(2.498,0,360,colors='black')
ax0.set_ylim([-20,380])

ax1.plot(df['timestamp'], speed)
ax1.grid(True)
ax1.set_ylim([-7e3, 7e3])
# ax[1].plot(df['timestamp'], middle_count_array)
# ax[1].plot(df['timestamp'],middle_count_shifted_array)



ax2.plot(df['timestamp'],accel)
ax2.grid(True)
fig.tight_layout()
plt.show()

df["motor_pos_kalman"] = effective_angle
df["vel_measured"] = speed
df.to_csv(filename, index=False)

