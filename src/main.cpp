
#include "MPU9250.h"

#include "imu.h"
#include "eigen_teensy.h"
#include "utility.h"

#include "simple.pb.h"
#include "pb_decode.h"

/* extern "C" int main(void) */
int main(void) {

    AHRS::IMU imu;

    // loop forever
	while (1) {
        /* Serial.println("Working"); */
        imu.read_imu();
        /* imu.output_serial(); */
        /* blink_led(); */
        /* imu.output_serial(); */
        delay(1000);
	}
}

    /* pb_byte_t buffer[128]; */
    /* size_t message_length; */
    /* bool status; */

    /* // encode the message */
    /* SimpleMessage message = SimpleMessage_init_zero; */
    
    /* // stream which will write to the buffer */
    /* pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer)); */

    /* // fill in message */
    /* message.lucky_number = 13; */
    
    /* // encode message */
    /* status = pb_encode(&stream, SimpleMessage_fields, &message); */
    /* message_length = stream.bytes_written; */

    /* if (!status) { */
    /*     Serial.print("Error: "); */
    /*     Serial.println(PB_GET_ERROR(&stream)); */
    /*     while(1) {} */
    /* } */

    /* // now send message over serial and then decode */
    /* { */
    /* // decode message */
    /* SimpleMessage message = SimpleMessage_init_zero; */
    /* pb_istream_t stream = pb_istream_from_buffer(buffer, message_length); */
    /* status = pb_decode(&stream, SimpleMessage_fields, &message); */

    /* if (!status) { */
    /*     Serial.print("Error: "); */
    /*     Serial.println(PB_GET_ERROR(&stream)); */
    /*     while(1) {} */
    /* } */

    /* Serial.println((int)message.lucky_number); */
    /* } */
