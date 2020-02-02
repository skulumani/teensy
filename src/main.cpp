#include "WProgram.h"
#include "MPU9250.h"

#include "imu.h"
#include "eigen_teensy.h"
#include "utility.h"

/* extern "C" int main(void) */
int main(void) {
    /* MPU9250 IMU(Wire,0x68); */
    /* MPU9250 IMU(SPI, 10); */
    /* int imu_status = setup_imu(IMU); */

    AHRS::IMU imu(SPI, 10);

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

