
#include "MPU9250.h"

#include "imu.h"
#include "eigen_teensy.h"
#include "utility.h"

#include "simple.pb.h"
#include "pb_decode.h"

/* extern "C" int main(void) */
int main(void) {

    AHRS::IMU imu;

    pb_byte_t buffer[128];
    size_t message_length;
    bool status;

    // encode the message
    SimpleMessage message = SimpleMessage_init_zero;

    // stream which will write to the buffer
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    int count = 0;
    // loop forever
    while (1) {
        /* Serial.println("Working"); */
        /* imu.read_imu(); */
        /* imu.output_serial(); */
        /* blink_led(); */
        /* imu.output_serial(); */


        /* pb_byte_t buffer[128]; */
        /* size_t message_length; */
        /* bool status; */

        /* AHRS_IMUMeasurement imu_meas = AHRS_IMUMeasurement_init_zero; */
        /* pb_ostream_t stream = pb_ostream_from_buffer(buffer, 128); */
        /* imu.imu.readSensor(); */
        /* imu_meas.accel_meas[0] = imu.imu.getAccelX_mss(); */

        /* status = pb_encode(&stream, AHRS_IMUMeasurement_fields, &imu_meas); */
        /* message_length = stream.bytes_written; */

        /* // decode */
        /* { */
        /* AHRS_IMUMeasurement message = AHRS_IMUMeasurement_init_zero; */
        /* pb_istream_t stream = pb_istream_from_buffer(buffer, message_length); */
        /* status = pb_decode(&stream, AHRS_IMUMeasurement_fields, &message); */

        /* Serial.print(imu.imu.getAccelX_mss(), 6); */
        /* Serial.println(); */
        /* } */

        delay(1000);
        count = count + 1;
    // fill in message
    message.lucky_number = count;

    // encode message
    status = pb_encode(&stream, SimpleMessage_fields, &message);
    message_length = stream.bytes_written;

    // now send message over serial and then decode
    {
        // decode message
        SimpleMessage message = SimpleMessage_init_zero;
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        status = pb_decode(&stream, SimpleMessage_fields, &message);

        Serial.println((int)message.lucky_number);
    }
    }
}

