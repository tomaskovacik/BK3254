# IMPORTANT NOTE

take care what module you buy, where are version which did not have support for all features,read description of what you buy, for example here from aliexpress:

<img src="https://raw.githubusercontent.com/tomaskovacik/BK3254/master/bk3254_only_BT.png">

<a href="https://www.aliexpress.com/item/1-pcs-BK3254-Bluetooth-Module-4-1-F6888-Stereo-Audio-Module-FM-Radio-TF-Card-U/32833631256.html">This module at aliexpress</a> works with my breadboard adapter, at least one I buy few months back.

<a href="https://www.aliexpress.com/item/BK3254-Bluetooth-4-1-stereo-audio-module-support-FM-radio-TF-card-U-disk-infrared-remote/32811949610.html">This one</a> has only BT and AUX funtionality, it make poping noise, then module is switching between internaly generated sounds and BT or while swtching from BT to AUX, probably need to use mute pin for muting poweramp, buttons areon ADC, in this PDF:  https://github.com/tomaskovacik/kicad-library/blob/master/library/datasheet/F-6888_bk3254/F-6888_BK3254_datasheet.pdf. I need to state that module which I receive hase these markings: F-6888, V1.2 2016-8-6, so this is not indication of anything!, shame :(



# Library for BK3254 based bluetooth audio module (F-6888)

Supported commands based on this datasheet translate by www.onlinedoctranslator.com:

https://github.com/tomaskovacik/kicad-library/blob/master/library/datasheet/F-6888_bk3254/BK3254_V1.2_HYT.zh-CN.en.pdf

and this:

https://github.com/tomaskovacik/kicad-library/blob/master/library/datasheet/F-6888_bk3254/BK3254_V1.3_HYT.zh-CN.en.pdf


# How to install

Follow this link to arduino.cc: https://www.arduino.cc/en/Guide/Libraries#toc5

# how to connect BK3254

## directly to computer

this is for testing if your module has serial interface enabled:

BK3254|computer(USB2serial for example)
-------|-------
   RX  |  TX
   TX  |  RX
  GND  |  GND
 VBAT  |  via diode to 5V

## arduino using software serial (UNO, nano..)

BK3254|computer(USB2serial for example)
-------|-------
   RX  |  7 (1st parameter of SoftwareSerial in example)
   TX  |  6 (2nd parameter of SoftwareSerial in example)
 RESET |  5 (defined as resetBTpin in example)
  GND  |  GND
 VBAT  |  via diode to 5V


## arduino using harware serial (mega ..)

BK3254|computer(USB2serial for example)
-------|-------
   RX  |  TX1 (if using Serial1)
   TX  |  RX1 (if using Serial1)
 RESET |  5 (defined as resetBTpin in example)
  GND  |  GND
 VBAT  |  via diode to 5V


# Supported commands and event 

For supported commands and events chek this <a href="https://github.com/tomaskovacik/BK3254/wiki/Supported-commands-and-event-send-from-module">wiki</a>.

# Supported functions

For supported functions chek this <a href="https://github.com/tomaskovacik/BK3254/wiki/Supported-functions">wiki</a> or check example.

# Library variables

On this <a href="https://github.com/tomaskovacik/BK3254/wiki/Variables-set-based-on-module-state">this</a> wiki page is list and variables which are set by librarie when event is received from module.

