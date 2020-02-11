
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
        /* imu.read_imu(); */
        imu.output_serial();
        /* blink_led(); */
        /* imu.output_serial(); */
        delay(1000);
	}
}

