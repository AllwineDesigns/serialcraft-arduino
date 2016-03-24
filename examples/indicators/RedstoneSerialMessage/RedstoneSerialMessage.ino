#include <SerialCraft.h>

SerialCraft sc;

const int redstoneLEDPin = 11;
const int redstoneLEDPin2 = 13;

void setup() {
  pinMode(redstoneLEDPin, OUTPUT);

    sc.setup();
    
    sc.registerRedstoneSerialCallback(redstoneSerial);
}

void loop() {
    sc.loop();
}

void redstoneSerial(int s, String id) {
    if(id == "test1") {
        analogWrite(redstoneLEDPin, map(s, 0, 15, 0, 255));
    } else if(id == "test2") {
        if(s > 0) {
            digitalWrite(redstoneLEDPin2, HIGH);
        } else {
            digitalWrite(redstoneLEDPin2, LOW);
        }
    }

    
}

