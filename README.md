# SerialCraft Arduino Library

This Arduino library provides an interface for interacting with the SerialCraft Minecraft mod. Follow these instructions for
getting up and running.

## Install Arduino IDE

First, you'll need the Arduino IDE. You can download it [here](https://www.arduino.cc/en/Main/Software).

## Install Pololu Drivers

If you've purchased the kit for the Advanced Minecraft Controller classes at Children's Museum of Bozeman STEAMlab, then the
Arduino you're using is called a Pololu A-Star Mini LV and it requires installing separate drivers for Windows. Follow [these
instructions, provided by Pololu](https://www.pololu.com/docs/0J61/6.1).

After the drivers have been installed, you should be able to select the Arduino Micro or Arduino Leonardo from the Board
menu as they use the same chip (ATmega 32U4). You can also add a Pololu A-Star 32U4 entry to the Board menu by following
the "Arduino add-on" section [here](https://github.com/pololu/a-star).

## Install the SerialCraft library

Download the [SerialCraft Arduino library](https://github.com/AllwineDesigns/serialcraft-arduino/archive/master.zip). Install the
library by following the instructions under [Importing a zip library](https://www.arduino.cc/en/Guide/Libraries#toc4) on Arduino's site.

## Using SerialCraft Arduino library to interface with SerialCraft Minecraft mod

### Download Minecraft

Minecraft is not necessary to use the SerialCraft Arduino library, but it's intent is to be able to interface with Minecraft. You
can purchase and download Minecraft [here](https://minecraft.net/).

### Install Minecraft Forge

You'll need Minecraft Forge to be able to install the SerialCraft Minecraft mod. The instructions page for installing Minecraft 
Forge can be found [here](http://www.minecraftforge.net/wiki/Installation/Universal). You'll need to install Minecraft Forge
for Minecraft version 1.7.10. Here are video tutorials on how to install it for [Windows](https://www.youtube.com/watch?v=ta74oqCi_vM)
and [Mac](https://www.youtube.com/watch?v=HnTJxLIP41c).

### Install SerialCraft Minecraft mod

You can download the latest SerialCraft mod release [here](https://github.com/AllwineDesigns/SerialCraftMod/releases). You'll
also need to download the jssc library (also from the release page), which SerialCraft depends on.
Unzip both files and place the resulting jar files in the mods directory as explained [here](http://www.minecraftmods.com/how-to-install-mods-for-minecraft-forge/).

Once installed and you enter the game, you can press 'k' by default to list any serial devices connected to your computer. If you
have your Arduino hooked up to your computer, it should be listed there. Close and reopen the menu to refresh the list. Click
connect after inputting the baud rate that your device has been configured to transmit at to start accepting serial events.

Stay tuned for [more documentation](https://github.com/AllwineDesigns/serialcraft-arduino/tree/master/docs) on what serial commands you can send to (or receive from) the SerialCraft mod.
