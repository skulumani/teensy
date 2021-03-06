#include "MPU9250.h"
#include "imu.h"

int setup_imu(MPU9250& IMU) {
    int status;
    
    Serial.begin(115200);
    Serial.println("Starting");

    while(!Serial) {
        Serial.println("Broken Serial");
    }

    // start communication with IMU 
    status = IMU.begin();
    if (status < 0) {
        Serial.println("IMU initialization unsuccessful");
        Serial.println("Check IMU wiring or try cycling power");
        Serial.print("Status: ");
        Serial.println(status);
        while(1) {}
    }

    // set calibration
    /* IMU.setAccelCalX(0, 1); */
    /* IMU.setAccelCalY(0, 1); */
    /* IMU.setAccelCalZ(0, 1); */

    return status;
}

int calibrate_imu(MPU9250& IMU) {
    // calibrate gyro
    Serial.println("Starting Gyro Calibration");
    Serial.println("Remain stationary!");
    delay(5000);
    IMU.calibrateGyro();

    Serial.println("Finished Gyro Calibration");

    // calibrate accel
    Serial.println("Starting Accel Calibration");
    Serial.println("Rotate IMU to all six orientations");
    
    Serial.println("X+ down");
    delay(5000);
    IMU.calibrateAccel();

    Serial.println("X- down");
    delay(5000);
    IMU.calibrateAccel();

    Serial.println("Y+ down");
    delay(5000);
    IMU.calibrateAccel();

    Serial.println("Y- down");
    delay(5000);
    IMU.calibrateAccel();
    
    Serial.println("Z+ down");
    delay(5000);
    IMU.calibrateAccel();

    Serial.println("Z- down");
    delay(5000);
    IMU.calibrateAccel();

    Serial.println("Finished Accel Calibration");
    // calibrate mag
    Serial.println("Starting Mag Calibration");
    delay(5000);
    IMU.calibrateMag();
    Serial.println("Finished Mag Calibration");

    // read the calibration values and save to the SD card/print out
    Serial.println("Finished Calibration");

    return 0;
}

namespace AHRS {

    IMU::IMU( void ) {
        setup_imu();
    }
    
    IMU::IMU( bool enable_interrupt) {
        _enable_interrupt = enable_interrupt;
        setup_imu();
    }

    int IMU::setup_imu( void ) {
        check_status(_imu.begin(), "imu.begin() error");

        check_status(_imu.setAccelRange(_accel_range), "imu.setAccelRange() error");
        check_status(_imu.setGyroRange(_gyro_range), "imu.setGyroRange() error");
        check_status( _imu.setDlpfBandwidth(_bandwidth), "imu.setDlpfBandwidth() error");
        check_status(_imu.setSrd(_sample_rate_divider), "imu.setSrd() error");

        if(_enable_interrupt) {
            check_status(_imu.enableDataReadyInterrupt(), "imu.enableDataReadyInterrupt() error");
        } else {
            check_status(_imu.disableDataReadyInterrupt(), "imu.disableDataReadyInterrupt() error");
        }
        
    }

    void IMU::check_status( int status_flag, String error_string ) {
        if (status_flag < 0) {
            Serial.println("Bad IMU Status");
            Serial.println("Check IMU wiring or power cycle");
            Serial.print("Status: ");
            Serial.println(status_flag);
            while(1) {
                Serial.println(error_string); 
                delay(2000);
            };
        } else {
            _imu_status = status_flag;
        }
        
    }

    void IMU::encode( uint8_t (&imu_buffer)[AHRS_IMUMeasurement_size]) {
        // setup nanopb stuff
        AHRS_IMUMeasurement imu_msg = AHRS_IMUMeasurement_init_zero;
        imu_msg.has_accel = true;
        imu_msg.has_gyro = true;
        imu_msg.has_mag = true;

        pb_ostream_t imu_stream = pb_ostream_from_buffer(imu_buffer, sizeof(imu_buffer));

        /* imu_msg.time      = _t_delta; */
        imu_msg.time = (float) micros()/1.0e6;

        imu_msg.accel.x = _imu.getAccelX_mss();
        imu_msg.accel.y = _imu.getAccelY_mss();
        imu_msg.accel.z = _imu.getAccelZ_mss();
        
        imu_msg.gyro.x = _imu.getGyroX_rads();
        imu_msg.gyro.y = _imu.getGyroY_rads();
        imu_msg.gyro.z = _imu.getGyroZ_rads();
        
        imu_msg.mag.x = _imu.getMagX_uT();
        imu_msg.mag.y = _imu.getMagY_uT();
        imu_msg.mag.z = _imu.getMagZ_uT();

        imu_msg.temp = _imu.getTemperature_C();

        pb_encode(&imu_stream, AHRS_IMUMeasurement_fields, &imu_msg);
         
        // write the message to the buffers
        /**
          if (!pb_encode_ex(&this->imu_stream, AHRS_IMUMeasurement_fields, &this->imu_msg, PB_ENCODE_DELIMITED)) {
          Serial.println("Error: IMU encoding error");
          }
         **/ 

    }

/**
    void IMU::output_serial(usb_serial_class& serial_usb ) {
        serial_usb.write(this->imu_buffer, sizeof(this->imu_buffer)); 
    }
**/  

    void IMU::calibrate( void ) {

    }
    
    void IMU::calibrate_mag( void ) {
        // collect a bunch of mag data and send off board
    }
    
    int IMU::read_imu( void ) {
        _imu.readSensor();
        // display the data
        Serial.print(_imu.getAccelX_mss(),6);
        Serial.print("\t");

        Serial.print(_imu.getAccelY_mss(),6);
        Serial.print("\t");

        Serial.print(_imu.getAccelZ_mss(),6);
        Serial.print("\t");

        Serial.print(_imu.getGyroX_rads(),6);
        Serial.print("\t");

        Serial.print(_imu.getGyroY_rads(),6);
        Serial.print("\t");

        Serial.print(_imu.getGyroZ_rads(),6);
        Serial.print("\t");

        Serial.print(_imu.getMagX_uT(),6);
        Serial.print("\t");

        Serial.print(_imu.getMagY_uT(),6);
        Serial.print("\t");

        Serial.print(_imu.getMagZ_uT(),6);
        Serial.print("\t");

        Serial.println(_imu.getTemperature_C(),6);

        return 0;
    }
    
    void IMU::update( void ) {
        _imu.readSensor();
        _t2 = micros();
        _t_delta = (float)(_t2-_t1)/1.0e6;
        _t1 = _t2;
    }

    Eigen::Matrix<float, 3, 1> IMU::get_accel( void ) {
        Eigen::Matrix<float, 3, 1> accel(_imu.getAccelX_mss() ,
                _imu.getAccelY_mss(),
                _imu.getAccelZ_mss());
        return accel;
    }

    Eigen::Matrix<float, 3, 1> IMU::get_gyro( void ) {
        Eigen::Matrix<float, 3, 1> gyro(_imu.getGyroX_rads() ,
                _imu.getGyroY_rads(),
                _imu.getGyroZ_rads());
        return gyro;
    }

    Eigen::Matrix<float, 3, 1> IMU::get_mag( void ) {
        Eigen::Matrix<float, 3, 1> mag(_imu.getMagX_uT() ,
                _imu.getMagY_uT(),
                _imu.getMagZ_uT());
        return mag;
    }

    float IMU::get_temp( void ) {
        return _imu.getTemperature_C();
    }
}
