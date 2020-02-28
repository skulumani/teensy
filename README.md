# Teensy

Instructions are here for both using the Arduino IDE or make and the AVR toolchain.

## TODO

* [x] Update teensy3 library and tools from the Arduino installation
* ~~* Add more examples~~
* ~~* Script to download ARM compiler tools from website~~
* ~~* Get teensy core code as a submodule~~
* Use makefile example to build simple setup script and use teensy_loader_cli to push to board
* [x] Get MPU9250 library installed and working
* [ ] Fix MPU9250.h to initialize the bias/scale factor variables (around line 169)
* [ ] Calibrate IMU 
* [ ] Create IMU wrapper class to interface with MPU9250 and rotate outputs to match breakboard diagram
* [ ] Test code to read at 1000Hz
* [ ] AHRS

## SPI Wiring for MPU 9250

Numbers correspond to pin out diagram - NOT location on board

* SCK - Clock pin 13 
* MOSI - pin 11
* MISO - pin 12
* SS - default is usually pin 10 but you can select any digital IO pin

Connecting to 9250

* NCS => SS Pin 10
* SDA -> MOSI  pin 11
* ADO -> MISO pin 12
* SCL -> SCK pin 13
* VCC -> 3.3V Pin 3
* GND -> GND 

9250 Pins

~~~
VDD: this should be a 2.4V to 3.6V power source.
GND: ground.
VDDI: digital I/O supply voltage. This should be between 1.71V and VDD.
FSYNC: not used, should be grounded.
INT: (optional) used for the interrupt output setup in enableDataReadyInterrupt and enableWakeOnMotion. Connect to interruptable pin on microcontroller.
SDA / SDI: connect to MOSI.
SCL / SCLK: connect to SCK.
AD0 / SDO: connect to MISO.
nCS: connect to chip select pin. Pin 10 was used in the code snippets in this document and the included examples, but any digital I/O pin can be used.
AUXDA: not used.
AUXCL: not used.
~~~

* [SPI Library](https://www.pjrc.com/teensy/td_libs_SPI.html)

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

Install the udev rule

~~~
sudo cp ./49-teensy.rules /etc/udev/rules.d/
~~~

4. Run Arduino and select Teensy 3.5 from Tools > Board

5. Open a sketch and upload such as File > Examples > Digital > Blink LED

6. Now can use Arduino to verify and upload sketches once a sketch is already running

## Removing Ardunio IDE

To avoid We just need Teensyduino so we can copy the files located

* `<ARDUINOPATH>/hardware/tools/arm` goes to `<prj>/tools`
* `<ARDUINOPATH>/hardware/tools/<executable >` goes to `<prj>/tools`
* `<ARDUINOPATH>/hardware/teensy/avr/cores/teensy3` goes to `<prj>/teensy3` 

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

## Libraries

* [SD Card](https://github.com/greiman/SdFat-beta)

## MPU9250 libraries

Two possible libraries for MPU9250. need to figure out which is best/most complete
* [MPU9250](https://github.com/bolderflight/MPU9250)
* [AHRS](https://github.com/kriswiner/MPU9250)
* [Sparkfun](https://github.com/sparkfun/SparkFun_MPU-9250_Breakout_Arduino_Library)
*
* [Guide](https://learn.sparkfun.com/tutorials/mpu-9250-hookup-guide)
* [IMU](http://x-io.co.uk/open-source-imu-and-ahrs-algorithms/)

## Guides

* [Teensy Guide](https://www.pjrc.com/teensy/td_download.html)
* [Teensy Template](https://github.com/apmorton/teensy-template)
* [Teensyduino](https://www.pjrc.com/teensy/td_download.html)
* [Teensy Core](https://github.com/PaulStoffregen/cores)
* [Setup AVR](http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/)
* [Embedded AVR](http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/)
* [Arduino Makefile](https://github.com/sudar/Arduino-Makefile)
* [PlatformIO](https://github.com/platformio/platformio-core/)

### CMake examples

https://github.com/drichelson/teensy-cmake

https://github.com/xya/teensy-cmake

## Magnetometer Calibration

* https://ieeexplore.ieee.org/document/1290055
* https://www.hindawi.com/journals/js/2010/967245/#B11
* https://teslabs.com/articles/magnetometer-calibration/
* https://ieeexplore.ieee.org/document/6289882
* https://www.vectornav.com/docs/default-source/documentation/vn-100-documentation/AN012.pdf?sfvrsn=c99fe6b9_15

## NanoPB/Protocol Buffers

Uses [nanopb](https://jpa.kapsi.fi/nanopb/)

1. Download the latest release
2. Copy the `generator-bin` directory to `tools`
3. Use `./tools/generator-bin/protoc --nanopb_out=. simple.proto` to compile the proto message
4. Copy the new message definition files to `src` or `include`
5. Update the following files if desired: `pb.h`, `pb_common.h`, `pb_encode.h`, `pb_decode.h`, `pb_common.c`, `pb_encode.c`, `pb_decode.c`

* [Stream Binding](https://github.com/eric-wieser/nanopb-arduino)
~~~

pb_byte_t buffer[128];
size_t message_length;
bool status;

// encode the message
SimpleMessage message = SimpleMessage_init_zero;

// stream which will write to the buffer
pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

// fill in message
message.lucky_number = 13;

// encode message
status = pb_encode(&stream, SimpleMessage_fields, &message);
message_length = stream.bytes_written;

if (!status) {
    Serial.print("Error: ");
    Serial.println(PB_GET_ERROR(&stream));
    while(1) {}
}

// now send message over serial and then decode
{
// decode message
SimpleMessage message = SimpleMessage_init_zero;
pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
status = pb_decode(&stream, SimpleMessage_fields, &message);

if (!status) {
    Serial.print("Error: ");
    Serial.println(PB_GET_ERROR(&stream));
    while(1) {}
}

Serial.println((int)message.lucky_number);
}
~~~

### Sending byte buffer over serial

~~~
    uint8_t buffer[128];
    size_t message_length;
    bool status;
    SimpleMessage message = SimpleMessage_init_zero;
    pb_ostream_t pb_out = pb_ostream_from_buffer(buffer, sizeof(buffer));
    
    int count = 0;
    while (1) {
        // ENCODING
        message.lucky_number = count;
        status = pb_encode(&pb_out, SimpleMessage_fields, &message);
        message_length = pb_out.bytes_written;

        serial_usb.write(buffer, sizeof(buffer));

        /* if(!status) { */
        /*     serial_usb.print("Encoding failed"); */
        /* } */
        // DECODE 
        /* { */
        /*     // new buffer */
        /*     uint8_t buffer_out[128]; */
        /*     for(int ii=0;ii++;ii<sizeof(buffer)){ */
        /*         buffer_out[ii] = buffer[ii]; */
        /*     } */

        delay(1000);
        count = count +1;
    }
~~~
