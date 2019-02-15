## Setup instructions for using Arduino IDE

1. Install [Arduino IDE](https://www.arduino.cc/en/Main/Software)

Download, extract and run `./install.sh`

This will just install arduino and setup links to the current directory. 

So you should put it someplace useful

2. Run Arduino software 

3. Download and install [Teensyduino](https://www.pjrc.com/teensy/td_download.html)

You'll download a file and need to set the executable bit 

~~~
chmod +x TeensyduinoInstall.linux64
~~~

4. Run Arduino and select Teensy 3.5 from Tools > Board

5. Open a sketch and upload such as File > Examples > Digital > Blink LED

6. Now can use Arduino to verify and upload sketches once a sketch is already running

We just need Teensyduino so we can copy the `<ARDUINOPATH>/hardware/tools` path

`<ARDUINOPATH>/hardware/tools/arm/bin`

## Teensy Loader Command Line 

* [Source](https://www.pjrc.com/teensy/loader_cli.html) and a submodule

1. Edit the Makefile to select the correct OS
2. Install libusb

~~~
brew install libusb-compat
sudo apt-get install libusb-dev
~~~

3. Copy the udev rule on linux

~~~
sudo cp tools/49-teensy.rules /etc/udev/rules.d
~~~

Then unplug and plug in the teensy

3. Call `make` to build the teensy_loader_cli

~~~
cd teensy_loader_cli
make
~~~

4. Upload a compiled hex file

~~~
teensy_loader_cli --mcu=mk64fx512 -w <name of nex>.hex
~~~

## Example [makefile](https://github.com/PaulStoffregen/cores/blob/master/teensy3/Makefile)

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
