#include <SerialCraft.h>

SerialCraft sc;

void setup() {
  sc.setup();

  sc.registerDigitalInputCallback(digitalCallback, 7);
}

void loop() {
  sc.loop();
}

void digitalCallback(bool reading) {
  if(reading == HIGH) {
    sc.sendRedstoneSignal("test", 0);
  } else {
    sc.sendRedstoneSignal("test", 15);
  }
}
