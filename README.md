# arduino-remote
Control any IR device from a browser with a simple serial protocol

I was frustrated that my new phone doesn't have an IR blaster, so I can't turn my TV on or off from the couch without buying a new remote. Instead of doing something so silly, I thought I'd use some spare electronics and build my own remote, from scratch, and make all of it controllable from my phone or computer! What followed was multiple attempts to build a REST API frontend for a serial port, with varying degrees of success.

This repository uses a simple Django web app to connect an Arduino powered IR remote to any browser on your LAN.

## Initial Setup

Right now, the setup process is fairly lengthy, but can be shortened in the future if there's interest.

**Prerequisites**

Hardware

1. A host computer (old laptop, spare raspberry pi)
2. An Arduino supported by the IRremote library
3. A USB cable for flashing and communication with the Arduino
4. An IR LED breakout, or an IR LED and the diode + current limiter required to run it
5. Wires to connect the LED to the Arduino

Software

0. A computer running some flavor of Linux.
1. `arduino-cli`, obtainable from your package manager, or with the Arduino SDK
2. `make`, for flashing the Arduino over CLI. Alternatively, you can use the Arduino IDE.
3. `poetry`, for managing the Python environment.
4. `ufw`, for allowing HTTP traffic from other computers to access the Django app.

**Setting up the hardware**
1. To start, grab an IR LED breakout board, or set up your own (with a protective diode and current limiting resistor)
2. Power the LED from the Arduino's 5V line. 
3. Attach the LED input to Pin 3 of the Arduino, which will generate the NEC pulses.
4. Plug the Arduino USB cable into the USB port of whatever computer is running your Django app.
5. Make sure the Arduino appears under /dev/ttyUSB0 (this is currently a hard coded assumption)

**Flashing the Arduino**

Using Arduino IDE
1. Open remote/remote.ino in the Arduino IDE
2. Click 'Upload', and make sure it completes successfully

Using `arduino-cli`
1. Run `cd remote`
2. Run `make up`


**Setting up the Python environment**
TODO

**Opening the firewall to your LAN**

*Proceed with caution, if you do this wrong you can open your host computer to attack!*

Unless you have an exceptionally unique home network, opening a firewall to your local network is safe, as your home modem disallows all inbound network traffic from the Internet.

I would highly recommend not doing this on a computer that will leave your home network (eg your laptop).

1. Find your local IPv4 address, section `inet` from `ip addr show`
2. Calculate the subnet you want. If your `inet` was something like `192.168.1.27`, just replace the last number with `0/24`, so `192.168.1.0/24`
3. With your subnet (not the one here), run `sudo ufw allow from 192.168.1.0/24`
4. Computers on your home WiFi can now talk to your Django app!

**Running the Django app**
1. From the repo directory, run `./py/arduino_remote_app/run`
2. You should see Django boot up and start listening for traffic!

**Turning the volume up**

All you have to do is go to a browser, type in `host_ip/api/volume/up`, and bam! You should see the volume turn up.

`192.168.1.27/api/volume/up`

**Toggling the power**

Again, go to a browser, and type `host_ip/api/power/toggle`

That's it!

## Extending functionality

TODO (describe NEC, how different tvs might have different codes, receiver.ino)
