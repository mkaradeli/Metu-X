import struct
import numpy as np
import pandas as pd


class log_processor():
	def __init__(self,filename: str) -> None:
		self.filename = filename
		self.file = open(file=filename, mode= 'rb')
		formatID = self.file.read(2)
		self.formatID, = struct.unpack('H', formatID)
		
		headerLen = self.file.read(1)
		self.headerLen, = struct.unpack('B', headerLen)


		header = self.file.read(self.headerLen)
		self.header = struct.unpack(f"{self.headerLen}s", header)[0][:-1].decode("utf-8")

		self.binary = self.file.read()
		self.file.close()

		self.convertBinary()
		self.safe_csv()


		

		


	def printInfo(self)->None:
		print(f"formatID = {self.formatID}")
		print(f"headerLen = {self.headerLen}")
		print(f"header = \"{self.header}\"")
		print(f"data count = {self.dataLen}")
		print(f"legend = {self.columns}")
		# print(f"time range = [{self.df['timestamp'][0]}]")

	def convertBinary(self)-> None:
		if self.formatID == 0:
			SUBSAMPLE_COUNT = 48
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
			records = [[*record[:18], list(record[18:66]), list(record[66:66+48])] for record in records]
			
			self.df = pd.DataFrame(records, columns = self.columns)
			self.dataLen = self.df.__len__()
			self.df["timestamp"] -= self.df["timestamp"][0]
			self.df["timestamp"] *= 1e-6
			
			encoder = np.concat(self.df["encoder_48"].to_numpy())
			current = np.concat(self.df["current_48"].to_numpy())
			subSampleTime = np.linspace(0,self.df['timestamp'][self.dataLen-1]+1e-3,SUBSAMPLE_COUNT * self.dataLen)
			records = np.transpose(np.array([subSampleTime,encoder,current]))
			self.df_subsample = pd.DataFrame(records, columns=["timestamp", "encoder", "current"])


			
			
	def safe_csv(self):
		self.df.to_csv(self.filename[:-3] + "csv",index=False)


# filename = 'log0064.bin'

# myLog = log_processor(filename)
