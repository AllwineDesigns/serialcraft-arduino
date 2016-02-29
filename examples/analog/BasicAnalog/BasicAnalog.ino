#include <SerialCraft.h>

SerialCraft sc;

void setup() {
  sc.setup();
  sc.registerAnalogInputCallback(analogInput, 0);
}

void loop() {
  sc.loop();
}

void analogInput(int reading) {
  Serial.println(reading);
}

