#include <SerialCraft.h>

SerialCraft sc;

const int rightJoystickXPin = 5;
const int rightJoystickYPin = 4;

const int leftJoystickXPin = 9;
const int leftJoystickYPin = 8;

const int redLEDPin = 13;
const int orangeLEDPin = 11;
const int yellowLEDPin = 10;
const int greenLEDPin = 5;
const int blueLEDPin = 6;

bool blinkRedLED = false;
bool blinkOrangeLED = false;
bool blinkYellowLED = false;
bool blinkGreenLED = false;
bool blinkBlueLED = false;

bool LEDsOn = false;

void setup() {
  pinMode(redLEDPin, OUTPUT);
  pinMode(orangeLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  
  sc.setup();

  // joystick movement callback
  sc.registerTimerCallback(checkJoysticks, 16);

  // blink callback
  sc.registerTimerCallback(blinkLEDS, 100);

  // light sensor
  sc.registerAnalogInputCallback(lightSensor, 3, 120, 100);

  // buttons/switches
  sc.registerDigitalInputCallback(sneak, 1);
  sc.registerDigitalInputCallback(jump, 0);
  sc.registerDigitalInputCallback(leftSwitch, 2);
  sc.registerDigitalInputCallback(rightSwitch, 20);
  sc.registerDigitalInputCallback(destroyBlock, 4);
  sc.registerDigitalInputCallback(placeBlock, 3);
  sc.registerDigitalInputCallback(leftUpperButton, 12);
  sc.registerDigitalInputCallback(leftLowerButton, 7);

  // dials
  sc.registerRedstoneInputCallback(leftDial, 0);
  sc.registerRedstoneInputCallback(rightDial, 1);

  // SerialCraft events
  sc.registerCreeperDistanceCallback(creeper);
  sc.registerPlayerHealthCallback(health);
  sc.registerPlayerFoodLevelCallback(food);
  sc.registerPlayerAirCallback(air);
  sc.registerRedstoneSerialCallback(redstoneMessage);

}

void loop() {
  sc.loop();
}

void lightSensor(int reading) {
  if(digitalRead(20) == LOW) {
    int t = map(reading, 0, 1023, 18000, 30000);
    sc.setTime(t);
  }
}

void blinkLEDS() {
  LEDsOn = !LEDsOn;
  if(LEDsOn) {
    if(blinkRedLED) {
      digitalWrite(redLEDPin, HIGH);
    }
    if(blinkOrangeLED) {
      digitalWrite(orangeLEDPin, HIGH);
    }
    if(blinkYellowLED) {
      digitalWrite(yellowLEDPin, HIGH);
    }
    if(blinkGreenLED) {
      digitalWrite(greenLEDPin, HIGH);
    }
    if(blinkBlueLED) {
      digitalWrite(blueLEDPin, HIGH);
    }
  } else {
    if(blinkRedLED) {
      digitalWrite(redLEDPin, LOW);
    }
    if(blinkOrangeLED) {
      digitalWrite(orangeLEDPin, LOW);
    }
    if(blinkYellowLED) {
      digitalWrite(yellowLEDPin, LOW);
    }
    if(blinkGreenLED) {
      digitalWrite(greenLEDPin, LOW);
    }
    if(blinkBlueLED) {
      digitalWrite(blueLEDPin, LOW);
    }
  }
}

void food(int f) {
  if(f < 4) {
    blinkOrangeLED = true;
  } else {
    blinkOrangeLED = false;
    float t = 1-(float)f/20;
    float tt = t*t;
    int brightness = 255*tt;
    analogWrite(orangeLEDPin, brightness);
  }
}

void air(int a) {
  if(a < 60) {
    blinkBlueLED = true;
  } else {
    blinkBlueLED = false;
    float t = 1-(float)a/300;
    float tt = t*t;
    int brightness = 255*tt;
    analogWrite(blueLEDPin, brightness);
  }
}

void redstoneMessage(int s, String msg) {
  if(s > 0) {
    float t = (float)s/15;
    float tt = t*t;
    int brightness = 255*tt;
    analogWrite(yellowLEDPin, brightness);
  } else {
    digitalWrite(yellowLEDPin, LOW);
  }
}

void health(int h) {
  if(h < 4) {
    blinkRedLED = true;
  } else {
    blinkRedLED = false;
    float t = 1-(float)h/20;
    float tt = t*t;
    int brightness = 255*tt;
    analogWrite(redLEDPin, brightness);
  }
}

void leftUpperButton(bool buttonReleased) {
  if(buttonReleased) {
    sc.sendRedstoneSignal("leftUpperButton", 0);
  } else {
    sc.sendRedstoneSignal("leftUpperButton", 15);
  }
}

void leftLowerButton(bool buttonReleased) {
  if(buttonReleased) {
    sc.sendRedstoneSignal("leftLowerButton", 0);
  } else {
    sc.sendRedstoneSignal("leftLowerButton", 15);
  }
}

void placeBlock(bool buttonReleased) {
  if(buttonReleased) {
    sc.releaseLeftMouseButton();
  } else {
    sc.pressLeftMouseButton();
  }
}

void destroyBlock(bool buttonReleased) {
  if(buttonReleased) {
    sc.releaseRightMouseButton();
  } else {
    sc.pressRightMouseButton();
  }
}

void leftSwitch(bool switchedOff) {
  if(switchedOff) {
    sc.sendRedstoneSignal("leftSwitch", 0);
  } else {
    sc.sendRedstoneSignal("leftSwitch", 15);
  }
}

void rightSwitch(bool switchedOff) {
  if(switchedOff) {
    sc.sendRedstoneSignal("rightSwitch", 0);
  } else {
    sc.sendRedstoneSignal("rightSwitch", 15);
  }
}

void leftDial(int state) {
  sc.sendRedstoneSignal("leftDial", state);
}

void rightDial(int state) {
  sc.sendRedstoneSignal("rightDial", state);
}

void sneak(bool buttonReleased) {
  if(buttonReleased) {
    sc.stopSneaking();
  } else {
    sc.startSneaking();
  }
}

void jump(bool buttonReleased) {
  if(buttonReleased) {
    sc.stopJumping();
  } else {
    sc.startJumping();
  }
}

void creeper(int dist) {
  if(dist < 8) {
    blinkGreenLED = true;
  } else {
    blinkGreenLED = false;
    float t = 1-(float)constrain(dist, 0, 20)/20;
    float tt = t*t;
    int brightness = 255*tt;
    analogWrite(greenLEDPin, brightness);
  }
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
