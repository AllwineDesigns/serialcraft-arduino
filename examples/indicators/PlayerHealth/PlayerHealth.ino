#include <SerialCraft.h>

SerialCraft sc;

const int healthLEDPin = 11;

void setup() {
    pinMode(healthLEDPin, OUTPUT);

    sc.setup();
   
    sc.registerPlayerHealthCallback(health);
}

void loop() {
    sc.loop();
}

void health(int h) {
    analogWrite(healthLEDPin, map(h, 0, 20, 0, 255));
}
