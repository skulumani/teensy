#ifndef IMU_H
#define IMU_H

#include "WProgram.h"
#include "Arduino.h"
#include "MPU9250.h"

#include "ahrs.pb.h"
#include "pb_common.h"
#include "pb.h"
#include "pb_encode.h"

int read_imu(MPU9250& IMU);

int calibrate_imu(MPU9250& IMU);

// TODO Build wrapper class for the IMU
// Seems X,Y axis are flipped for Chip wrt Board
// Verify that other sensors output into same frame (rotate to match the board)
//
//
int setup_imu(MPU9250 &IMU);

namespace AHRS {
    class IMU {
        private:
            int status;
            void setup_serial( void );
            MPU9250 imu = MPU9250(SPI, 10);
            /* MPU9250 imu = MPU9250(Wire, 0x68); */
             
            // Buffers for IMU Protobuf message
            pb_byte_t accel_buffer[AHRS_SensorMeasurement_size];
            pb_byte_t gyro_buffer[AHRS_SensorMeasurement_size];
            pb_byte_t mag_buffer[AHRS_SensorMeasurement_size];
            pb_byte_t temp_buffer[AHRS_SensorMeasurement_size];
            
            pb_byte_t imu_buffer[AHRS_IMUMeasurement_size];

            // streams
            pb_ostream_t accel_stream; 

            // messages
            AHRS_SensorMeasurement accel_msg = AHRS_SensorMeasurement_init_zero;
            AHRS_IMUMeasurement imu_msg = AHRS_IMUMeasurement_init_zero;

            // encode measurements
            void encode( void );
        public:
            IMU( void );
            /* IMU(SPIClass &bus, uint8_t csPin) : MPU9250(bus, csPin) { */
            /* setup_serial(); */
            /* }; */
            virtual ~IMU( void ) {};
    
            // Send the buffers out over serial
            void output_serial( void );

            void calibrate( void );

    };
}
#endif
