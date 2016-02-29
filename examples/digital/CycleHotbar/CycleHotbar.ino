#include <SerialCraft.h>

SerialCraft sc;

int item = 1;

void setup() {
  sc.setup();

  sc.registerDigitalInputCallback(nextItem, 7);
}

void loop() {
  sc.loop();
}

void nextItem(bool reading) {
  if(reading == LOW) {
    item = item%9+1;
    sc.setHotbarItem(item);
  }
}
