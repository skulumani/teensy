#ifndef IMU_H
#define IMU_H

#include "WProgram.h"
#include "Arduino.h"
#include "MPU9250.h"

int read_imu(MPU9250& IMU);

int calibrate_imu(MPU9250& IMU);

// TODO Build wrapper class for the IMU
// Seems X,Y axis are flipped for Chip wrt Board
// Verify that other sensors output into same frame (rotate to match the board)
//
//
int setup_imu(MPU9250 &IMU);

namespace AHRS {
    class IMU : public MPU9250 {
        private:
            int status;
            void setup_serial( void );

        public:
            IMU(SPIClass &bus, uint8_t csPin) : MPU9250(bus, csPin) {
            setup_serial();
            };
            virtual ~IMU( void ) {};

            void output_serial( void );

            void calibrate( void );

    };
}
#endif
