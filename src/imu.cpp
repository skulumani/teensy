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

int AHRS::IMU::read_imu( void ) {
    this->imu.readSensor();
    // display the data
    Serial.print(this->imu.getAccelX_mss(),6);
    Serial.print("\t");
    
    Serial.print(this->imu.getAccelY_mss(),6);
    Serial.print("\t");

    Serial.print(this->imu.getAccelZ_mss(),6);
    Serial.print("\t");

    Serial.print(this->imu.getGyroX_rads(),6);
    Serial.print("\t");

    Serial.print(this->imu.getGyroY_rads(),6);
    Serial.print("\t");

    Serial.print(this->imu.getGyroZ_rads(),6);
    Serial.print("\t");
    
    Serial.print(this->imu.getMagX_uT(),6);
    Serial.print("\t");

    Serial.print(this->imu.getMagY_uT(),6);
    Serial.print("\t");

    Serial.print(this->imu.getMagZ_uT(),6);
    Serial.print("\t");

    Serial.println(this->imu.getTemperature_C(),6);

    return 0;
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
    float val;
    
    Serial.println("Finished Calibration");
}


namespace AHRS {

    IMU::IMU( void ) {
        this->setup_serial();
    }
    

    void IMU::setup_serial( void ) {
        Serial.begin(115200);
        Serial.println("Starting IMU Serial outputs");

        while(!Serial) {}

        status = this->imu.begin();

        if (status < 0) {
            Serial.println("IMU Initialization unsuccessful");
            Serial.println("Check IMU wiring or power cycle");
            Serial.print("Status: ");
            Serial.println(status);
            while(1) {};
        }
    }

    void IMU::encode( void ) {
        this->imu.readSensor();

        // setup nanopb stuff
        /* pb_byte_t imu_buffer[AHRS_IMUMeasurement_size]; */
        /* pb_ostream_t imu_stream = pb_ostream_from_buffer(imu_buffer, AHRS_IMUMeasurement_size); */
        /* AHRS_IMUMeasurement imu_msg = AHRS_IMUMeasurement_init_zero; */

        this->imu_msg.accel_meas[0] = this->imu.getAccelX_mss();
        this->imu_msg.accel_meas[1] = this->imu.getAccelY_mss();
        this->imu_msg.accel_meas[2] = this->imu.getAccelZ_mss();
        
        this->imu_msg.gyro_meas[0] = this->imu.getGyroX_rads();
        this->imu_msg.gyro_meas[1] = this->imu.getGyroY_rads();
        this->imu_msg.gyro_meas[2] = this->imu.getGyroZ_rads();

        this->imu_msg.mag_meas[0] = this->imu.getMagX_uT();
        this->imu_msg.mag_meas[1] = this->imu.getMagY_uT();
        this->imu_msg.mag_meas[2] = this->imu.getMagZ_uT();

        this->imu_msg.temp_meas = this->imu.getTemperature_C();

        // write the message to the buffers
        if (!pb_encode_ex(&this->imu_stream, AHRS_IMUMeasurement_fields, &this->imu_msg, PB_ENCODE_DELIMITED)) {
            Serial.println("Error: IMU encoding error");
        }

    }

    void IMU::output_serial( void ) {
        
        // get the latest data
        this->encode();
    
        // send over serial
        /* Serial.write(this->imu_buffer, AHRS_IMUMeasurement_size); */

        // decode here and output over serial
        {
            AHRS_IMUMeasurement imu_new = AHRS_IMUMeasurement_init_zero;
            pb_byte_t imu_buffer_new[max_message_size];
            pb_istream_t stream = pb_istream_from_buffer(this->imu_buffer, max_message_size);
            bool status = pb_decode_ex(&stream, AHRS_IMUMeasurement_fields, &imu_new, PB_DECODE_DELIMITED);
            Serial.println((float)imu_new.accel_meas[0]);
        }
    }
    
    void IMU::calibrate( void ) {

    }
    
    void IMU::calibrate_mag( void ) {
        // collect a bunch of mag data and send off board
    }
}
