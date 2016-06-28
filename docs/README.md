# SerialCraft object

The SerialCraft object provides a event loop that allows the programmer to register callback
functions when certain events happen, such as pressing a button, turning a dial or receiving 
a certain events Minecraft. To use the SerialCraft library, you must include it at the top of
your program. You then define a single SerialCraft object at the top of your
Arduino sketch and call the setup() and loop() methods in the required setup() and loop() Arduino 
functions. In setup(), you also register any callbacks you want to respond to. 

## Basic Usage

Here's a basic example (the BasicChat example, which can be loaded from the libraries - SerialCraft - digital 
menu in the Arduino IDE). This program requires a button be hooked up to pin 7 of your Arduino.

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

The program above tells your Arduino to send a Minecraft chat message whenever the button hooked up to pin 7
is pressed. You can open the Serial monitor (magnifying glass in the top right corner), and see the chat
message that will be sent to the SerialCraft Minecraft mod, which will make your character send a message
in the game. Make sure you close the Serial monitor before connecting your Arduino to the SerialCraft mod
as only one program can be communicating with the Arduino at a time.

## Registering Callbacks

In the main setup() function, you can register additional callbacks that will be run in response to certain events. The
available callbacks you can register are listed below. Each callback must be a function that you define
somewhere in your program. Each callback takes certain arguments, which will be described below.

### Minecraft SerialCraft mod callbacks

These callbacks occur only when your Arduino is connected over serial to the SerialCraft mod.

#### sc.registerRedstoneSerialCallback(redstoneSerial)

The redstone serial callback is called when the Redstone Serial Message block detects a redstone signal
change (such as powering it with a lever or button). When you place the Redstone Serial Message block
a text field appears where you type in a message that is sent along with the redstone signal strength
to the callback. A redstone serial callback could have the following definition:

    void redstoneSerial(int s, String id) {
      if(id == "test") {
        if(s > 0) {
          digitalWrite(13, HIGH);
        } else {
          digitalWrite(13, LOW);
        }
      }
    } 

The callback is executed with the redstone signal strength passed to the variable `s` (will be in the range 0-15),
and the message that you typed into the Redstone Serial Message block will be passed to the `id` variable. The code
above checks if the signal strength is greater than 0, the message block is powered and we tell the Arduino to 
set pin 13 to HIGH. This could be used to turn on an LED, for example. If the signal strength is 0, the message block
is not powered and we tell the Arduino to set pin 13 to LOW. This would turn an LED off.

#### sc.registerPlayerHealthCallback(health)

The player health callback is called whenever your Minecraft character's health changes, such as when you take damage
or heal damage. The callback is passed your health value, which ranges from 0 (you died), to 20 (full health). You can
use this value to control the brightness of an LED such as in the example below (this is taken from the PlayerHealth
sketch that can be opened from the libraries - SerialCraft - indicators menu in the Arduino IDE). If your Arduino
has a LED connected to pin 11, the brightness of that LED will reflect how much health you have. 

    void health(int h) {
      analogWrite(11, map(h, 0, 20, 0, 255));
    }

#### sc.registerPlayerAirCallback(air)

The player air callback is called whenever your Minecraft character's air supply changes, such as when you swim
under water or surface after being under water. The callback is passed your air supply value, which ranges from 0 
(you're suffocating), to 300 (full air supply). This example is similar to the one above for health. The callback
below controls the brightness of an LED connected to pin 11.

    void air(int a) {
      analogWrite(11, map(a, 0, 300, 0, 255));
    }

#### sc.registerPlayerFoodLevelCallback(food)

The player food level callback is called whenever your Minecraft character's food level changes, such as when you
eat food, or your hunger level drops from sprinting or jumping. The callback is passed your food level value, 
which ranges from 0 (you're starving), to 20 (food level maxed). The callback below controls the brightness of an 
LED connected to pin 11.

    void food(int f) {
      analogWrite(11, map(f, 0, 20, 0, 255));
    }


#### sc.registerCreeperDistanceCallback(creeper)

The creeper distance callback is called when the distance to the nearest creeper changes. This can be helpful to
give the player more time to respond to an incoming creeper attack. See the CreeperAlert example (in the libraries -
SerialCraft - indicators menu in the Arduino IDE) for an example that turns on an LED when the creeper comes within
20 blocks and gets brighter as it gets closers. Once under 8 blocks, the LED begins to blink. Here's a simpler example
that just shows how to turn on an LED connected to pin 11 if a creeper is within 10 blocks of the player:

    void creeper(int dist) {
      if(dist <= 10) {
        digitalWrite(11, HIGH);
      } else {
        digitalWrite(11, LOW);
      }
    }

The dist variable passed to the creeper callback ranges from 0-255.

### Analog callbacks

The follow callbacks can be registered to be run in response to changes in an analog signal connected to a specified pin
of the Arduino.

#### sc.registerAnalogInputCallback(analog, p)

TODO


