# Introduction #

The gMeter PC board is designed to use a solder-less 'pogo-pin' programming connector. This is why the ISP programming pads have no holes. They are however laid out the same as the standard AVR 6-pin ISP header pins, with pin-1 indicated by the only square pad. I did this simply because I wanted the board to have a cleaner look, once ready for use.

Here's my home made pogo-pin interface, using a clothes peg for spring-loading. The target board gets its ISP pads placed beneath the pogo pins, for programming.

![http://gmeter-usb.googlecode.com/svn/wiki/home.attach/pogo-isp.jpg](http://gmeter-usb.googlecode.com/svn/wiki/home.attach/pogo-isp.jpg)

The 0.68mm pogo pins fit into standard 0.8mm PCB holes, for soldering. You can plug the standard 6-hole ISP socket directly over the upper, protruding pogo pin barrels, like my [gProg](https://code.google.com/p/gruvin9x/wiki/GProg) device is connected in the photo above.

The pogo pins are soldered to a small carrier PCB, then glued to the clothes peg. (Wooden pegs work best. But I didn't have any.) The far end of the clothes peg is depressed to lift the pogo pins and release the PCB. The peg's spring tension seems about right to match the springs of six pogo pins, though it really isn't very critical.

Pogo pins are individually spring loaded, usually with a sharp point and sort of resemble miniature shock absorbers. I bought mine on eBay, by searching "pogo pins", to find 0.68mm versions. The full description was, "10pcs P50-B1 Dia 0.68mm Length 16mm 75g Spring Test Probe Pogo Pin".

![http://gmeter-usb.googlecode.com/svn/wiki/home.attach/pogo-pins.jpg](http://gmeter-usb.googlecode.com/svn/wiki/home.attach/pogo-pins.jpg)

Instead of setting up a solderless pogo-pin system, you could simply surface-mount-solder a 3x2 pin array or wires to the gMeter PCB pads. A through-hole version of 3x2 pin header would probably work best in this instance.