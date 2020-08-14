# MacroPad
You will need to import Keyboard.h and add the Keypad library to your arduino IDE

The Arduino Pro Micro requires you to install Sparkfun AVR Boards by adding this url to the boards manager urls:

https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json

also make sure you choose the right voltage and speed for your board before flashing the sketch

implemented color signaling for different key pages, but actual key page implementation hasn't been implemented yet.

current config is top 5 keys correspond to : F13 to F17
bottom row press : CTRL-ALT-6 to CTRL-ALT-0
