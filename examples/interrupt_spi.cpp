

#include "MPU9250.h"
#include "WProgram.h"
#include "Arduino.h"

MPU9250 IMU(SPI, 10);
int status;

volatile bool newData;

void getIMU ( ) {
    newData = true;
}

int main( void ) {

    Serial.begin(115200);
    while(!Serial) {}

    status = IMU.begin();
    if (status < 0) {
        Serial.println("IMU initialization unsuccessful");
        while(1) {}
    }

    IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_184HZ);
    IMU.setSrd(200);
    IMU.enableDataReadyInterrupt();
    pinMode(1, INPUT);
    attachInterrupt(1, getIMU, RISING);

    float t1, t2;
    float dt;
    t1 = 0;
    t2 = 0;
    dt = 0;
    while(1) {
        if (newData == true) {
            newData = false;
            // read the sensor
            IMU.readSensor();
            t2 = (float)micros()/1.0e6;
            dt = t2-t1;
            t1 = t2;
            // display the data
            Serial.print(1/dt,6);
            Serial.print(" hz\t");
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
        }
    }
}


