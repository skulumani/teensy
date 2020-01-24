#include "WProgram.h"
#include "MPU9250.h"

extern "C" int main(void)
{
#ifdef USING_MAKEFILE

	// To use Teensy 3.0 without Arduino, simply put your code here.
	// For example:

    MPU9250 IMU(Wire,0x68);
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

	pinMode(13, OUTPUT);
	while (1) {
        /* digitalWriteFast(13, HIGH); */
        /* delay(1000); */
        /* digitalWriteFast(13, LOW); */
        /* delay(500); */
        /* Serial.println("Hello"); */
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
        delay(100);
	}


#else
	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
		yield();
	}
#endif
}

