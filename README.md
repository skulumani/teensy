## Setup instructions

1. Install [Arduino IDE](https://www.arduino.cc/en/Main/Software)
2. Run Arduino software 
3. Download and install [Teensyduino](https://www.pjrc.com/teensy/td_download.html)
4. Run Arduino and select Teensy 3.5 from Tools > Board
5. Open a sketch and upload such as File > Examples > Digital > Blink LED
6. Now can use Arduino to verify and upload sketches once a sketch is already running

## Teensy Loader Command Line 

* [Source](https://www.pjrc.com/teensy/loader_cli.html) and a submodule

1. Edit the Makefile to select the correct OS
2. Install libusb

~~~
brew install libusb-compat
sudo apt-get install libusb-dev
~~~
3. Call `make` to build the teensy_loader_cli

## AVR Compiler

1. MacOSX

~~~
brew tap osx-cross/avr
brew install avr-gcc
~~~

## Guides

* [Teensy Guide](https://www.pjrc.com/teensy/td_download.html)
* [Teensy Template](https://github.com/apmorton/teensy-template)
* [Teensyduino](https://www.pjrc.com/teensy/td_download.html)
* [Teensy Core](https://github.com/PaulStoffregen/cores)
* [Setup AVR](http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/)
* [Embedded AVR](http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/)
* [Arduino Makefile](https://github.com/sudar/Arduino-Makefile)
* [PlatformIO](https://github.com/platformio/platformio-core/)
