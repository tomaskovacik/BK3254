/*
        GNU GPL v3
        (C) Tomas Kovacik [nail at nodomain dot sk]
        https://github.com/tomaskovacik/

        example for F-6188 module library
*/


#include "BK3254.h"
#include <SoftwareSerial.h>

uint8_t BTState;
uint8_t CallState;
uint8_t MusicState;
uint8_t PowerState;

SoftwareSerial swSerial(7, 6); //rxPin, txPin, inverse_logic

BK3254 BT(&swSerial, 5);

void getInitStates() {
//  BT.getName();
//  BT.getConnectionStatus();
//  BT.getPinCode();
//  BT.getAddress();
//  BT.getSoftwareVersion();
//  BT.getMusicStatus();
//  BT.getHFPstatus();
}

void setup() {
  BT.begin();
  Serial.begin(115200);
  Serial.println(F("press h for help"));
  getInitStates();
}


void loop() {

  if (Serial.available() > 0)
  {
    // read the incoming byte:
    char c = Serial.read();
    switch (c)
    {
      case 'h': //help
        Serial.println(F("PairingInit                  1"));
        Serial.println(F("PairingExit                  2"));
        Serial.println(F("ConnectLastDevice            3"));
        Serial.println(F("Disconnect                   4"));
        Serial.println(F("callAnsware                  5"));
        Serial.println(F("callReject                   6"));
        Serial.println(F("callHangUp                   7"));
        Serial.println(F("callRedial                   8"));
        Serial.println(F("volumeUp                     9"));
        Serial.println(F("volumeDown                   a"));
        Serial.println(F("languageSwitch               b"));
        Serial.println(F("channelSwitch                c"));
        Serial.println(F("shutdownBT                   d"));
        Serial.println(F("switch input                 e"));
        Serial.println(F("send custom AT+command   f+CMD"));
        Serial.println(F("openPhoneVoice               g"));
        Serial.println(F("show info about module       i"));
        Serial.println(F("memoryClear                  j"));
        Serial.println(F("languageSetNumber        k+num"));
        Serial.println(F("musicTogglePlayPause         l"));
        Serial.println(F("musicStop                    m"));
        Serial.println(F("musicNextTrack               n"));
        Serial.println(F("musicPreviousTrack           o"));
        Serial.println(F("musicFastForward             q"));
        Serial.println(F("musicRewind                  r"));
        Serial.println(F("getName                      s"));
        Serial.println(F("getConnectioStatus           t"));
        Serial.println(F("getPinCode                   u"));
        Serial.println(F("getAddress                   v"));
        Serial.println(F("getSoftwareVersion           w"));
        Serial.println(F("MusicGetStatus               x"));
        Serial.println(F("getHFPstatus                 y"));
        Serial.println(F("StartModule                  z"));
        Serial.println(F("send APT data            A+data"));
        break;
    }
  }

BT.getNextEventFromBT();

if (BTState != BT.BTState) {
  switch (BT.BTState) {
    case BT.Connected:
      Serial.println(F("Bluetooth connected"));
      break;
    case BT.Disconnected:
      Serial.println(F("Bluetooth disconnected"));
      break;
    case BT.Pairing:
      Serial.println(F("Bluetooth in pairing mode"));
      break;
  }
  BTState = BT.BTState;
}

if (CallState != BT.CallState) {
  switch (BT.CallState) {
    case (BT.IncomingCall):
      Serial.println(F("Incoming call:"));
      Serial.println(BT.CallerID);
      break;
    case (BT.OutgoingCall):
      Serial.println(F("Dialing:"));
      Serial.println(BT.CallerID);
      break;
    case (BT.CallInProgress):
      Serial.println(F("Calling:"));
      Serial.println(BT.CallerID);
      break;
  }
  CallState = BT.CallState;
}

if (MusicState != BT.MusicState) {
  switch (BT.MusicState) {
    case (BT.Playing):
      Serial.println(F("Playing music"));
      break;
    case (BT.Idle):
      Serial.println(F("Music stoped"));
      break;
  }
  MusicState = BT.MusicState;
}


}
