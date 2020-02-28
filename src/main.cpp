
#include "MPU9250.h"

#include "imu.h"
#include "eigen_teensy.h"
#include "utility.h"

#include "simple.pb.h"

#include "pb_decode.h"
#include "pb_encode.h"
#include <Print.h>
#include <Stream.h>

class Print;
class Stream;

static bool pb_print_write(pb_ostream_t *stream, const pb_byte_t *buf, size_t count) {
    Print* p = reinterpret_cast<Print*>(stream->state);
    size_t written = p->write(buf, count);
    return written == count;
}

pb_ostream_s as_pb_ostream(Print& p) {
    return {&pb_print_write, &p, SIZE_MAX, 0};
}

static bool pb_stream_read(pb_istream_t *stream, pb_byte_t *buf, size_t count) {
    Stream* s = reinterpret_cast<Stream*>(stream->state);
    size_t written = s->readBytes(buf, count);
    return written == count;
}

pb_istream_s as_pb_istream(Stream& s) {
    #ifndef PB_NO_ERRMSG
        return {&pb_stream_read, &s, SIZE_MAX, 0};
    #else
        return {&pb_stream_read, &s, SIZE_MAX};
    #endif
}

/* extern "C" int main(void) */
int main(void) {
    
    AHRS::IMU imu;
    usb_serial_class serial_usb;
    serial_usb.begin(115200);

    /* AHRS_IMUMeasurement imu_msg = AHRS_IMUMeasurement_init_zero; */
    // simple message
    uint8_t buffer[128];
    size_t message_length;
    bool status;
    
    // can no longer print to console when using nanopb - we're sending bytes
    /* serial_usb.println("starting"); */
    
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

        /* serial_usb.write(buffer, sizeof(buffer)); */
        serial_usb.write(imu.imu_buffer, sizeof(imu.imu_buffer));

        delay(1000);
        count = count +1;
    }
}

