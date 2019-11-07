Happy hedgehog  535  mkdir build && cd build
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
