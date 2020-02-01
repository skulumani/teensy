#ifndef IMU_H
#define IMU_H
#include "MPU9250.h"

int setup_imu(MPU9250& IMU);
int read_imu(MPU9250& IMU);

int calibrate_imu(MPU9250& IMU);

#endif
