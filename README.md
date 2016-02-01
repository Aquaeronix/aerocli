Aquaeronix: Tools for Accessing the Aquaero5(R) USB Device
==========================================================

[![BuildStatus](https://travis-ci.org/Aquaeronix/aerocli.svg?branch=stable)]
(https://travis-ci.org/Aquaeronix/aerocli)

&copy; 2012 lynix <lynix47@gmail.com>, 

&copy; 2013 JinTu <JinTu@praecogito.com> lynix <lynix47@gmail.com>, 

&copy; 2014 barracks510 <barracks510@gmail.com>, 

&copy; 2015 barracks510 <barracks510@gmail.com>
 

SUMMARY 
---------------- 
Aquaeronix aims at providing a C interface for accessing the Aquaero5(R) USB
device by 'Aqua Computer' (http://www.aqua-computer.de).

It consists of a set of functions for data access and conversion, and a
command-line tool using these functions as an example implementation.


REQUIREMENTS 
---------------- 
Unlike its predecessor, `aerotools`, which targets the Aquaero(R) 4.00),
Aquaeronix currently uses the USB HIDDEV interface provided by the Linux kernel
via the `/dev/usb/hiddev?` device nodes, so no dependencies for this.


BUILDING 
---------------- 
To build the main components of the project simply issue `./configure && make`
in the project root. Compiled binaries will reside in the subdirectory the were
originated in.  This software may be permanantly installed and uninstalled using
the commands `make install` and `make uninstall` respectively. 

You may also use the precompiled RPMs located at [my
repositories](http://unintel.tk). Additional addons may be found under the
Aquaeronix github page.


SETUP 
---------------- 
To be able to query the Aquaero5(R) device you have to set appropriate access
rights for the device node.

You can either do this manually by identifying the device node using `lsusb`
(looking for the Vendor- and Product-ID), or just install a udev rule like this
one:

`ATTRS{idVendor}=="0c70", ATTRS{idProduct}=="f001", GROUP="aquaero",
MODE="0640"`

This will give all members of the `aquaero` group read access to the device.

As the Aquaero5(R) identifies itself as multiple devices (USB keyboard, mouse
and the actual device we want to query) you have to examine which device node
represents the data source.

In my case, there is `/dev/usb/hiddev[0-2]` which all match the udev rule
provided above. The correct one for me is `/dev/usb/hiddev0`, but I don't know
whether it is always the first one. Just try as stated under USAGE - if you
choose the wrong one there will simply be no output at all.


USAGE: aerocli 
---------------- 
`aerocli`, as stated above, is the example implementation of a command-line tool
that uses the provided query - and format conversion functions provided by
Aquaeronix.

 - To query the first device found (via autodiscovery), simply issue `aerocli`.

 - To query a specific device (if you have more than one attached to your
     system) simply issue `aerocli -d /dev/usb/hiddevX` (see SETUP for the
     meaning of X).

 - To get a more script-friendly output in the form of `KEY=VALUE` pairs just
     add `-o export`. For more comprehensive output in both default and export
     modes, use `-a`, e.g. `-a -o default` or `-a -o export`.

 - To set software sensor values use `-s SENSOR:VALUE` i.e. `-s 1:30.00` or `-s
     1:11.11 -s 2:22.22 -s 3:33.33`.

Note: Multiple software sensor values must be sent at once. If aerocli is run
again and any sensor value is set, all other unspecified sensors are set to
default (disconnected).

 - To synchronize the Aquaero5(R) time with your system time use `-T`.

 - To set a device/sensor name use `-n REFERENCE:INDEX:VALUE` i.e. `-n
     "sensors:1:Sensor 1"`.

 - To get a list of the device/sensor name references and all default names,
     simply omit the argument to `-n`.
  

BUGS / CONTACT 
---------------- 
Feel free to report any bugs you find using the 'issues' function on GitHub. If
you wish to contact the authors, you can drop them an email. You may contact
barracks510 at barracks510@gmail.com. For lynix, you might wish to use his GPG
key, #4804CCA9 on keys.gnupg.net


LICENSE 
---------------- 
This program is published under the terms of the GNU General Public License,
version 3. See the file 'LICENSE' for more information.

