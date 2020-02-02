#include "WProgram.h"
#include "MPU9250.h"

#include "imu.h"
#include "eigen_teensy.h"
#include "utility.h"

/* extern "C" int main(void) */
int main(void) {

    AHRS::IMU imu;

    /* setup_led(); */
    // always need a loop 
	while (1) {
        /* read_imu(IMU); */
        /* Serial.println("Working"); */
        /* blink_led(); */
        imu.output_serial();
        delay(100);
	}
}

