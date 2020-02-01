#include "WProgram.h"
#include "MPU9250.h"
#include "imu.h"

/* extern "C" int main(void) */
int main(void) {
    MPU9250 IMU(Wire,0x68);
    int imu_status = setup_imu(IMU);

	pinMode(13, OUTPUT);
	while (1) {
        read_imu(IMU);
        delay(100);
	}
}

