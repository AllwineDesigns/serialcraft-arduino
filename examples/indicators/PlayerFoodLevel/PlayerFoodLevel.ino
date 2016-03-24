#include <SerialCraft.h>

SerialCraft sc;

const int foodLEDPin = 11;

void setup() {
    pinMode(foodLEDPin, OUTPUT);

    sc.setup();
   
    sc.registerPlayerFoodLevelCallback(food);
}

void loop() {
    sc.loop();
}

void food(int f) {
    analogWrite(foodLEDPin, map(f, 0, 20, 0, 255));
}
