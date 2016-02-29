#include <SerialCraft.h>

SerialCraft sc;

void setup() {
sc.setup();

sc.registerAnalogInputCallback(analogCallback, 0);
}

void loop() {
  sc.loop();

}

void analogCallback(int reading) {
  int t = map(reading, 0, 1023, 6000, 18000);
  sc.setTime(t);
}
