import struct
import numpy as np
import pandas as pd
import os.path as path

NORMALIZE_TIMESTAMPS = True

class  log_processor():
	def __init__(self,filename: str) -> None:
		self.filename = filename
		if not path.exists(filename):
			print(f"file '{filename}' doesnt exists.")
			exit()
		self.file = open(file=filename, mode= 'rb')
		formatID = self.file.read(2)
		self.formatID, = struct.unpack('H', formatID)
		
		headerLen = self.file.read(1)
		self.headerLen, = struct.unpack('B', headerLen)


		header = self.file.read(self.headerLen)
		self.header = struct.unpack(f"{self.headerLen}s", header)[0][:-1].decode("utf-8")


		print(f"formatID = {self.formatID}")
		print(self.header)


		self.convertBinary()
		# self.binary = self.file.read()
		self.file.close()

		# self.safe_csv()


		

		


	def printInfo(self)->None:
		print(f"formatID = {self.formatID}")
		print(f"headerLen = {self.headerLen}")
		print(f"header = \"{self.header}\"")
		print(f"data count = {self.dataLen}")
		print(f"legend = {self.columns}")
		# print(f"time range = [{self.df['timestamp'][0]}]")

	def convertBinary(self)-> None:
		if self.formatID == 0:
			self.binary = self.file.read()
			def find_subsampleCount(SUBSAMPLE_COUNT):
				# SUBSAMPLE_COUNT = 256
				self.SUBSAMPLE_COUNT = SUBSAMPLE_COUNT
				self.struct_format = f"<I17f{SUBSAMPLE_COUNT}H{SUBSAMPLE_COUNT}H"

				self.struct_size = struct.calcsize(self.struct_format)
				self.columns = [
					"timestamp",
					"motor_duty",
					"current_measured",
					"current_demand",
					"encoderFront",
					"encoderButt",
					"encoderGeared",
					"vel_measured",
					"vel_demand",
					"motor_pos_kalman",
					"motor_pos_demand",
					"mass_estimation",
					"pressure_manifold",
					"pressure_nozzle",
					"pressure_demand",
					"force_feedback",
					"force_measured",
					"thrust_demand",
					"encoder_48",
					"current_48"
				]
				records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
				records = [[*record[:18], list(record[18:18+SUBSAMPLE_COUNT]), list(record[18+SUBSAMPLE_COUNT:18+2*SUBSAMPLE_COUNT])] for record in records]
				return records
			
			for SUBSAMPLE_COUNT in [48,64,128,256]:
				try:
					records = find_subsampleCount(SUBSAMPLE_COUNT)
					print(f"SUBSAMPLE_COUNT is {SUBSAMPLE_COUNT}")
					break 
				except:
					print(f"SUBSAMPLE_COUNT is not {SUBSAMPLE_COUNT}")
			else:
				print("fuck!")

			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6

			if NORMALIZE_TIMESTAMPS:
				self.df["timestamp"] = np.linspace(0,self.df['timestamp'][self.dataLen-1],self.dataLen)
			
			encoder = np.concat(self.df["encoder_48"].to_numpy())
			current = np.concat(self.df["current_48"].to_numpy())
			subSampleTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3,SUBSAMPLE_COUNT * self.dataLen)
			records = np.transpose(np.array([subSampleTime,encoder,current]))
			self.df_subsample = pd.DataFrame(records, columns=["timestamp", "encoder", "current"])
		elif self.formatID == 1:
			self.binary = self.file.read()
			SUBSAMPLE_COUNT = 24
			self.SUBSAMPLE_COUNT = SUBSAMPLE_COUNT
			self.struct_format = f"<I17f{SUBSAMPLE_COUNT}H{SUBSAMPLE_COUNT}HHxxxxxxd"

			self.struct_size = struct.calcsize(self.struct_format)
			self.columns = [
				"timestamp",
				"motor_duty",
				"current_measured",
				"current_demand",
				"encoderFront",
				"encoderButt",
				"encoderGeared",
				"vel_measured",
				"vel_demand",
				"motor_pos_kalman",
				"motor_pos_demand",
				"mass_estimation",
				"pressure_manifold",
				"pressure_nozzle",
				"pressure_demand",
				"force_feedback",
				"force_measured",
				"thrust_demand",
				"encoder_48",
				"current_48",
				"lastReading",
				"angleRaw"
			]

			print(self.struct_size)
			records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
			records = [[*record[:18], list(record[18:18+24]), list(record[18+24:18+48]), *record[18+48:18+48+2]] for record in records]
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6
			
			encoder = np.concat(self.df["encoder_48"].to_numpy())
			current = np.concat(self.df["current_48"].to_numpy())
			subSampleTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3,SUBSAMPLE_COUNT * self.dataLen)
			records = np.transpose(np.array([subSampleTime,encoder,current]))
			print(records)
			self.df_subsample = pd.DataFrame(records, columns=["timestamp", "encoder", "current"])

		elif self.formatID == 2:
			self.binary = self.file.read()
			self.struct_format = f"<I7fHxx"
			self.struct_size = struct.calcsize(self.struct_format)
			self.columns = [
				"timestamp",
				"motor_duty",
				"current_measured",
				"current_demand",
				"encoderButt",
				"vel_measured",
				"motor_pos_kalman",
				"angleRaw",
				"current_raw"
			]
			records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
			
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6

		elif self.formatID == 3:
			self.binary = self.file.read()
			self.struct_format = f"<I7fHxx3f"
			self.struct_size = struct.calcsize(self.struct_format)
			self.columns = [
				"timestamp",
				"motor_duty",
				"current_measured",
				"current_demand",
				"encoderButt",
				"vel_measured",
				"motor_pos_kalman",
				"angleRaw",
				"current_raw",
				"valveAngleKalman",
    			"valveAngle",
    			"valveVelocity",
			]
			records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
			
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6

		elif self.formatID == 4:
			struct_size = self.file.read(2)
			self.struct_size, = struct.unpack('H', struct_size)

			self.binary = self.file.read()
			self.struct_format = f"<I7fHxx20f"
			if self.struct_size != struct.calcsize(self.struct_format):
				print('struct format is wrowng.')
				print(f'log struct size = {self.struct_size}, calculated struct size = {struct.calcsize(self.struct_format)}')
				exit()
			self.columns = [
				"timestamp",
				"motor_duty",
				"current_measured",
				"current_demand",
				"encoderButt",
				"vel_measured",
				"motor_pos_kalman",
				"angleRaw",
				"current_raw",
				"valveAngleKalman",
    			"valveAngle",
    			"valveVelocity",
    			"current_subsample"
			]

			records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
			records = [[*record[:9], list(record[9:13]), list(record[13:17]), list(record[17:21]), list(record[21:29])] for record in records]
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6

			self.positionTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/4, 4 * self.dataLen)
			self.currentTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/8, 8 * self.dataLen)
			# encoder = np.concat(self.df["encoder_48"].to_numpy())

			self.valveAngleKalman = np.concat(self.df["valveAngleKalman"].to_numpy())
			self.valveAngle = np.concat(self.df["valveAngle"].to_numpy())
			self.valveVelocity = np.concat(self.df["valveVelocity"].to_numpy())
			self.current_subsample = np.concat(self.df["current_subsample"].to_numpy())

		elif self.formatID == 5:
			struct_size = self.file.read(2)
			self.struct_size, = struct.unpack('H', struct_size)

			self.binary = self.file.read()
			self.struct_format = f"<I7fHxx28f"
			if self.struct_size != struct.calcsize(self.struct_format):
				print('struct format is wrowng.')
				print(f'log struct size = {self.struct_size}, calculated struct size = {struct.calcsize(self.struct_format)}')
				exit()
			self.columns = [
				"timestamp",
				"motor_duty",
				"current_measured",
				"current_demand",
				"encoderButt",
				"vel_measured",
				"motor_pos_kalman",
				"angleRaw",
				"current_raw",
				"valveAngleKalman",
    			"valveAngle",
    			"valveVelocity",
    			"current_subsample",
    			"duty_subsample"
			]

			records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
			records = [[*record[:9], list(record[9:13]), list(record[13:17]), list(record[17:21]), list(record[21:29]), list(record[29:29+8])] for record in records]
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6

			self.positionTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/4, 4 * self.dataLen)
			self.currentTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/8, 8 * self.dataLen)
			# encoder = np.concat(self.df["encoder_48"].to_numpy())

			self.valveAngleKalman = np.concat(self.df["valveAngleKalman"].to_numpy())
			self.valveAngle = np.concat(self.df["valveAngle"].to_numpy())
			self.valveVelocity = np.concat(self.df["valveVelocity"].to_numpy())
			self.current_subsample = np.concat(self.df["current_subsample"].to_numpy())
			self.duty_subsample = np.concat(self.df["duty_subsample"].to_numpy())





			# records = np.transpose(np.array([subSampleTime,encoder,current]))
			# self.df_subsample = pd.DataFrame(records, columns=["timestamp", "encoder", "current"])

		elif self.formatID == 6:
			struct_size = self.file.read(2)
			self.struct_size, = struct.unpack('H', struct_size)

			self.binary = self.file.read()
			self.struct_format = f"<I7fHxx30f"
			if self.struct_size != struct.calcsize(self.struct_format):
				print('struct format is wrowng.')
				print(f'log struct size = {self.struct_size}, calculated struct size = {struct.calcsize(self.struct_format)}')
				exit()
			self.columns = [
				"timestamp",
				"motor_duty",
				"current_measured",
				"current_demand",
				"encoderButt",
				"vel_measured",
				"motor_pos_kalman",
				"angleRaw",
				"current_raw",
				"valveAngleKalman",
    			"valveAngle",
    			"valveVelocity",
    			"current_subsample",
    			"duty_subsample",
    			"speedDemand",
    			"pos_ref"
			]

			records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
			records = [[*record[:9], list(record[9:13]), list(record[13:17]), list(record[17:21]), list(record[21:29]), list(record[29:29+8]), record[37], record[38]] for record in records]
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6

			self.positionTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/4, 4 * self.dataLen)
			self.currentTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/8, 8 * self.dataLen)
			# encoder = np.concat(self.df["encoder_48"].to_numpy())

			self.valveAngleKalman = np.concat(self.df["valveAngleKalman"].to_numpy())
			self.valveAngle = np.concat(self.df["valveAngle"].to_numpy())
			self.valveVelocity = np.concat(self.df["valveVelocity"].to_numpy())
			self.current_subsample = np.concat(self.df["current_subsample"].to_numpy())
			self.duty_subsample = np.concat(self.df["duty_subsample"].to_numpy())

			# records = np.transpose(np.array([subSampleTime,encoder,current]))
			# self.df_subsample = pd.DataFrame(records, columns=["timestamp", "encoder", "current"])

		elif self.formatID == 7:
			struct_size = self.file.read(2)
			self.struct_size, = struct.unpack('H', struct_size)

			self.binary = self.file.read()
			self.struct_format = f"<I2f32f"
			if self.struct_size != struct.calcsize(self.struct_format):
				print('struct format is wrowng.')
				print(f'log struct size = {self.struct_size}, calculated struct size = {struct.calcsize(self.struct_format)}')
				exit()
			self.columns = [
				"timestamp",
				"current_measured",
				"current_demand",
				"valveAngleKalman",
    			"valveAngle",
    			"valveVelocity",
    			"current_subsample",
    			"duty_subsample",
    			"speedDemand",
    			"pos_ref",
    			"pos_ref_rate_limited",
    			"speed_ref_rate_limited"
			]


			records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
			records = [[*record[:3], list(record[3:3+4]), list(record[7:7+4]), list(record[11:11+4]), list(record[15:15+8]), list(record[23:23+8]), *record[31:31+4]] for record in records]
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6

			self.positionTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/4, 4 * self.dataLen)
			self.currentTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/8, 8 * self.dataLen)
			# encoder = np.concat(self.df["encoder_48"].to_numpy())

			self.valveAngleKalman = np.concat(self.df["valveAngleKalman"].to_numpy())
			self.valveAngle = np.concat(self.df["valveAngle"].to_numpy())
			self.valveVelocity = np.concat(self.df["valveVelocity"].to_numpy())
			self.current_subsample = np.concat(self.df["current_subsample"].to_numpy())
			self.duty_subsample = np.concat(self.df["duty_subsample"].to_numpy())

			# records = np.transpose(np.array([subSampleTime,encoder,current]))
			# self.df_subsample = pd.DataFrame(records, columns=["timestamp", "encoder", "current"])

		elif self.formatID == 8:
			struct_size = self.file.read(2)
			self.struct_size, = struct.unpack('H', struct_size)

			self.binary = self.file.read()
			self.struct_format = f"<I2f34f"
			if self.struct_size != struct.calcsize(self.struct_format):
				print('struct format is wrowng.')
				print(f'log struct size = {self.struct_size}, calculated struct size = {struct.calcsize(self.struct_format)}')
				exit()
			self.columns = [
				"timestamp",
				"current_measured",
				"current_demand",
				"valveAngleKalman",
    			"valveAngle",
    			"valveVelocity",
    			"current_subsample",
    			"duty_subsample",
    			"speedDemand",
    			"pos_ref",
    			"pos_ref_rate_limited",
    			"speed_ref_rate_limited",
    			"manifold_pressure",
    			"nozzle_pressure"
			]


			records = [struct.unpack(self.struct_format,self.binary[i:i+self.struct_size]) for i in range(0,len(self.binary),self.struct_size)]
			records = [[*record[:3], list(record[3:3+4]), list(record[7:7+4]), list(record[11:11+4]), list(record[15:15+8]), list(record[23:23+8]), *record[31:31+6]] for record in records]
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6

			self.positionTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/4, 4 * self.dataLen)
			self.currentTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3/8, 8 * self.dataLen)
			# encoder = np.concat(self.df["encoder_48"].to_numpy())

			self.valveAngleKalman = np.concatenate(self.df["valveAngleKalman"].to_numpy())
			self.valveAngle = np.concatenate(self.df["valveAngle"].to_numpy())
			self.valveVelocity = np.concatenate(self.df["valveVelocity"].to_numpy())
			self.current_subsample = np.concatenate(self.df["current_subsample"].to_numpy())
			self.duty_subsample = np.concatenate(self.df["duty_subsample"].to_numpy())






			# records = np.transpose(np.array([subSampleTime,encoder,current]))
			# self.df_subsample = pd.DataFrame(records, columns=["timestamp", "encoder", "current"])

		else:
			print("DONT KNOW formatID")
			exit()
		self.safe_csv()

	def safe_csv(self):
		self.df.to_csv(self.filename[:-3] + "csv",index=False)


# filename = 'log0064.bin'

# myLog = log_processor(filename)
