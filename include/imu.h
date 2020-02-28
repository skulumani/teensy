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
             

            // encode measurements
            /* void setup_serial( void ); */
            
            void calibrate_mag( void );

            // keep track of time
            uint32_t current_time = 0;

        public:
            // Buffers for IMU Protobuf message
            pb_byte_t imu_buffer[max_message_size];

            IMU( void );
            /* IMU(SPIClass &bus, uint8_t csPin) : MPU9250(bus, csPin) { */
            /* setup_serial(); */
            /* }; */
            virtual ~IMU( void ) {};
    
            // Send the buffers out over serial
            /* void output_serial(usb_serial_class& serial_usb); */

            void calibrate( void );
            
            int read_imu( void );
            void encode( void );
            
            void send(usb_serial_class& serial_usb);

            MPU9250 imu = MPU9250(SPI, 10);
    };
}
#endif
