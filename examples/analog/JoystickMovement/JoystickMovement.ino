#include <SerialCraft.h>

SerialCraft sc;

const int rightJoystickXPin = 5;
const int rightJoystickYPin = 4;

const int leftJoystickXPin = 9;
const int leftJoystickYPin = 8;

void setup() {
  sc.setup();

  sc.registerTimerCallback(checkJoysticks, 16);
}

void loop() {
  sc.loop();
}

void checkJoysticks() {
    int x = analogRead(rightJoystickXPin)-512;
    int y = analogRead(rightJoystickYPin)-512;

    if(x > 100 || x < -100 ||
        y > 100 || y < -100) {
      sc.moveMouse(2*x, 2*y);
    } else {
      sc.moveMouse(0,0);
    }

    int leftX = analogRead(leftJoystickXPin)-512;
    int leftY = analogRead(leftJoystickYPin)-512;

    sc.analogMovement(leftX,leftY);
}
