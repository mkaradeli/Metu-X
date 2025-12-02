import matplotlib.pyplot as plt
import struct

filename = 'log0005.bin'

'''
    uint32_t timestamp;								4
    sh2_RotationVector_t quaternion;				4*4
    float motor_pos_kalman[4];						4*4
    float motor_pos_demand[4];						4*4
    float force_feedback[4];						4*4
    float mass_estimation;							4
    float thrust_demand[4];							4*4
    float platform_controller_demand[3];			3*4
    float lidar_raw;								4
    float lidar_strength;							4
    float pressure[5];								4*5
    float accels[3];								4*3
    float height_kalman;							4
    float velocity_kalman;							4
    total 148 bytes
    '''

class entry:
	def __init__(self, entry: bytes) -> None:
		self.timestamp = int.from_bytes(entry[0:4],byteorder='little') 
		self.quaternion = [int.from_bytes(entry[i*4:i*4+4],byteorder='little') for i in range(1,5)]
		self.motor_pos_kalman = struct.unpack('<ffff',entry[5*4 : 8*4 + 4])
		self.motor_pos_demand = [int.from_bytes(entry[i*4 : i*4 + 4], byteorder='little') for i in range(9,13)]
		self.force_feedback = [int.from_bytes(entry[i*4 : i*4 + 4], byteorder='little') for i in range(13,17)]
		self.mass_estimation = int.from_bytes(entry[17*4 : 17*4 + 4], byteorder='little')
		self.thrust_demand = [int.from_bytes(entry[i*4 : i*4 + 4], byteorder='little') for i in range(18,22)]
		self.platform_controller_demand = [int.from_bytes(entry[i*4 : i*4 + 4], byteorder='little') for i in range(22,25)]

		self.lidar_raw = struct.unpack('<f', entry[25*4 : 25*4 + 4])[0]
		self.lidar_strength = int.from_bytes(entry[26*4 : 26*4 + 4], byteorder='little')
		self.pressure = [int.from_bytes(entry[i*4 : i*4 + 4], byteorder='little') for i in range(27,32)]
		self.accels = [int.from_bytes(entry[i*4 : i*4 + 4], byteorder='little') for i in range(32,35)]
		self.height_kalman = int.from_bytes(entry[35*4 : 35*4 + 4], byteorder='little')
		self.velocity_kalman = int.from_bytes(entry[36*4 : 36*4 + 4], byteorder='little')
		return	
	def __repr__(self) -> str:
		return str([
			self.timestamp,
			self.motor_pos_kalman,
			self.lidar_raw])
	def get_current(self) -> float:
		return (self.lidar_raw -2048) /4096 * 3.3 / 0.066

currents=[]
angle = []
with open(file=filename, mode='rb') as f:
	for _ in range(10000):
		data = entry(f.read(148))
		currents.append(data.get_current())
		# print(data.get_current())
		angle.append(data.motor_pos_kalman[0])



print(currents[-5:-1])
plt.figure()
plt.plot(currents)
# plt.figure()
# plt.plot(angle)
plt.show()