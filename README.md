# BBB_Wing
This is an open source UAV software project, which use node-based architecture with one code base to deploy different targets like ground control software, flight controller, recorders, emulators and etc.

### Dependencies
 
  * C++11 compiler
  * Qt 5.5 or greater(no-gui targets can be built with lower Qt5 versions)
  * CMake 2.8.11 or greater
  * ZeroMQ
  * Linux I2C header (board only)
  * GPSD header and development files (board only)
 
#### Ubuntu users can use apt:
```
  sudo apt-get install cmake libzmq-dev libi2c-dev libgps-dev
```

### Building 
```
mkdir build
cd build
cmake .. -DTARGET_TYPE=<type>
make
```

#### TARGET_TYPE varible can be specified with:
 
  * board - UAV software, designed to run on single-board computer like Raspberry Pi, Beaglebone Black or others
  * ground - ground control station with rich graphics interface
  * all - all possible targets, used by default

#### Resulting binaries will be deployed in 'result' folder
