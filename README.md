# Happy hedgehog  
This is the code for the student project of sound following toy. 

## Requirements
## Description
Device was based on the newly created Sipeed platform, exactly on the Maix Bit
module due to the fact that this equipment was created for audio analysis and has
hardware interfaces i2s, dma, and hardware accelerated FFT. For this we have
added DC to DC converter and bridge-H (h-bridge) from Pololu based on Toshiba
chip (TB6612) and a board with 12 addressable diodes and 7 digital i2s
microphones. The final prototype is very easy to use. You basically talk and it comes to you.

Signal analysis part is based on the geometrical transformation method. 
![Test Image 2]("method.png")

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
