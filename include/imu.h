#ifndef IMU_H
#define IMU_H

#include "WProgram.h"
#include "Arduino.h"
#include "MPU9250.h"

#include "ahrs.pb.h"
#include "pb_common.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

int read_imu(MPU9250& IMU);

int calibrate_imu(MPU9250& IMU);

// TODO Build wrapper class for the IMU
// Seems X,Y axis are flipped for Chip wrt Board
// Verify that other sensors output into same frame (rotate to match the board)
//
//
int setup_imu(MPU9250 &IMU);

#define max_message_size 128

namespace AHRS {
    class IMU {
        private:
            int status;
            /* MPU9250 imu = MPU9250(Wire, 0x68); */
             
            // Buffers for IMU Protobuf message
            pb_byte_t imu_buffer[max_message_size];
            // streams
            pb_ostream_t imu_stream = pb_ostream_from_buffer(imu_buffer, max_message_size);
            // messages
            AHRS_IMUMeasurement imu_msg = AHRS_IMUMeasurement_init_zero;

            // encode measurements
            /* void setup_serial( void ); */
            
            void calibrate_mag( void );
        public:
            IMU( void );
            /* IMU(SPIClass &bus, uint8_t csPin) : MPU9250(bus, csPin) { */
            /* setup_serial(); */
            /* }; */
            virtual ~IMU( void ) {};
    
            // Send the buffers out over serial
            void output_serial(usb_serial_class& serial_usb);

            void calibrate( void );
            
            int read_imu( void );
            void encode( void );

            MPU9250 imu = MPU9250(SPI, 10);
    };
}
#endif
