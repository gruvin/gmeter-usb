# KiCAD Schematic and PCB Design Software #

The gMeter circuit schematic and PCB design is done in free and open source, KiCAD software. KiCAD is available free of charge for Windows, Linux and Mac. However, I have not had much success with the OS X version, so I run the Linux version, under a VMWare virtual machine Ubuntu Desktop v12.04 LTS. (The Windows version is also very stable and works well.)

The project files are in trunk/hardware.

There are two project files, once for the standard (larger) size gMeter (`gMeter.pro`) and one for the smaller version, using the MLF ATmega chip (`gMeter-MLF.pro`).

## Bill of Mterial (BOM) File ##

An (incomplete at time of writing) bill of materials (BOM) Excel spreadsheet file is located at `trunk/hardware/gmeter-bom.xlsx`.

## PDF Schematic and Parts Placement Guides ##

There are PDF versions of the circuit schematics and part placement guide (top layer silk screen) at [trunk/hardware/assembly](https://code.google.com/p/gmeter-usb/source/browse/#svn%2Ftrunk%2Fhardware%2Fassembly).

## Frozen PCB Files ##

When I submit an order to the factor, I take an archive copy of the PCB files for that version. Two of these exist at the time of this writing, in trunk: `hardware-v1.0_frozen` and `hardware-mlf-v1.0_frozen`. These files should never be changed.

## Production Gerber and Drill Files ##

These can be found in the frozen archive folders (see above) in, sub-folders`production` and `production-mlf`.

## Why not Eagle from CADsoft? ##

I get asked this a lot. The answer is simple; "Because it's not open source and this is an open source project."