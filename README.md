Here is wiki page with some modules I tested from ali: https://github.com/tomaskovacik/BK3254/wiki/modules-from-ali



# Library for BK3254/BK3266 based bluetooth audio module (F-6888/F6988)

This library supports both **BK3254** and **BK3266** based Bluetooth audio modules. These modules communicate using "ASCII" mode commands (AT+, COM+, BT+, FM+ prefixes).

## BK3254 vs BK3266 Support

- **BK3254**: Original module, uses AT commands (AT+, COM+, BT+, FM+)
- **BK3266**: Newer variant with extended features and slightly different command set
  - Uses BT+ commands for queries (BT+GAD, BT+GNM, BT+GPI) instead of AT+
  - Additional features: equalizer status query, song time/name retrieval
  - Enable BK3266 mode by defining `#define BK3266` in BK3254.h before compilation

The library automatically selects the correct command set based on the `BK3266` preprocessor definition. Both modules support standard playback control, volume management, call handling, and FM radio features.

**Note:** This library is for receiver-only modules. For HY5066SR (transmitter/receiver), use [this repository](https://github.com/tomaskovacik/HY5066SR/).

Supported commands based on this datasheet translate by www.onlinedoctranslator.com are on <a href="https://github.com/tomaskovacik/BK3254/wiki/Supported-commands-and-event-send-from-module">this</a> wiki page.

https://github.com/tomaskovacik/kicad-library/blob/master/library/datasheet/F-6888_bk3254/

https://github.com/tomaskovacik/kicad-library/tree/master/library/datasheet/F-6988_BK3266

# Tested modules

<a href="https://github.com/tomaskovacik/BK3254/wiki/modules-from-ali">Here</a> is a wiki page with test result and links to functional modules.

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
 VBAT  |  via diode to 5V (input for li-ion batery so 4.2V max! )

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

