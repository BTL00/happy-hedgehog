#remove every
import numpy as np
buffer_0 = np.fromfile("./file_hex.txt", dtype="uint32")
buffer_1 = np.zeros(buffer_0.shape, dtype="int16")
