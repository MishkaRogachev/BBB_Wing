# BBB_Wing
Open souce UAV software project, 

### Dependencies
 
  * C++11 compiler
  * Qt 5.5 (non-gui targets can be build with lower Qt5 versions)
  * CMake 2.8.11
  * ZermoMQ 2
  * libi2c-dev (board only)
  * libqgpsmm-dev (board only)

### Building 
```
mkdir build # you can name build directory whatever you want
cd build
cmake .. -DTARGET_TYPE=<type>
make
```

#### TARGET_TYPE varible can be specified:
 
  * board - UAV software, designed to run on single-board computer like Raspberry Pi, Beaglebone Black or others
  * ground - ground control station with rich graphics interface
  * all - all possible targets, used by default

#### Resulting binaries will be deployed in 'result' folder
