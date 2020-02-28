
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
    
        // ENCODING
        SimpleMessage message = SimpleMessage_init_zero;
        pb_ostream_t pb_out = pb_ostream_from_buffer(buffer, sizeof(buffer));

        message.lucky_number = count;

        status = pb_encode(&pb_out, SimpleMessage_fields, &message);
        message_length = pb_out.bytes_written;
        
        {
            SimpleMessage msg = SimpleMessage_init_zero;
            pb_istream_t stream = pb_istream_from_buffer(buffer, sizeof(buffer));
            pb_decode(&stream, SimpleMessage_fields, &msg);
            serial_usb.println(msg.lucky_number);

            AHRS_IMUMeasurement imu_msg = AHRS_IMUMeasurement_init_zero;
            pb_istream_t imu_stream = pb_istream_from_buffer(imu.imu_buffer, sizeof(imu.imu_buffer));
            pb_decode(&imu_stream, AHRS_IMUMeasurement_fields, &imu_msg);
            serial_usb.println(imu_msg.accel_meas[0]);
            imu.read_imu();
        }
        /* serial_usb.write(buffer, sizeof(buffer)); */
        /* imu.send(serial_usb); */

        delay(1000);
        count = count +1;
    }
}

