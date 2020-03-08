#ifndef IMU_H
#define IMU_H

#include "MPU9250.h"
#include "eigen_teensy.h"

#include "ahrs.pb.h"
#include "pb_common.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

int read_imu(MPU9250& IMU);

int calibrate_imu(MPU9250& IMU);

// TODO 
// Seems X,Y axis are flipped for Chip wrt Board
// Verify that other sensors output into same frame (rotate to match the board)
int setup_imu(MPU9250 &IMU);

namespace AHRS {
    class IMU {
        private:
            int _imu_status;

            /* MPU9250 imu = MPU9250(Wire, 0x68); */
            MPU9250 _imu = MPU9250(SPI, 10);
            
            // keep track of time
            uint32_t _t1 = 0;
            uint32_t _t2 = 0;
            float _t_delta = 0;
            
            // IMU parameters
            MPU9250::AccelRange _accel_range = MPU9250::ACCEL_RANGE_16G;
            MPU9250::GyroRange _gyro_range = MPU9250::GYRO_RANGE_2000DPS;
            MPU9250::DlpfBandwidth _bandwidth = MPU9250::DLPF_BANDWIDTH_184HZ;
            uint8_t _sample_rate_divider = 9; // TODO Create an enum to set SRD/DLPF for a few common sample rates
            // 0  - 1000 hz, 9 - 100hz
            bool _enable_interrupt = true;

            void calibrate_mag( void );
            void check_status( int status_flag, String error_string);
            int setup_imu( void );
        public:
            // constructors
            IMU( void );
            IMU( bool enable_interrupt);

            virtual ~IMU( void ) {};
    
            void calibrate( void );
            
            int read_imu( void );
            void encode( uint8_t (&imu_buffer)[AHRS_IMUMeasurement_size]);
            
            void update( void );

            Eigen::Matrix<float, 3, 1> get_accel( void ) ;
            Eigen::Matrix<float, 3, 1> get_gyro( void ) ;
            Eigen::Matrix<float, 3, 1> get_mag( void ) ;
            float get_temp( void ) ;

    };
}
#endif
