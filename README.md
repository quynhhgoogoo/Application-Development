# This is my readme file, by Quynh Luong (e1601128)
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
- Step 1 : Boot up RPi, and apply the USB sound card.
- Step 2 : RPi onboard sound card does not have microphone interface. We have to change the default audio device to be USB sound card.
- Step 3 : Use “lsusb” command to check if your USB sound card is mounted
- Step 4 : Use “sudo nano /etc/asound.conf”command and put following content to the file:
- pcm.!default {
  type plug
  slave {
    pcm "hw:1,0"
  }
 }
 ctl.!default {
    type hw
    card 1
 }
- Step 5 : Go to your home directory. Use “nano .asoundrc” command and put the same content to the file.
- Step 6 : Run alsamixer you should be able to see that USB sound card is the default audio device.

If you are using Raspbian Jessie, you have to roll back alsa-utils to an early version.
The newest version of Raspbian (a.k.a. Jessie) comes with a new version of alsa-utils (1.0.28),
which has a bug while recording: it doesnât stop even a ââduration' switch is given, and generates lots of useless audio files.
To fix this problem, we have to downgrade alsa-util to an earlier version (1.0.25).

- Step 1 : Use sudo nano /etc/apt/sources.list command and add the last line:
- deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi
- Step 2 : Run sudo apt-get update
- Step 3 : Run sudo aptitude versions alsa-utils
- Step 4 : Run sudo apt-get install alsa-utils=1.0.25-4
- Step 5 : Reboot (if necessary).
- Step 6 : Run arecord -r44100 -c1 -f S16_LE -d5 test.wav
- Step 7 : Put earphone on. Run aplay test.wav

2. Installation instructions :

2.1 RPi Default Booting & Keyboard Layout :
By default RPi3 boots into X-server mode. This takes more booting time. And in most cases you donât use a display. So the first thing is to disable it.
To do so, you need to attach a HDMI display to it and change configurations. You also need a USB keyboard for this step.
- Step 1 : Open a terminal Accessories
- Step 2 : Run sudo raspi-config
- Step 3 : Select boot options
- Step 4 : Select B2 Console Autologin
- Step 5 : Reboot sudo reboot

2.2 Send IP Address by Email.
When using a Raspberry Pi remotely, you need to know its IP address so that you can connect to it. There are many ways to get the IP address from your Pi.
The simplest way to edit rc.local
- Step 1 : After the reboot, run command sudo nano /etc/rc.local
- Step 2 : Add following lines:

 #!/bin/sh -e
 #
 #rc.local
 #
 #This script is executed at the end of each multiuser runlevel.Make sure that the script will "exit 0" on success or any other value on error.
 #
 #In order to enable or disable this script just change the execution bits.
 #
 #By default this script does nothing.

 #Print the IP address
 sleep 30

 _IP=$(hostname -I) || true
 if [ "$_IP" ]; then
  printf "My IP address is %s\n" "$_IP"
  curl --url http://www.cc.puv.fi/~gc/php/sendMailRPi.php -d email=YourEmail&from=YourRPi3Name
 fi

 exit 0
- Step 3 : The first line sleep 30
- Step 4 : The curl


3. Operating instructions :
- Step 1 : Run "make clean" command to remove the previous connected files.
- Step 2 : Run "make" to connect multi-file.
- Step 3 : Run "./sound.a" command in order to display the sound waveforms.
- Step 4 : Go to this website http://www.cc.puv.fi/~e1601128/sound_log.txt to see the datas.

4. List of files included :
- README.md : contains information about other files in a directory or archive of computer software. 
- makefile : connects seperated files in this project and turns it into multi-file. 
- wave.c : contains functions related to wave execution.
- wave.h : header file of wave.c .
- screen.c : contains functions related to screen display. 
- screen.h : header file of screen.c. 
- comm-c : the communication module via libcurl. 
- comm.h : header file of comm.c. 
- main.c : contains main() function which executes the output of this project.
- sound.php : the server page that receives datas. 


5. Copyright and licensing information.
Source code by Dr. Gao Chao
- Doctor of Science (Technology)
- Principal Lecturer at Vaasan ammattikorkeakoulu, Vaasa University of Applied Sciences

6. Contact information for the distributor or programer.
- email : luongdiemquynh1998@gmail.com
- phone : +358469426841
- facebook address : diemm.quynhh.1
