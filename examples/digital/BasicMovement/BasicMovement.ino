#include <SerialCraft.h>

SerialCraft sc;

void setup() {
  sc.setup();

  sc.registerDigitalInputCallback(forwardMovement, 7);
  sc.registerDigitalInputCallback(backwardMovement, 6);
  sc.registerDigitalInputCallback(leftMovement, 5);
  sc.registerDigitalInputCallback(rightMovement, 4);
}

void loop() {
  sc.loop();
}

void forwardMovement(bool reading) {
  if(reading == LOW) {
      sc.startMovingForward();
  } else {
      sc.stopMovingForward();
  }
}

void backwardMovement(bool reading) {
  if(reading == LOW) {
      sc.startMovingBackward();
  } else {
      sc.stopMovingBackward();
  }
}

void leftMovement(bool reading) {
  if(reading == LOW) {
      sc.startMovingLeft();
  } else {
      sc.stopMovingLeft();
  }
}

void rightMovement(bool reading) {
  if(reading == LOW) {
      sc.startMovingRight();
  } else {
      sc.stopMovingRight();
  }
}
