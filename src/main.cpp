
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

    /* AHRS_IMUMeasurement imu_msg = AHRS_IMUMeasurement_init_zero; */
    // simple message
    uint8_t buffer[128];
    size_t message_length;
    bool status;
    
    // can no longer print to console when using nanopb - we're sending bytes
    /* Serial.println("starting"); */
    
    // pb_istream_s pb_in = as_pb_istream(Serial);
    // pb_decode(&pb_in, AHRS_IMUMeasurement_fields, &imu_msg)
    //
    // loop forever
    int count = 0;
    while (1) {
        imu.encode();
        imu.send(serial_usb);

        count = count +1;
    }
}

