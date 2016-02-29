#include <SerialCraft.h>

SerialCraft sc;

const int joystickPin = 0;

void setup() {
  sc.setup();

  sc.registerTimerCallback(timerCallback, 16);
}

void loop() {
  sc.loop();
}

void timerCallback() {
    int reading = analogRead(joystickPin)-512;

    if(reading > 100 || reading < -100) {
      sc.moveMouse(2*reading, 0);
    } else {
      sc.moveMouse(0,0);
    }
    
}



