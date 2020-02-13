#include "utility.h"

void setup_led() {
    int led = 13;
    pinMode(led, OUTPUT);
}

void blink_led(const int& blink_rate) {

    int led = 13;
    float delay_time = 1.0/blink_rate * 1000;
    digitalWrite(led, HIGH);
    delay(delay_time);
    digitalWrite(led, LOW);
    delay(delay_time);
}
