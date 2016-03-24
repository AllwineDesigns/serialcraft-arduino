#include <SerialCraft.h>

SerialCraft sc;

const int airLEDPin = 11;

void setup() {
    pinMode(airLEDPin, OUTPUT);

    sc.setup();
   
    sc.registerPlayerAirCallback(air);
}

void loop() {
    sc.loop();
}

void air(int a) {
    analogWrite(airLEDPin, map(a, 0, 300, 0, 255));
}
