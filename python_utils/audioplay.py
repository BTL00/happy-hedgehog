import numpy as np
from scipy.io import wavfile
from scipy.signal import resample
import sounddevice as sd
import serial

buf_len = 264600/6

int_arr_0 = []
int_arr_1 = []
int_arr_2 = []
int_arr_3 = []

with serial.Serial('/dev/cu.wchusbserial1410', 115200, timeout=1) as ser:
	lines = 0
	line_arr = []
	while lines < buf_len:
		line_arr.append(ser.readline())
		if(lines % 100):
			print lines
		lines += 1

	for line in line_arr:
		line_as_ints = line.split(',',8)
		if(line_as_ints[0] != '' and line_as_ints[1] != ''  and float(line_as_ints[0]) < 400000 and float(line_as_ints[0]) > -400000  and float(line_as_ints[1]) < 400000and float(line_as_ints[1]) > -400000 and float(line_as_ints[2]) < 400000 and float(line_as_ints[2]) > -400000 and float(line_as_ints[3]) < 400000 and float(line_as_ints[3]) >- 400000  and float(line_as_ints[4]) < 400000 and float(line_as_ints[4]) > -400000  and float(line_as_ints[5]) < 400000 and float(line_as_ints[5]) > -400000): #and float(line_as_ints[6]) < 400000 and float(line_as_ints[7]) < 400000):
			int_arr_0.append([ float(line_as_ints[0])/255, float(line_as_ints[1])/255 ] )
			int_arr_1.append([ float(line_as_ints[2])/255, float(line_as_ints[3])/255 ] )
			int_arr_2.append([ float(line_as_ints[4])/255, float(line_as_ints[5])/255 ] )
			#int_arr_3.append([ float(line_as_ints[6])/255, float(line_as_ints[7])/255 ] )


data_resampled_0 = resample(int_arr_0, buf_len)
data_resampled_1 = resample(int_arr_1, buf_len)
data_resampled_2 = resample(int_arr_2, buf_len)
#data_resampled_3 = resample(int_arr_3, buf_len)

print("sound")
wavfile.write("test5_0.wav", 44100, data_resampled_0)
wavfile.write("test5_1.wav", 44100, data_resampled_1)
wavfile.write("test5_2.wav", 44100, data_resampled_2)
#wavfile.write("test5_3.wav", 44100, data_resampled_3)
