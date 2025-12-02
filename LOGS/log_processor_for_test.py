import matplotlib.pyplot as plt
import struct
from numpy import pi
import pandas as pd
import log_processor_lib


# from numpy import timedelta64

filename = 'log0010.bin'
filename = 'log0049.bin'


myLog = log_processor_lib.log_processor(filename)
df = myLog.df

# print(df)
# df["timestamp"] -= df["timestamp"][0]
# df["timestamp"] /= 1e6

# df["current_measured"] -= df["current_measured"][0]
# df["current_measured"] *= -1


fig, ax = plt.subplots(3,sharex=True)
# fig.tight_layout()
fig.suptitle(filename)

# ax[0].set_title('test')
ax[0].plot(df["timestamp"],df["motor_duty"])
ax[0].grid(1)
ax[0].set(ylabel="duty")

ax[1].plot(myLog.df_subsample["timestamp"],(myLog.df_subsample["current"]*(3.3/(2**16))-2.5)/0.066, linewidth=1)
ax[1].grid(1)

# ax[1].set_yticks(log_processor_lib.np.arange(-30,40,10))
ax[1].set(ylabel="current [A]")
ax[2].plot(df["timestamp"],df["motor_pos_kalman"]/360*2*pi)
ax[2].grid(True)
ax[2].set(ylabel="motor angle [rad]")
fig.tight_layout()
# ax.get_shared_x_axes()
# plt.figure()
# plt.plot(df['timestamp'],df['encoderButt'], '.')


df.to_csv(filename[:-3]+"csv", index=False)
fig.savefig(filename[:-3]+"png")

plt.show()