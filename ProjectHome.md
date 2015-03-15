# The gMeter, by Gruvin #

![http://gmeter-usb.googlecode.com/svn/wiki/home.attach/gMeter-mlf%20lit.jpg](http://gmeter-usb.googlecode.com/svn/wiki/home.attach/gMeter-mlf%20lit.jpg)

The gMeter (pron: gee-meter) was originally created to provide at-a-glance indication of our multi-user DSL internet bandwidth and to sound an alarm if unreasonably high traffic persists unexpectedly. The unit is stuck to the wall by our internet gateway, where it can be easily seen (and heard), even when the machine's monitor if off, as it usually is.

The prototype was originally tested on a Raspberry Pi embedded computer, where it performed flawlessly. It is now connected to our Ubuntu 12.04 LTS Server internet gateway/firewall machine.

The gMeter has a strip of eight SMD, coloured LED's and one piezo "beeper", for audible alerts. These can be configured in any way desired, through modification of the open source firmware and command-line options passed to the host control program.

Obviously, this board could be used for any type of visual linear data display, like water tank level or greenhouse temperature, each perhaps with a Raspberry Pi computer as the host, collecting data -- or whatever. You can arrange the LED colours in whatever order and have the alarm sound however makes sense for the intended use. Such is the beauty of open source. ;-)

## Two Versions ##
There are currently two versions of the board. One employs an easier to hand-solder, TQFP packaged ATmega88P and is about 3x10cm in overall size. This one also includes BluTooth™ module connectivity for wireless comms, as well as break-out pads for four spare MCU I/O pins.

The second, smaller version is about 2x7cm in size and utilises the tiny MLF-32 packaged ATmega88P. This one does not have the BT or spare I/O pads.

USB end-point connectivity is effected in firmware by the excellent V-USB open source USB stack for 8-bit micros, created and kindly provided free by [Objective Development](http://www.obdev.at).

Here's the larger, first-built version, with BT module port and four spare IO break-out pads...

![http://gmeter-usb.googlecode.com/svn/wiki/home.attach/gMeter-std-first-build.png](http://gmeter-usb.googlecode.com/svn/wiki/home.attach/gMeter-std-first-build.png)

Here's the smaller prototype design, as rendered in KiCAD's 3D View ...

<a href='Hidden comment: 
TODO: change image to photos of completed v1.0 PCB(s) when available
'></a>

![http://gmeter-usb.googlecode.com/svn/wiki/home.attach/gMeter-mlf.jpg](http://gmeter-usb.googlecode.com/svn/wiki/home.attach/gMeter-mlf.jpg)

On my monitor, this image is about 200% of actual size, which is 2x7cm. The large green area is the bottom-side copper layer, while the red artwork is the top-side copper.  (12MHz crystal part are not shown.)

As at 2013-06-27, I am awaiting arrival of the PCBs from the factory in China, for this smaller version.

## See the HOWTO wiki page for more information ##

There is more detailed information in the [wiki](HOWTO.md).