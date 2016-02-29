#include <SerialCraft.h>

SerialCraft sc;

void setup() {
sc.setup();

sc.registerDigitalInputCallback(sendMessage, 7);
}

void loop() {
  sc.loop();
}

void sendMessage(bool reading) {
  if(reading == LOW) {
    sc.sendChatMessage("hello world!");
  }
}
