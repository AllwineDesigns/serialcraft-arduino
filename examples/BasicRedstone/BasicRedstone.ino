#include <SerialCraft.h>

SerialCraft sc;

void setup() {
sc.setup();

sc.registerRedstoneInputCallback(redstoneCallback, 0);
}

void loop() {
  sc.loop();

}

void redstoneCallback(int reading) {
  sc.sendRedstoneSignal("test", reading);
}

