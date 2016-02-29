#include <SerialCraft.h>

SerialCraft sc;

void setup() {
  sc.setup();

  sc.registerDigitalInputCallback(leftClick, 7);
  sc.registerDigitalInputCallback(rightClick, 6);
}

void loop() {
  sc.loop();
}

void leftClick(bool reading) {
  if(reading == LOW) {
    sc.pressLeftMouseButton();
  } else {
    sc.releaseLeftMouseButton();
  }
}

void rightClick(bool reading) {
  if(reading == LOW) {
    sc.pressRightMouseButton();
  } else {
    sc.releaseRightMouseButton();
  }
}
