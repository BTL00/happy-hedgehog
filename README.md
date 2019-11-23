# Happy hedgehog  
This is the code for the student project of sound following toy. Aim of the project was to design and create a code for our prototype a of interactive, voice following toy. Moving toy is characterized by its ability to follow the voice of the kid with the use of 7 microphone array. In our project it is assumed that it will follow the loudest sound, not specific voice command.

## Requirements
## Description
Device was based on the newly created Sipeed platform, exactly on the Maix Bit
module due to the fact that this equipment was created for audio analysis and has
hardware interfaces i2s, dma, and hardware accelerated FFT. For this we have
added DC to DC converter and bridge-H (h-bridge) from Pololu based on Toshiba
chip (TB6612) and a board with 12 addressable diodes and 7 digital i2s
microphones. The final prototype is very easy to use. You basically talk and it comes to you.

**Signal analysis part** is based on the geometrical transformation method. 
![Method](/images/method.png)

**Software algorithm:**
![Algorithm](/images/algorithm.png)
- initialize all 4 I2S channels, stereo -> 7 microphones
i2s_init(I2S_DEVICE_0, I2S_RECEIVER, 0xFF)
- set averages to zero to start
- read the samples of the 7 mics from the rx_buffer
- if only noise is present (a low central microphone output), set all array mic averages to 0. Else subtract the central microphone output from the other array mics, and make sure that their value is between 0 and 512
- move in direction designated by the loudest sound

## Various useful stuff
  ```535  mkdir build && cd build
  536  cmake .. -DTOOLCHAIN=/usr/local/riscv/bin -DPROJ=hello_world
  537  make -j8
  538  ls
  539  python3 ./../isp_auto_dan.py -d /dev/cu.usbserial-* -b 1500000 *.bin
  540  ls /dev/ | grep usb
  541  ls /dev/ | grep wc
  542  ls /dev/
  543  ls /dev/
  544  ls /dev/
  545  python3 ../../isp_auto_dan.py -d /dev/cu.usbserial-1420 -b 1500000 *.bin
  546  python3 ../../isp_auto_dan.py -d /dev/tty.usbserial-1420 -b 1500000 *.bin
  547  python3 ../../isp_auto_dan.py -d /dev/tty.wchusbserial1420 -b 1500000 *.bin
  548  history | tail -n15
  549  history | tail -n15 >> ../README.md
  
  ```
## TODO:
- add multiple buffers
- try with FreeRTOS sdk and more tasks to optimize performanc

## Futher reasearch
Eventually, the project can be considered as a success.All the aims were fulfilled.
The prototype is working. Of course project could be developed furthermore, as was planned at the beginning. App can be attached to control the movement of robot from your phone. We are quite satisfied with the results obtained.  Current state of the prototype is satisfactory, but can be improved in the future.

## Webpage
Additionally we created webpage for our hedgehog http://happyhedgehog.pl/

