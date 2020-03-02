
#include "WProgram.h"
#include "Arduino.h"

#include "imu.h"
#include "utility.h"

volatile bool new_data;

void get_imu() {
    new_data = true;
}

/* extern "C" int main(void) */
int main(void) {
    
    AHRS::IMU imu(true);
    // interrupt settings
    pinMode(1, INPUT);
    attachInterrupt(1, get_imu, RISING);

    /* Serial.begin(115200); */
    usb_serial_class serial_usb;
    serial_usb.begin(115201);
    
    // buffer for message data
    uint8_t imu_buffer[AHRS_IMUMeasurement_size];

    // loop forever
    while (1) {
        if (new_data == true) {
            new_data = false;
            imu.update();
            imu.encode(imu_buffer);
            serial_usb.write(imu_buffer, sizeof(imu_buffer));
        }
    }
}

