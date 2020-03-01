

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
    Serial.println("starting");
    if (status < 0) {
        Serial.println("IMU initialization unsuccessful");
        while(1) {
        Serial.println("Broken");
        delay(2000);
        }
    }
    
    IMU.enableWakeOnMotion(100, MPU9250::LP_ACCEL_ODR_15_63HZ);
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
            Serial.println("Awake!");
        }
    }
}


