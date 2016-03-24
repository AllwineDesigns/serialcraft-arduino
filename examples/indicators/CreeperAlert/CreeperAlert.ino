#include <SerialCraft.h>

SerialCraft sc;

bool blinkCreeper = false;
bool creeperLEDOn = true;

const int creeperLEDPin = 11;

void setup() {
    pinMode(creeperLEDPin, OUTPUT);
    sc.setup();

    sc.registerCreeperDistanceCallback(creeper);
    sc.registerTimerCallback(timer, 100);
}

void loop() {
    sc.loop();
}

void creeper(int dist) {
  dist = constrain(dist, 0, 20);
  if(dist < 8) {
      blinkCreeper = true;
  } else {
    blinkCreeper = false;
    analogWrite(creeperLEDPin, map(20-dist, 0, 20, 0, 255));
  }
}

void timer() {
    if(blinkCreeper) {
      creeperLEDOn = !creeperLEDOn;
      if(creeperLEDOn) {
        digitalWrite(creeperLEDPin, HIGH);
      } else {
        digitalWrite(creeperLEDPin, LOW);
      }
    }
}

