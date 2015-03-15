# Introduction #

Some brief notes about the two board designs and their firmware, as well as the host system software, which communicates with the USB board.

# V-USB from Objective Development #

This project was made possible through the excellent [V-USB project](http://www.obdev.at/products/vusb/index.html), from Objective Development.

There, you will find all the documentation and example projects needed to fully understand the code here-in and to make your own USB capable 8-bit micro projects.

In the meantime, here are some quick notes to help get gMeter working quickly.

# Flashing Firmware #



## The Standard (larger) gMeter Board ##

<img src='http://gmeter-usb.googlecode.com/svn/wiki/home.attach/gMeter-std-first-build.png' width='320'>

The latest (development) firmware source files are located at <a href='https://code.google.com/p/gmeter-usb/source/browse/#svn%2Ftrunk%2Ffirmware'>trunk/firmware</a>. You should check out the files with Subversion (svn), using the instructions on the main <a href='https://code.google.com/p/gmeter-usb/source/checkout'>Source</a> page, from the menu above.<br>
<br>
The firmware I use is compiled under AVR-GCC v4.7.2, on an Apple Mac, running OS X 10.8.3 (Mountain Lion). But it should compile equally fine under AVR-GCC on any other platform, too.<br>
<br>
On a Unix system, assuming you have AVR-GC installed, compiling is a simple matter of ...<br>
<pre><code>$ cd gmeter-usb/firmware<br>
$ make<br>
</code></pre>

I have no idea how that is done under Windows. But I'd assume it's very similar.<br>
<br>
You will need to set the 'fuses' in a brand new ATmega88P on your board. You can do this from the <code>firmware</code> directory as follows ...<br>
<br>
<pre><code>$ . wfuses<br>
</code></pre>

I use bash as my shell, so that dot (.) tells bash to 'source' the contents of the file wfuses and execute the commands there-in. Here's what is in wfuses ...<br>
<br>
<pre><code>avrdude -c usbasp -P usb -p atmega88p -B8 -u -U lfuse:w:0xf7:m -U hfuse:w:0xd5:m<br>
# -U efuse:w:0xf9:m<br>
</code></pre>

I commented out the efuse setting, because it always fails verification with my version of AVRDUDE. However, I do program it at least once, ignoring the verification error, before doing that. Perhaps you'll have better luck with AVR Studio, under Windows?<br>
<br>
The -B8 argument is required to slow down the programmer, so it will work with the factory default internal oscillator in the chip, because the external 12.0MHz crystal oscillator is not enabled until the fuse settings are programming. Once the 12MHz oscillator is running, you don't need to -B8 any more.<br>
<br>
To flash the firmware code into the ATmega88P, there's a similar process, using the file wflash ...<br>
<br>
<pre><code>$ . wflash<br>
</code></pre>

That file contains ...<br>
<pre><code>avrdude -c usbasp -P usb -p atmega88p -U flash:w:main.hex<br>
</code></pre>

Obviously, you need to change the <code>-c usbasp</code> to match the type of programmer you are actually using.<br>
<br>
<b>If you're using Windows</b> and prefer to use the Atmel AVR Studio suite to set the fuses and burn the Flash, then by all means go ahead.<br>
<br>
<h3>An ATmega48 Will Also Work</h3>

At the time of writing, the Flash and RAM usage for the firmware is as follows ...<br>
<pre><code>ROM: 1878 bytes (data=2)<br>
RAM: 52 bytes<br>
</code></pre>

That means you can easily use the smaller capacity ATmega48 chip (4K Flash), should they happen to be more readily available. I plan to use a '48 from my stock for the compact MLF version, below.<br>
<br>
<h2>The MLF (compact) gMeter Board</h2>

Not yet built. Firmware not yet written -- although it will be almost identical to the standard version -- just minus any BlueTooth serial port code, which doesn't exist in the standard version either at the time of this writing.<br>
<br>
Fuse and Flash programming will be the same as for the standard board, as noted above.<br>
<br>
<h2>The Host Software gMeterControl</h2>

Communicating with the gMeter via USB requires the <code>libusb</code> libraries to be installed on the host system. These are available at <a href='http://libusb.org'>http://libusb.org</a>. (I might even be relying on the legacy ​libusb-compat version? Not entirely sure. I have both installed, in any case.)<br>
<br>
Windows is an issue. Apparently, you need a custom made driver DLL file for each <code>libusb</code> device. There are tools, somewhere, to get that done. Apparently, you can just put your custom DLL file in the same folder as the host control program -- gMeterControl.exe in this case. I do not use Windows, so I have not been down that path. Nor do I have any experience using GCC under Windows for creating command line executables, though I've seen it can be easily done.<br>
<br>
Those issues aside, building the gMeterControl program under a Unix style OS should be as simple as ...<br>
<br>
<pre><code>$ cd trunk/host<br>
$ make<br>
</code></pre>

<b>GCC Version</b>: I'm using the Apple supplied GCC/LLVM v4.2.1 on my Mac and GCC v4.6.3 on Ubuntu and Debian Squeeze on the Raspberry Pi. No differences in coding are required between these versions.<br>
<br>
The program will output usage hints, if run without any command line arguments ...<br>
<pre><code>$ ./gMeterControl <br>
usage:<br>
  ./gMeterControl test -- runs a communications an LED/alarm test.<br>
  ./gMeterControl 0:1:2:3:4:5:6:7:8 [alarm] -- set LED level. Optionally turn on alarm.<br>
  ./gMeterControl alarm on:off -- set audible alarm.<br>
</code></pre>

So for example, if you want to have the gMeter light up its lower 5 LEDs and sound the alarm ...<br>
<pre><code>$ ./gMeterControl 5 alarm<br>
</code></pre>

To silence the alarm, you can either send the same command, omitting '<code>alarm</code>'  or run ...<br>
<pre><code>$ ./gMeterControl alarm off<br>
</code></pre>

Running <code>gMeterControl test</code>, will thoroughly test USB communications and then run a sequence of LEDs and a "beep", assuming everything is working right.<br>
<br>
NOTE: On my Apple MAC, running OX 10.8.3, it seems to take gMeterControl (<code>usblib</code>, actually) a second or more to find the gMeter USB device. However, under Ubuntu Linux and on a Raspberry Pi, the command completes seemingly instantly. I have no idea why the Apple system is slower.<br>
<br>
If you wanted to use the gMeter to display rapidly changing data,  I would suggest custom writing the host control program for the purpose, such that the device is opened just once and then sent multiple commands rapidly, before finally getting close at program exit.