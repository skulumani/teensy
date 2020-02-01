#include "WProgram.h"
#include "MPU9250.h"
#include "imu.h"
#include "eigen_teensy.h"

/* extern "C" int main(void) */
int main(void) {
    /* MPU9250 IMU(Wire,0x68); */
    int led = 13;
    test_eigen();
    /* MPU9250 IMU(SPI, 10); */

    /* int imu_status = setup_imu(IMU); */


	pinMode(led, OUTPUT);
    // always need a loop 
	while (1) {
        /* read_imu(IMU); */
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
        delay(500);
        /* Serial.println("Working"); */
	}
}

