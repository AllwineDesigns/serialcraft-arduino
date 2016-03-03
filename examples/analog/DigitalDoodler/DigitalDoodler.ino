#include <SerialCraft.h>

SerialCraft sc(9600);

int x;
int y;

void setup() {
  sc.setup();
  sc.registerAnalogInputCallback(analogInputX, 5, 2,0);
  sc.registerAnalogInputCallback(analogInputY, 0, 2,0);
}

void loop() {
  sc.loop();
}

void analogInputX(int reading) {
  x = reading;
  Serial.print(x);
  Serial.print("\t");
  Serial.println(y);
}
void analogInputY(int reading) {
  y = reading;
  Serial.print(x);
  Serial.print("\t");
  Serial.println(y);
}


