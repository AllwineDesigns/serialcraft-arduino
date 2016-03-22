#ifndef SERIAL_CRAFT_INCLUDE
#define SERIAL_CRAFT_INCLUDE

#ifndef SERIAL_CRAFT_TIMERS
#define SERIAL_CRAFT_TIMERS 4
#endif

#ifndef SERIAL_CRAFT_DIGITAL_INPUTS
#define SERIAL_CRAFT_DIGITAL_INPUTS 4
#endif

#ifndef SERIAL_CRAFT_ANALOG_INPUTS
#define SERIAL_CRAFT_ANALOG_INPUTS 4
#endif

#ifndef SERIAL_CRAFT_REDSTONE_INPUTS
#define SERIAL_CRAFT_REDSTONE_INPUTS 4
#endif

#ifndef SERIAL_CRAFT_HOTBAR_INPUTS
#define SERIAL_CRAFT_HOTBAR_INPUTS 4
#endif

#include <Arduino.h>

class SCTimer {
  private:
      void (*callback)();
      unsigned long lastUpdate;
      unsigned long interval;
      
  public: 
      SCTimer() {
      }
      SCTimer(void (*func)(), unsigned long i) : 
          callback(func), interval(i), lastUpdate(0) {
      }

      bool isReady() {
        return millis()-lastUpdate > interval;
      }

      void callCallback() {
        callback();
        lastUpdate = millis();
      }
};

// defaults to pullup resistor and readings must be sustained for 50 milliseconds for a change to be detected (debounced)
class SCDigitalInput {
    private:
        bool state;
        bool lastReading;
        unsigned long int lastReadingTime;

        int pin;
        unsigned int debounce_time;

        void (*callback)(bool);

    public:
        SCDigitalInput() {
        }
        SCDigitalInput(void (*func)(bool), int p, bool pullup=1, unsigned int deb=50) : callback(func), pin(p), debounce_time(deb) {
            state = HIGH;
            lastReading = HIGH;
            lastReadingTime = millis();

            if(pullup) {
                pinMode(pin, INPUT_PULLUP);
            } else {
                pinMode(pin, INPUT);
            }
        }

        void callCallback() {
            callback(state);
        }

        bool didStateChange() {
            int reading = digitalRead(pin);
            if(reading != lastReading) {
              lastReading = reading;
              lastReadingTime = millis();
            }

            if(millis()-lastReadingTime > debounce_time) {
                if(lastReading != state) {
                  state = lastReading;
                  return true;
                }
            }
            return false;
        }
};

class SCAnalogInput {
    private:
        int state;
        int lastReading;
        unsigned long int lastReadingTime;

        int pin;
        unsigned int debounce_time;
        int sensitivity;

        void (*callback)(int);

    public:
        SCAnalogInput() {
        }

        SCAnalogInput(void (*func)(int), int p, int s=5, int d=0) : callback(func), pin(p), debounce_time(d), sensitivity(s) {
            state = 0;
            lastReading = 0;
        }

        void callCallback() {
            callback(state);
        }

        bool didStateChange() {
            int reading = analogRead(pin);
            if(lastReading-reading >= sensitivity || lastReading-reading <= -sensitivity) {
              lastReading = reading;
              lastReadingTime = millis();
            }

            
            unsigned long int m = millis();
            if(m-lastReadingTime >= debounce_time) {
                if(lastReading != state) {
                  state = lastReading;
                  return true;
                }
            }
            return false;
        }
};

class SCRedstoneInput {
    private:
        int state;
        int lastReading;
        unsigned long int lastReadingTime;

        int pin;
        int debounce_time;

        void (*callback)(int);

    public:
        SCRedstoneInput() {
        }

        SCRedstoneInput(void (*func)(int), int p, unsigned int d=5) : callback(func), pin(p), debounce_time(d) {
            state = 0;
        }

        bool didStateChange() {
            int reading = map(analogRead(pin), 0, 1023, 0, 15);
            if(reading != lastReading) {
                lastReading = reading;
                lastReadingTime = millis();
            }

            if(millis()-lastReadingTime > debounce_time) {
                if(lastReading != state) {
                    state = lastReading;
                    return true;
                }
            }

            return false;
        }

        void callCallback() {
            callback(state);
        }
};

class SCHotbarInput {
    private:
        int state;
        int lastReading;
        unsigned long int lastReadingTime;

        int pin;
        int debounce_time;

        void (*callback)(int);

    public:
        SCHotbarInput() {
        }

        SCHotbarInput(void (*func)(int), int p, unsigned int d=5) : callback(func), pin(p), debounce_time(d) {
            state = 0;
        }

        bool didStateChange() {
            int reading = map(analogRead(pin), 0, 1023, 1, 9);
            if(reading != lastReading) {
                lastReading = reading;
                lastReadingTime = millis();
            }

            if(millis()-lastReadingTime > debounce_time) {
                if(lastReading != state) {
                    state = lastReading;
                    return true;
                }
            }

            return false;
        }

        void callCallback() {
            callback(state);
        }
};

enum SCSerialState {
    SC_HEADER,
    SC_MESSAGE
};

#ifndef SC_SERIAL_TIMEOUT
#define SC_SERIAL_TIMEOUT 2000
#endif

class SCSerialInput {
  private:
      SCSerialState state;
      int messageLength;
      unsigned long startedWaiting;

      void (*redstone_callback)(int, String);
      void (*player_health_callback)(int);
      void (*player_air_callback)(int);
      void (*player_food_level_callback)(int);
      void (*creeper_callback)(int);
      
  public: 
      SCSerialInput() : state(SC_HEADER), 
                        redstone_callback(0),
                        player_health_callback(0),
                        player_air_callback(0),
                        player_food_level_callback(0),
                        creeper_callback(0) {
      }

      void registerRedstoneSerialCallback(void (*func)(int,String)) {
          redstone_callback = func;
      }
      void registerPlayerHealthCallback(void (*func)(int)) {
          player_health_callback = func;
      }
      void registerPlayerAirCallback(void (*func)(int)) {
          player_air_callback = func;
      }
      void registerPlayerFoodLevelCallback(void (*func)(int)) {
          player_food_level_callback = func;
      }

      void registerCreeperDistanceCallback(void (*func)(int)) {
          creeper_callback = func;
      }

      void loop() {
          switch(state) {
              case SC_HEADER: {
                  if(Serial.available() >= 4 && Serial.read() == 1) {
                      // 0x01 0x53 0x43 <1 byte message length>
                      // 0x01  S    C   <1 byte message length>

                      char s = Serial.read();
                      char c = Serial.read();

                      if(s == 'S' && c == 'C') {
                          messageLength = Serial.read();
                          startedWaiting = millis();
                          state = SC_MESSAGE;
                      }
                  }
                  break;
              }
              case SC_MESSAGE: {
                  if(millis()-startedWaiting > SC_SERIAL_TIMEOUT) {
                      state = SC_HEADER;
                  } else {
                      // this assumes that the message will never be longer
                      // than the Serial buffer (which is usually 64)
                      // If this ever becomes insufficient, we'd 
                      // need to create our own buffer and read in
                      // data as it comes rather than wait until the
                      // full message is in the Serial buffer.
                      if(Serial.available() >= messageLength) {
                          char type = Serial.read();
                          switch(type) {
                              case 0: {// Redstone message
                                  if(redstone_callback) {
                                      // If we have a callback then parse
                                      // our message and call it
                                      int redstoneSignal = Serial.read();
                                      char *buffer = (char*)malloc(messageLength-1);
                                      Serial.readBytes(buffer, messageLength-2);
                                      buffer[messageLength-2] = '\0';
                                      String redstoneID(buffer);
                                      free(buffer);

                                      redstone_callback(redstoneSignal, redstoneID);
                                  } else {
                                      // otherwise, consume the data and ignore it
                                      // to avoid unnecessary memory allocations
                                      for(int i = 0; i < messageLength-1; i++) {
                                          Serial.read();
                                      }
                                  }

                                  break;
                              }
                              case 1: { // Health
                                  int health = Serial.read();

                                  if(player_health_callback) {
                                      player_health_callback(health);
                                  }
                                  break;
                              }
                              case 2: { // Food level
                                  int foodLevel = Serial.read();

                                  if(player_food_level_callback) {
                                      player_food_level_callback(foodLevel);
                                  }
                                  break;
                              }
                              case 3: { // Air
                                  int air = (Serial.read() << 8) + Serial.read();

                                  if(player_air_callback) {
                                      player_air_callback(air);
                                  }

                                  break;
                              }
                              case 4: { // Creeper Distance
                                  int creeperDist = Serial.read();

                                  if(creeper_callback) {
                                      creeper_callback(creeperDist);
                                  }
                                  break;
                              }
                              default:
                                  // unknown type
                                  break;
                          }
                          state = SC_HEADER;
                      }
                  }
                  break;
              }
          }
      }
};


class SerialCraft {
    private:
        unsigned long int baud;
        SCTimer timers[SERIAL_CRAFT_TIMERS];
        int numTimers;

        SCDigitalInput digitalInputs[SERIAL_CRAFT_DIGITAL_INPUTS];
        int numDigitalInputs;

        SCAnalogInput analogInputs[SERIAL_CRAFT_ANALOG_INPUTS];
        int numAnalogInputs;

        SCRedstoneInput redstoneInputs[SERIAL_CRAFT_REDSTONE_INPUTS];
        int numRedstoneInputs;

        SCHotbarInput hotbarInputs[SERIAL_CRAFT_HOTBAR_INPUTS];
        int numHotbarInputs;

        SCSerialInput serialInput;

        bool lastMouseMoveWasZero;
    public:
        SerialCraft(unsigned long int b = 115200) : baud(b), numTimers(0), numDigitalInputs(0), numAnalogInputs(0) {
        }

        void registerRedstoneSerialCallback(void (*func)(int,String)) {
            serialInput.registerRedstoneSerialCallback(func);
        }

        void registerPlayerHealthCallback(void (*func)(int)) {
            serialInput.registerPlayerHealthCallback(func);
        }
        void registerPlayerAirCallback(void (*func)(int)) {
            serialInput.registerPlayerAirCallback(func);
        }
        void registerPlayerFoodLevelCallback(void (*func)(int)) {
            serialInput.registerPlayerFoodLevelCallback(func);
        }
        void registerCreeperDistanceCallback(void (*func)(int)) {
            serialInput.registerCreeperDistanceCallback(func);
        }

        void registerTimerCallback(void (*func)(), unsigned long i) {
            timers[numTimers] = SCTimer(func, i);
            numTimers++;
        }

        void registerDigitalInputCallback(void (*func)(bool), int p, bool pullup=1, unsigned int deb=50) {
            digitalInputs[numDigitalInputs] = SCDigitalInput(func,p,pullup,deb);
            numDigitalInputs++;
        }

        void registerAnalogInputCallback(void (*func)(int), int p, int s=5, int d=0) {
            analogInputs[numAnalogInputs] = SCAnalogInput(func,p,s,d);
            numAnalogInputs++;
        }

        void registerRedstoneInputCallback(void (*func)(int), int p, int d=5) {
            redstoneInputs[numRedstoneInputs] = SCRedstoneInput(func,p,d);
            numRedstoneInputs++;
        }

        void registerHotbarInputCallback(void (*func)(int), int p, int d=5) {
            hotbarInputs[numHotbarInputs] = SCHotbarInput(func,p,d);
            numHotbarInputs++;
        }
        
        void setup() {
            Serial.begin(baud); 
        }

        void loop() {
            for(int i = 0; i < numTimers; i++) {
                if(timers[i].isReady()) {
                  timers[i].callCallback();
                }
            }

            for(int i = 0; i < numDigitalInputs; i++) {
                if(digitalInputs[i].didStateChange()) {
                    digitalInputs[i].callCallback();
                }
            }

            for(int i = 0; i < numAnalogInputs; i++) {
                if(analogInputs[i].didStateChange()) {
                    analogInputs[i].callCallback();
                }
            }

            for(int i = 0; i < numRedstoneInputs; i++) {
                if(redstoneInputs[i].didStateChange()) {
                    redstoneInputs[i].callCallback();
                }
            }

            for(int i = 0; i < numHotbarInputs; i++) {
                if(hotbarInputs[i].didStateChange()) {
                    hotbarInputs[i].callCallback();
                }
            }

            serialInput.loop();
        }

        void setHotbarItem(int i) {
            Serial.print("hotbar ");
            Serial.println(i);
        }

        void updatePlayerInfo() {
            Serial.println("update_player_info");
        }

        void sendRedstoneSignal(String id, unsigned int value) {
            Serial.print("redstone ");
            Serial.print(value);
            Serial.print(" ");
            Serial.println(id);
        }

        void moveMouse(int x, int y) {
            if(x == 0 && y == 0) {
                if(!lastMouseMoveWasZero) {
                    Serial.println("m 0 0");
                    lastMouseMoveWasZero = true;
                }
            } else {
                lastMouseMoveWasZero = false;
                Serial.print("m ");
                Serial.print(x);
                Serial.print(" ");
                Serial.println(y);
            }
        }

        void setTime(unsigned int value) {
            Serial.print("time set ");
            Serial.println(value);
        }

        void startMovingForward() {
            Serial.println("move_forward forward");
        }

        void startMovingBackward() {
            Serial.println("move_forward back");
        }

        void stopMovingForward() {
            Serial.println("move_forward neutral");
        }

        void stopMovingBackward() {
            stopMovingForward();
        }

        void startMovingLeft() {
            Serial.println("move_strafe left");
        }

        void startMovingRight() {
            Serial.println("move_strafe right");
        }

        void stopMovingLeft() {
            Serial.println("move_strafe neutral");
        }

        void stopMovingRight() {
            stopMovingLeft();
        }

        void sendChatMessage(const String &msg) {
            Serial.print("chat ");
            Serial.println(msg);
        }

        void pressLeftMouseButton() {
            Serial.println("left_button_press");
        }

        void releaseLeftMouseButton() {
            Serial.println("left_button_release");
        }

        void pressRightMouseButton() {
            Serial.println("right_button_press");
        }

        void releaseRightMouseButton() {
            Serial.println("right_button_release");
        }

        void startSneaking() {
            Serial.println("move_down");
        }

        void stopSneaking() {
            Serial.println("stop_move_down");
        }

        void startJumping() {
            Serial.println("start_jumping");
        }

        void stopJumping() {
            Serial.println("stop_jumping");
        }
};


#endif
