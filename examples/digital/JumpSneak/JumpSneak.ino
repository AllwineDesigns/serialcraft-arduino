#include <SerialCraft.h>

SerialCraft sc;

int item = 1;

void setup() {
  sc.setup();

  sc.registerDigitalInputCallback(jump, 7);
  sc.registerDigitalInputCallback(sneak, 6);
}

void loop() {
  sc.loop();
}

void jump(bool reading) {
  if(reading == LOW) {
    sc.startJumping();
  } else {
    sc.stopJumping();
  }
}

void sneak(bool reading) {
  if(reading == LOW) {
    sc.startSneaking();
  } else {
    sc.stopSneaking();
  }
}
