#remove every
import numpy as np
buffer_0 = np.fromfile("./file_hex.txt", dtype="uint32")
buffer_1 = np.zeros(buffer_0.shape, dtype="int16")

for i in buffer_0:
	buffer_1 = 
