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
    IMU.setAccelCalX(0, 1);
    IMU.setAccelCalY(0, 1);
    IMU.setAccelCalZ(0, 1);

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
