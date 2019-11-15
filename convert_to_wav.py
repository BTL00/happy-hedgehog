import numpy as np
from scipy.io import wavfile
from scipy.signal import resample
import sounddevice as sd
import serial
from numpy import linalg as LA

buffer_0 = np.fromfile("./file_channel_0.txt", dtype="int16")

single_channel = buffer_0[0::8]

data_resampled_0 = resample(buffer_0, len(buffer_0))

print("sound")
//wavfile.write("outuput_0.wav", 44100, np.interp(data_resampled_0, (data_resampled_0.min(), data_resampled_0.max()), (-1, +1)))
