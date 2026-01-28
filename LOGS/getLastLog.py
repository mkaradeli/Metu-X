import os
import shutil

sdFolder = "/Volumes/NO NAME"
if not os.path.exists(sdFolder):
	sdFolder = "/Volumes/LOG0       "
	if not os.path.exists(sdFolder):
		print("SD bağlı değil.")
		exit()

dirlist = sorted(os.listdir(sdFolder))
logName = ""


for filename in dirlist:
	if "log" in filename and ".bin" in filename:
		logName = filename
# logName = "log0000.bin"

# logName = "log0149.bin"
if logName:
	print(logName)
	shutil.copy(os.path.join(sdFolder,logName), "./")