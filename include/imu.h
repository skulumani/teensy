#ifndef IMU_H
#define IMU_H

#include "Arduino.h"
#include "MPU9250.h"

int setup_imu(MPU9250& IMU);
int read_imu(MPU9250& IMU);

int calibrate_imu(MPU9250& IMU);

// TODO Build wrapper class for the IMU
// Seems X,Y axis are flipped for Chip wrt Board
// Verify that other sensors output into same frame (rotate to match the board)
//
#endif
