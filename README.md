# christmas_light
A christmas light sequence for Raspberry Pi and WS2801 lamps.

Background:
I got a Raspbarry Pi and two strips of WS2801 lamps (100 in total).
What I want to do is some nice christmas lightning when it hangs outside my house.  It's not for a christmas tree.

Some code is borrowed/stolen from an arduino projects I found called MashedPixels

HARDWARE
I have connected these pins to my WS2801 lamps:
PIN 6  - GROUND
PIN 19 - GPIO10 (SPI_MOSI) is connected to DI
PIN 21 - GPIO11 (SPI_CLK) is connected to CI

The power to the WS2801 comes from seperate USB power.

Don't forget to enable SPI with "sudo raspi-config".  It is turned off by default.

------------------------------
MashedPixels note:

* [demo](https://www.youtube.com/watch?v=gfSNxLwvbII)
* [breadboard demo](https://www.youtube.com/watch?v=gfSNxLwvbII)
* [strip demo](https://www.youtube.com/watch?v=dMHQV0NTcpk)
* [Christmas tree demo](https://www.youtube.com/watch?v=ITD6IiKeDy0)