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
# filename = 'log1260.bin'
if len(sys.argv) == 2:
	filename = sys.argv[1]
print(filename)
filename = "live_atis.BIN"
# myLog = log_processor(filename=filename)
# print(myLog.df.axes)
# test = pd.DataFrame([])

# print( test._dir_())
# exit()
# print(myLog.df.)
# aaa = np.diff(myLog.df.angleRaw, append=[myLog.df.angleRaw[myLog.dataLen-1]])

# for filename in dirlist:
# 	if "log" in filename and ".bin" in filename:
# 		print(filename)
# 		try:
myLog = log_processor(filename)

CD = [0.1699, 0.1723, 0.1730, 0.1763]
for i in range(4):
	myLog.df[f"F_estimate_{i}"] = CD[i] * myLog.df[f"nozzle_pressure_{i}"]




fig,ax= plt.subplots(4,4,sharex=True)
fig.canvas.manager.set_window_title(filename)

fig.tight_layout()

for i in range(4):
	ax[0][i].grid(True)
	ax[0][i].set_title(f"Nozzle Pressure {i}")

	ax[0][i].plot(myLog.df["timestamp"], myLog.df[f"nozzle_pressure_{i}"], label="Nozzle Pressure")
	ax[0][i].plot(myLog.df.timestamp, myLog.df[f"pressure_demand_{i}"], label=f"Nozzle Demand")
	ax[0][i].set_ylabel('Nozzle Pressure [Psi]')
	ax[0][i].legend()
	# ax[0][i].set_xlim(0,60)
	# ax[0][i].set_ylim(-10,4500)

  

	ax[1][i].set_title(f'Valve Position {i}')
	ax[1][i].plot(myLog.df.timestamp, myLog.df[f"pos_ref_{i}"], label="Position Referance")
	ax[1][i].plot(myLog.df.timestamp, myLog.df[f"valveAngle_{i}"], label="Position Feedback")
	# ax[1][i].set_ylim(-100,2000)

	ax[1][i].set_ylabel("Valve Angle [deg]")
	ax[1][i].legend()
	ax[1][i].grid(True)

	ax[2][i].plot(myLog.df.timestamp, myLog.df[f"current_demand_{i}"], label = "demand")
	ax[2][i].plot(myLog.df.timestamp, myLog.df[f"current_measured_{i}"], label="measured")
	ax[2][i].grid(True)
	ax[2][i].set_ylabel("current [A]")

	ax[3][i].plot(myLog.df.timestamp, myLog.df[f"F_estimate_{i}"], label="F_estimate")
	ax[3][i].grid(True)
	ax[3][i].set_ylabel("F_estimate [N]")
	ax[3][i].set_xlabel("time [s]")
	ax[3][i].legend()


# ax[3].set_ylim(0,600)
plt.savefig(filename[:-4]+'.png')

fig2,ax2= plt.subplots(1,sharex=True)
fig2.canvas.manager.set_window_title(filename+" manifold")

fig2.tight_layout()

ax2.grid(True)
ax2.set_title('Manifold Pressure')
ax2.plot(myLog.df.timestamp, myLog.df.manifold_pressure, label="Manifold Pressure")
ax2.set_ylabel('Manifold Pressure [Psi]')
ax2.set_xlabel("time [s]")
ax2.legend()

fig3,ax3= plt.subplots(3,sharex=True)
fig3.canvas.manager.set_window_title(filename+" overlay")

fig3.tight_layout()

for i in range(4):
	ax3[0].plot(myLog.df.timestamp, myLog.df[f"nozzle_pressure_{i}"], label=f"Nozzle Pressure {i}")
	ax3[0].plot(myLog.df.timestamp, myLog.df[f"pressure_demand_{i}"], label=f"Nozzle Demand {i}")

	ax3[1].plot(myLog.df.timestamp, myLog.df[f"valveAngle_{i}"], label=f"Position Feedback {i}")
	ax3[2].plot(myLog.df.timestamp, myLog.df[f"current_measured_{i}"], label=f"Current {i}")

ax3[0].grid(True)
ax3[0].set_title("Nozzle Pressure")
ax3[0].set_ylabel('Nozzle Pressure [Psi]')
ax3[0].legend()

ax3[1].grid(True)
ax3[1].set_title('Valve Position')
ax3[1].set_ylabel("Valve Angle [deg]")
ax3[1].legend()

ax3[2].grid(True)
ax3[2].set_title('Current')
ax3[2].set_ylabel("current [A]")
ax3[2].set_xlabel("time [s]")
ax3[2].legend()

## Kf altitude
fig4,ax4= plt.subplots(2,sharex=True)
fig4.canvas.manager.set_window_title(filename+" kf_altitude")

fig4.tight_layout()

ax4[0].grid(True)
ax4[0].set_title('kf_altitude')
# ax4.subplots(2)
ax4[0].plot(myLog.df.timestamp, myLog.df.kf_altitude, label="kf_altitude")
ax4[0].set_ylabel('kf_altitude (m) bro')
ax4[0].set_xlabel("time [s]")
ax4[0].legend()

## kf_velocity
# fig5,ax5= plt.subplots(1,sharex=True)
# fig5.canvas.manager.set_window_title(filename+" kf_velocity")

# fig5.tight_layout()

ax4[1].grid(True)
ax4[1].set_title('kf_velocity')
ax4[1].plot(myLog.df.timestamp, myLog.df.kf_velocity, label="kf_velocity")
ax4[1].set_ylabel('kf_velocity (m/s) bro')
ax4[1].set_xlabel("time [s]")
ax4[1].legend()


## Thrust_demand 4lu
fig6,ax6= plt.subplots(1,sharex=True)
fig6.canvas.manager.set_window_title(filename+" thrust_demand 4lu")

fig6.tight_layout()

for i in range(4):
	ax6.plot(myLog.df.timestamp, myLog.df[f"thrust_demand_{i}"], label=f"Thrust Demand {i}")

ax6.grid(True)
ax6.set_title("Thrust Demand")
ax6.set_xlabel("Time (s)")
ax6.set_ylabel('Thrust Demand (N)')
ax6.legend()

## Thrust_demand 4lu
## kf_velocity

'''
fig7,ax7= plt.subplots(1,sharex=True)
fig7.canvas.manager.set_window_title(filename+" MODES")

fig7.tight_layout()

ax7.grid(True)
ax7.set_title('MODES')

ax7.plot(myLog.df.timestamp, myLog.df.actuator_mode, label="actuator_mode") # DISABLED, DUTY, CURRENT, ... FORCE
ax7.plot(myLog.df.timestamp, myLog.df.mission_modes, label="mission_modes") # TF_OPEN, TF_CLOSE,  TF_FULL, DISCHARGE, HOVER, DROP
ax7.plot(myLog.df.timestamp, myLog.df.system_modes, label="system_modes")

ax7.set_ylabel('Mod indexleri')
ax7.set_xlabel("Zaman [s] bro")
ax7.legend()
'''

fig7,ax7= plt.subplots(1,sharex=True)
fig7.canvas.manager.set_window_title(filename+" F_estimated 4lü üst üste")

fig7.tight_layout()

ax7.grid(True)
ax7.set_title('F_estimated')

ax7.plot(myLog.df.timestamp, myLog.df[f"F_estimate_{0}"], label="F_estimated 0")
ax7.plot(myLog.df.timestamp, myLog.df[f"F_estimate_{1}"], label="F_estimated 1")
ax7.plot(myLog.df.timestamp, myLog.df[f"F_estimate_{2}"], label="F_estimated 2")
ax7.plot(myLog.df.timestamp, myLog.df[f"F_estimate_{3}"], label="F_estimated 3")

ax7.set_xlabel("Time (s)")
ax7.set_ylabel('Thrust Estimated (N)')

ax7.legend()

#############

fig8,ax8= plt.subplots(1,sharex=True)
fig8.canvas.manager.set_window_title(filename+" HWIL Simulasyon")

fig8.tight_layout()

ax8.grid(True)
ax8.set_title('acceleration')

ax8.plot(myLog.df.timestamp, myLog.df.linAccel_x , label="Accel X")
ax8.plot(myLog.df.timestamp, myLog.df.linAccel_y , label="Accel Y")
ax8.plot(myLog.df.timestamp, myLog.df.linAccel_z , label="Accel Z")

ax8.set_xlabel("Time (s)")
ax8.set_ylabel('accel [m/s2]')

ax8.legend()

'''
enum class system_modes
  : int32_T {
  IDLE = 0,                 // Default value
  TESTFIRE = 1,
  HOVER = 2,
  DROP = 3,
  SHUTDOWN = 4,
  FAULT = 5,
  ARMED = 6,                // logging, actuators cold, waiting for safety pin
  SAFE_DISCHARGE = 7
'''


fig9,ax9= plt.subplots(1,sharex=True)
fig9.canvas.manager.set_window_title(filename+" F_estimated 4lü üst üste")

fig9.tight_layout()

ax9.grid(True)
ax9.set_title('Quaternion')

ax9.plot(myLog.df.timestamp, myLog.df.quaternion_i , label="i")
ax9.plot(myLog.df.timestamp, myLog.df.quaternion_j, label="j")
ax9.plot(myLog.df.timestamp, myLog.df.quaternion_k, label="k")
ax9.plot(myLog.df.timestamp, myLog.df.quaternion_r, label="r")

qx = myLog.df.quaternion_i
qy = myLog.df.quaternion_j
qz = myLog.df.quaternion_k
qw = myLog.df.quaternion_r

pi = np.arctan2(1, 1) * 4
roll = np.arctan2(2 * (qw * qx + qy * qz), 1 - 2 * (qx * qx + qy * qy))
pitch = np.arcsin(2 * (qw * qy - qz * qx))  #- pi + 2 * np.arctan2(np.sqrt(1 + 2 * (qw * qy - qx * qz)), np.sqrt(1 - 2 * (qw * qy - qx * qz)))
yaw = np.arctan2(2 * (qw * qz + qx * qy), 1 - 2 * (qy * qy + qz * qz))

ax9.set_xlabel("Time (s)")
ax9.set_ylabel('Quat')

ax9.legend()

fig10,ax10= plt.subplots(1,sharex=True)
fig10.canvas.manager.set_window_title(filename+" F_estimated 4lü üst üste")

fig10.tight_layout()

ax10.grid(True)
ax10.set_title('eulers')

ax10.plot(myLog.df.timestamp, roll / pi * 180, label="roll")
ax10.plot(myLog.df.timestamp, pitch / pi * 180, label="pitch")
# ax10.plot(myLog.df.timestamp, yaw / pi * 180, label="yaw")

ax10.set_xlabel("Time (s)")
ax10.set_ylabel('euler [deg]')

ax10.legend()

# Plotu atesle

fig11,ax11= plt.subplots(2,sharex=True)
fig11.canvas.manager.set_window_title(filename+" F_estimated 4lü üst üste")
ax11[0].plot(myLog.df.timestamp, myLog.df.angular_velocity_demand_x, label = "velocity_demand_x")
ax11[0].plot(myLog.df.timestamp, myLog.df.angular_velocity_x, label = "velocity_x")
ax11[0].legend()
ax11[0].grid(True)

ax11[1].plot(myLog.df.timestamp, myLog.df.angular_velocity_demand_y, label = "velocity_demand_y")
ax11[1].plot(myLog.df.timestamp, myLog.df.angular_velocity_y, label = "velocity_y")
ax11[1].legend()
ax11[1].grid(True)

# ax11[2].plot(myLog.df.timestamp, myLog.df.angular_velocity_demand_z, label = "velocity_demand_z")
# ax11[2].plot(myLog.df.timestamp, myLog.df.angular_velocity_z, label = "velocity_z")
# ax11[2].legend()

plt.show()
plt.figure()
plt.plot(1e3*np.diff(myLog.df.timestamp),'.')
plt.ylabel("entry period [ms]")
plt.xlabel("entry id")
plt.grid(1)
#plt.show()
print(f"logging period std= {np.std(1e6*np.diff(myLog.df.timestamp)):.3} us")
print(f"logging period mean= 1.0 ms + {-1000+np.mean(1e6*np.diff(myLog.df.timestamp))} us")

print(myLog.struct_size)
# plt.show()
		# except:
		# 	continue

# print(myLog.df["manifold_pressure"][0])

# print(myLog.df.axes)
