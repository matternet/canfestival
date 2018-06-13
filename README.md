## Installing CANfestival for the Beaglebone Black
```
~$ git clone https://github.com/matternet/canfestival.git
~$ cd canfestival
~/canfestival$ ./configure --can=socket --timers=unix --wx=0 --arch=armv7l 
~/canfestival$ make canfestival
~/canfestival$ sudo make install
```
