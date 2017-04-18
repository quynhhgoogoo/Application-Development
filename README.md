# This is my readme file, by quynhhgoogoo
Raspberry Pi acoustic sensor project

This project will turn a raspberry Pi 3 into an acoustic sensor.

GENERAL CONTENTS :
1. Configuration instructions.
2. Installation instructions.
3. Operating instructions.
4. List of files included.
5. Copyright and licensing information.
6. Contact information for the distributor or programer.

1. Configuration

1.1 Hardwave configuration
A raspberry Pi 2 is recommended. If a older version of Pi is used, corresponding
configuration might be changed.
The Pi is mounted with a USB sound card, and plugged in a microphone.
It is recommonded to have Ethernet connection for your PI.

1.2 Software configuration

The USB sound card has to be set as default audio device. To do so, you need
to modify two files with following contents.

First, you need to set USB Sound Card as Default:
Step 1 : Boot up RPi, and apply the USB sound card.
Step 2 : RPi onboard sound card does not have microphone interface. We have to change the default audio device to be USB sound card.
Step 3 : Use “lsusb” command to check if your USB sound card is mounted
Step 4 : Use “sudo nano /etc/asound.conf”command and put following content to the file:
pcm.!default {
  type plug
  slave {
    pcm "hw:1,0"
  }
}
ctl.!default {
    type hw
    card 1
}
Step 5 : Go to your home directory. Use “nano .asoundrc” command and put the same content to the file.
Step 6 : Run alsamixer you should be able to see that USB sound card is the default audio device.

If you are using Raspbian Jessie, you have to roll back alsa-utils to an early version.
The newest version of Raspbian (a.k.a. Jessie) comes with a new version of alsa-utils (1.0.28),
which has a bug while recording: it doesnât stop even a ââduration' switch is given, and generates lots of useless audio files.
To fix this problem, we have to downgrade alsa-util to an earlier version (1.0.25).

Step 1 : Use sudo nano /etc/apt/sources.list command and add the last line:
deb http://mirrordirector.raspbian.org/raspbian/ jessie main contrib non-free rpi
#Uncomment line below then 'apt-get update' to enable 'apt-get source'
#deb-src http://archive.raspbian.org/raspbian/ jessie main contrib non-free rpi
deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi
Step 2 : Run sudo apt-get update

