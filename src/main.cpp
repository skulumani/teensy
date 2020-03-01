
#include "WProgram.h"
#include "Arduino.h"

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
    serial_usb.begin(115201);
    
    // buffer for message data
    uint8_t imu_buffer[AHRS_IMUMeasurement_size];

    // loop forever
    while (1) {
        imu.encode(imu_buffer);
        /* imu.send(serial_usb); */
        serial_usb.write(imu_buffer, sizeof(imu_buffer));
        delay(100);
    }
}

