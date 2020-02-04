#include "MPU9250.h"
#include "imu.h"

int setup_imu(MPU9250& IMU) {
    int status;
    
    Serial.begin(115200);
    Serial.println("Starting");

    while(!Serial) {}

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

int read_imu(MPU9250& IMU) {
    IMU.readSensor();
    // display the data
    Serial.print(IMU.getAccelX_mss(),6);
    Serial.print("\t");
    
    Serial.print(IMU.getAccelY_mss(),6);
    Serial.print("\t");

    Serial.print(IMU.getAccelZ_mss(),6);
    Serial.print("\t");

    Serial.print(IMU.getGyroX_rads(),6);
    Serial.print("\t");

    Serial.print(IMU.getGyroY_rads(),6);
    Serial.print("\t");

    Serial.print(IMU.getGyroZ_rads(),6);
    Serial.print("\t");
    
    Serial.print(IMU.getMagX_uT(),6);
    Serial.print("\t");

    Serial.print(IMU.getMagY_uT(),6);
    Serial.print("\t");

    Serial.print(IMU.getMagZ_uT(),6);
    Serial.print("\t");

    Serial.println(IMU.getTemperature_C(),6);

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

        // setup nanopb 
        this->accel_stream = pb_ostream_from_buffer(this->accel_buffer, sizeof(this->accel_buffer));

    }
    
    void IMU::encode( void ) {
        this->imu.readSensor();

        this->accel_msg.meas[0] = this->imu.getAccelX_mss();
        this->accel_msg.meas[1] = this->imu.getAccelY_mss();
        this->accel_msg.meas[2] = this->imu.getAccelZ_mss();
        
        this->gyro_msg.meas[0] = this->imu.getGyroX_rads();
        this->gyro_msg.meas[1] = this->imu.getGyroY_rads();
        this->gyro_msg.meas[2] = this->imu.getGyroZ_rads();

        this->mag_msg.meas[0] = this->imu.getMagX_uT();
        this->mag_msg.meas[1] = this->imu.getMagY_uT();
        this->mag_msg.meas[2] = this->imu.getMagZ_uT();

        this->temp_msg.meas[0] = this->imu.getTemperature_C();

        this->imu_msg.accel = this->accel_msg;
        this->imu_msg.gyro = this->gyro_msg;
        this->imu_msg.mag = this->mag_msg;
        this->imu_msg.temp = this->temp_msg;

        // write the message to the buffers
        // accel
        if (!pb_encode_ex(&this->accel_stream, AHRS_SensorMeasurement_fields, &this->accel_msg, PB_ENCODE_DELIMITED)) {
            Serial.println("Error: Accel encoding error");
        }

        if (!pb_encode_ex(&this->gyro_stream, AHRS_SensorMeasurement_fields, &this->gyro_msg, PB_ENCODE_DELIMITED)) {
            Serial.println("Error: Gyro encoding error");
        }

        if (!pb_encode_ex(&this->mag_stream, AHRS_SensorMeasurement_fields, &this->mag_msg, PB_ENCODE_DELIMITED)) {
            Serial.println("Error: Mag encoding error");
        }

        if (!pb_encode_ex(&this->temp_stream, AHRS_SensorMeasurement_fields, &this->temp_msg, PB_ENCODE_DELIMITED)) {
            Serial.println("Error: Temp encoding error");
        }

        if (!pb_encode_ex(&this->imu_stream, AHRS_SensorMeasurement_fields, &this->imu_msg, PB_ENCODE_DELIMITED)) {
            Serial.println("Error: IMU encoding error");
        }

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

    void IMU::output_serial( void ) {
        
        // get the latest data
        this->encode();
    
        // send over serial
        Serial.write(imu_buffer, sizeof(imu_msg));
    }
    
    void IMU::calibrate( void ) {

    }

}
