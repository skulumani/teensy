
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
    return {pb_print_write, &p, SIZE_MAX, 0};
}

static bool pb_stream_read(pb_istream_t *stream, pb_byte_t *buf, size_t count) {
    Stream* s = reinterpret_cast<Stream*>(stream->state);
    size_t written = s->readBytes(buf, count);
    return written == count;
}

pb_istream_s as_pb_istream(Stream& s) {
    #ifndef PB_NO_ERRMSG
        return {pb_stream_read, &s, SIZE_MAX, 0};
    #else
        return {pb_stream_read, &s, SIZE_MAX};
    #endif
}

/* extern "C" int main(void) */
int main(void) {

    AHRS::IMU imu;

    AHRS_IMUMeasurement imu_msg = AHRS_IMUMeasurement_init_zero;
    imu_msg.accel_meas[0] = 1.0;
    imu_msg.accel_meas[1] = 2.0;
    imu_msg.accel_meas[2] = 3.0;

    pb_ostream_s pb_out = as_pb_ostream(Serial);
    Serial.println("encoding");
    bool status = pb_encode(&pb_out, AHRS_IMUMeasurement_fields, &imu_msg);
    
    // pb_istream_s pb_in = as_pb_istream(Serial);
    // pb_decode(&pb_in, AHRS_IMUMeasurement_fields, &imu_msg)
    //
    // loop forever
    while (1) {
        delay(1000);
        Serial.println("test");
    }
}

