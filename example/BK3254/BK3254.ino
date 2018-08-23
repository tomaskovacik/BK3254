/*
        GNU GPL v3
        (C) Tomas Kovacik [nail at nodomain dot sk]
        https://github.com/tomaskovacik/

        example for F-6188 module library
*/


#include "BK3254.h"
#include <SoftwareSerial.h>

uint16_t BTState;
uint16_t CallState;
uint16_t MusicState;
uint16_t PowerState;
uint16_t InputSelected;
uint16_t MusicMode;

SoftwareSerial swSerial(7, 6); //rxPin, txPin, inverse_logic

BK3254 BT(&swSerial, 5);

void getInitStates() {
  BT.getName();
  BT.getConnectionStatus();
  BT.getPinCode();
  BT.getAddress();
  BT.getMusicStatus();
  BT.getHFPStatus();
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
        Serial.println(F("resetModule            a"));
        Serial.println(F("pairingInit            b"));
        Serial.println(F("connectLastDevice      c"));
        Serial.println(F("disconnect             d"));
        Serial.println(F("callAnsware            e"));
        Serial.println(F("callReject             f"));
        Serial.println(F("callHangUp             g"));
        Serial.println(F("callRedial             i"));
        Serial.println(F("musicTogglePlayPause   j"));
        Serial.println(F("musicNextTrack         k"));
        Serial.println(F("fmNextTrack            l"));
        Serial.println(F("musicPreviousTrack     m"));
        Serial.println(F("fmPreviousTrack        n"));
        Serial.println(F("volumeUp               o"));
        Serial.println(F("volumeDown             p"));
        Serial.println(F("volumeSet              q"));
        Serial.println(F("volumeGet              r"));
        Serial.println(F("shutdown               s"));
        Serial.println(F("standby                t"));
        Serial.println(F("powerup                u"));
        Serial.println(F("switchInput            v"));
        Serial.println(F("switchInputToBluetooth x"));
        Serial.println(F("switchInputToCard      y"));
        Serial.println(F("switchInputToAux       z"));
        Serial.println(F("switchInputToFm        w"));
        Serial.println(F("switchInputToUsb       A"));
        Serial.println(F("musicModeRepeatAll     B"));
        Serial.println(F("musicModeRepeatOne     C"));
        Serial.println(F("cardGetCurrentPlayingSongNumber D"));
        Serial.println(F("cardUsbGetSongsCount   E"));
        Serial.println(F("usbGetCurrentPlayingSongNumber F"));
        Serial.println(F("fmStartSearch          G"));
        Serial.println(F("fmStopSearch           H"));
        Serial.println(F("fmGetFreq              I"));
        Serial.println(F("fmTunePreset           J"));
        Serial.println(F("fmTuneFreq             K"));
        Serial.println(F("fmGetFreq2             L"));
        Serial.println(F("fmGetPreset            M"));
        Serial.println(F("fmGetFreqOfPreset      N"));
        Serial.println(F("getAddress             O"));
        Serial.println(F("getPinCode             P"));
        Serial.println(F("getName                R"));
        Serial.println(F("getConnectionStatus    S"));
        Serial.println(F("getMusicStatus         T"));
        Serial.println(F("getHFPStatus           U"));
        Serial.println(F("changeName             V"));
        Serial.println(F("voicesOn               X"));
        Serial.println(F("voicesOff              Y"));
        Serial.println(F("getVoicesState         Z"));
        Serial.println(F("goBackOn               W"));
        Serial.println(F("goBackOff              0"));
        Serial.println(F("getGoBack              1"));
        Serial.println(F("callOn                 2"));
        Serial.println(F("callOff                3"));
        Serial.println(F("getCall                4"));
        Serial.println(F("reboot                 5"));
        Serial.println(F("musicGetCurrentMode                 6"));
        break;
      case 'a':
        BT.resetModule();
        break;
      case 'b':
        BT.pairingInit();
        break;
      case 'c':
        BT.connectLastDevice();
        break;
      case 'd':
        BT.disconnect();
        break;
      case 'e':
        BT.callAnsware();
        break;
      case 'f':
        BT.callReject();
        break;
      case 'g':
        BT.callHangUp();
        break;
      case 'i':
        BT.callRedial();
        break;
      case 'j':
        BT.musicTogglePlayPause();
        break;
      case 'k':
        BT.musicNextTrack();
        break;
      case 'l':
        BT.fmNextTrack();
        break;
      case 'm':
        BT.musicPreviousTrack();
        break;
      case 'n':
        BT.fmPreviousTrack();
        break;
      case 'o':
        BT.volumeUp();
        break;
      case 'p':
        BT.volumeDown();
        break;
      case 'q':
        //  BT.volumeSet();
        break;
      case 'r':
        BT.volumeGet();
        break;
      case 's':
        BT.shutdown();
        break;
      case 't':
        BT.standby();
        break;
      case 'u':
        BT.powerup();
        break;
      case 'v':
        BT.switchInput();
        break;
      case 'x':
        BT.switchInputToBluetooth();
        break;
      case 'y':
        BT.switchInputToCard();
        break;
      case 'z':
        BT.switchInputToAux();
        break;
      case 'w':
        BT.switchInputToFm();
        break;
      case 'A':
        BT.switchInputToUsb();
        break;
      case 'B':
        BT.musicModeRepeatAll();
        break;
      case 'C':
        BT.musicModeRepeatOne();
        break;
      case 'D':
        BT.cardGetCurrentPlayingSongNumber();
        break;
      case 'E':
        BT.cardUsbGetSongsCount();
        break;
      case 'F':
        BT.usbGetCurrentPlayingSongNumber();
        break;
      case 'G':
        BT.fmStartSearch();
        break;
      case 'H':
        BT.fmStopSearch();
        break;
      case 'I':
        BT.fmGetFreq();
        break;
      case 'J':
        // BT.fmTunePreset();
        break;
      case 'K':
        // BT.fmTuneFreq();
        break;
      case 'L':
        BT.fmGetFreq2();
        break;
      case 'M':
        BT.fmGetPreset();
        break;
      case 'N':
        //  BT.fmGetFreqOfPreset();
        break;
      case 'O':
        BT.getAddress();
        break;
      case 'P':
        BT.getPinCode();
        break;
      case 'R':
        BT.getName();
        break;
      case 'S':
        BT.getConnectionStatus();
        break;
      case 'T':
        BT.getMusicStatus();
        break;
      case 'U':
        BT.getHFPStatus();
        break;
      case 'V':
        BT.changeName();
        break;
      case 'X':
        BT.voicesOn();
        break;
      case 'Y':
        BT.voicesOff();
        break;
      case 'Z':
        BT.getVoicesState();
        break;
      case 'W':
        BT.goBackOn();
        break;
      case '0':
        BT.goBackOff();
        break;
      case '1':
        BT.getGoBack();
        break;
      case '2':
        BT.callOn();
        break;
      case '3':
        BT.callOff();
        break;
      case '4':
        BT.getCall();
        break;
      case '5':
        BT.reboot();
        break;
      case '6':
        BT.musicGetCurrentMode();
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
        Serial.println(F("Incoming call: "));
        Serial.println(BT.CallerID);
        break;
      case (BT.OutgoingCall):
        Serial.println(F("Dialing: "));
        Serial.println(BT.CallerID);
        break;
      case (BT.CallInProgress):
        Serial.println(F("Calling: "));
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

  if (InputSelected != BT.InputSelected) {
    switch (BT.InputSelected) {
      case (BT.AUX):
        Serial.println(F("AUX selected"));

        break;
      case (BT.SDcard):
        Serial.println(F("SDCard selected"));
        break;
      case (BT.Bluetooth):
        Serial.println(F("BT selected"));
        break;
      case (BT.USB):
        Serial.println(F("USB selected"));
        break;
    }
    InputSelected = BT.InputSelected;
  }
  if (MusicMode != BT.MusicMode) {
    switch (BT.MusicMode) {
      case (BT.PlayAll):
        Serial.println(F("Music play all"));
        break;
      case (BT.PlayOne):
        Serial.println(F("Music play one"));
        break;
    }
    MusicMode = BT.MusicMode;
  }
}
