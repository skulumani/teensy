
#include "MPU9250.h"

#include "imu.h"
#include "eigen_teensy.h"
#include "utility.h"

#include "simple.pb.h"

#include "pb_decode.h"
#include "pb_encode.h"

/* extern "C" int main(void) */
int main(void) {
    
    AHRS::IMU imu;
    /* Serial.begin(115200); */
    usb_serial_class serial_usb;
    serial_usb.begin(115200);
    
    // loop forever
    while (1) {
        imu.encode();
        imu.send(serial_usb);
        delay(1000);
    }
}

