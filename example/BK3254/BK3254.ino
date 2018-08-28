/*
        GNU GPL v3
        (C) Tomas Kovacik [nail at nodomain dot sk]
        https://github.com/tomaskovacik/

        example for library for A2DP bluetooth modules based on BEKEN corp chip BK3254
*/


#include "BK3254.h"
#include <SoftwareSerial.h>


uint16_t BTState;
uint16_t CallState;
uint16_t MusicState;
uint16_t PowerState;
uint16_t InputSelected;
uint16_t MusicMode;
uint16_t CurrentFrequency;
uint8_t CurrentPreset;
uint16_t currentVolume;
String CallerID = "";

SoftwareSerial swSerial(7, 6); //rxPin, txPin, inverse_logic

BK3254 BT(&swSerial, 5);

#define INITVOLUME "1"

void getInitStates() {
  while (BT.getName() != 1);
  while (BT.getConnectionStatus() != 1);
  while (BT.getPinCode() != 1);
  while (BT.getAddress() != 1);
  while (BT.getMusicStatus() != 1);
  while (BT.getHFPStatus() != 1);
}

void setup() {
  BT.begin();
  Serial.begin(115200);
  Serial.println(F("press h for help"));
  delay(1000);
  getInitStates();
  delay(100);
  while (BT.volumeSet(INITVOLUME) != 1);
}

void printInputSelected();
void printMusicState();
void printBTstate();
void printMusicState();
void printPowerState();
void printMusicMode();
void printAllInfo();
void printCurrentMusicMode();
void printCallState();

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
        Serial.println(F("musicPreviousTrack     l"));
        Serial.println(F("volumeUp               m"));
        Serial.println(F("volumeDown             n"));
        Serial.println(F("volumeSet              o"));
        Serial.println(F("volumeGet              p"));
        Serial.println(F("shutdown               q"));
        Serial.println(F("standby                r"));
        Serial.println(F("powerup                s"));
        Serial.println(F("switchInput            t"));
        Serial.println(F("switchInputToBluetooth u"));
        Serial.println(F("switchInputToCard      v"));
        Serial.println(F("switchInputToAux       x"));
        Serial.println(F("switchInputToFm        y"));
        Serial.println(F("switchInputToUsb       z"));
        Serial.println(F("musicModeRepeatAll     w"));
        Serial.println(F("musicModeRepeatOne     A"));
        Serial.println(F("musicGetCurrentMode    B"));
        Serial.println(F("cardGetCurrentPlayingSongNumber C"));
        Serial.println(F("cardUsbGetSongsCount   D"));
        Serial.println(F("usbGetCurrentPlayingSongNumber E"));
        Serial.println(F("fmStartSearch          F"));
        Serial.println(F("fmStopSearch           G"));
        Serial.println(F("fmGetFreq              H"));
        Serial.println(F("fmTunePreset X=preset         IX"));
        Serial.println(F("fmTuneFreq  (XXXX=freq)    JXXXX"));
        Serial.println(F("fmGetFreq2             K"));
        Serial.println(F("fmGetPreset            L"));
        Serial.println(F("fmGetFreqOfPreset  X=preset    MX"));
        Serial.println(F("getAddress             N"));
        Serial.println(F("getPinCode             O"));
        Serial.println(F("getName                P"));
        Serial.println(F("getConnectionStatus    Q"));
        Serial.println(F("getMusicStatus         R"));
        Serial.println(F("getHFPStatus           S"));
        Serial.println(F("changeName             T(DNW)"));
        Serial.println(F("voicesOn               U(DNW)"));
        Serial.println(F("voicesOff              V(DNW)"));
        Serial.println(F("getVoicesState         X(DNW)"));
        Serial.println(F("goBackOn               Y(DNW)"));
        Serial.println(F("goBackOff              Z(DNW)"));
        Serial.println(F("getGoBack              W(DNW)"));
        Serial.println(F("callOn                 0(DNW)"));
        Serial.println(F("callOff                1(DNW)"));
        Serial.println(F("getCall                2(DNW)"));
        Serial.println(F("reboot                 3(DNW)"));
        Serial.println(F("print all info         4"));
        Serial.println();
        printAllInfo();

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
        BT.musicPreviousTrack();
        break;
      case 'm':
        BT.volumeUp();
        break;
      case 'n':
        BT.volumeDown();
        break;
      case 'o':
        {
          delay(100);
          String str;
          c = 0;
          while (Serial.available() > 0) {
            c = Serial.read();
            str += c;
          }
          BT.volumeSet(str);
        }
        break;
      case 'p':
        BT.volumeGet();
        break;
      case 'q':
        BT.shutdown();
        break;
      case 'r':
        BT.standby();
        break;
      case 's':
        BT.powerup();
        break;
      case 't':
        BT.switchInput();
        break;
      case 'u':
        BT.switchInputToBluetooth();
        break;
      case 'v':
        BT.switchInputToCard();
        break;
      case 'x':
        BT.switchInputToAux();
        break;
      case 'y':
        BT.switchInputToFm();
        break;
      case 'z':
        BT.switchInputToUsb();
        break;
      case 'w':
        BT.musicModeRepeatAll();
        break;
      case 'A':
        BT.musicModeRepeatOne();
        break;
      case 'B':
        BT.musicGetCurrentMode();
        break;
      case 'C':
        BT.cardGetCurrentPlayingSongNumber();
        break;
      case 'D':
        BT.cardUsbGetSongsCount();
        break;
      case 'E':
        BT.usbGetCurrentPlayingSongNumber();
        break;
      case 'F':
        BT.fmStartSearch();
        break;
      case 'G':
        BT.fmStopSearch();
        break;
      case 'H':
        BT.fmGetFreq();
        break;
      case 'I':
        {
          delay(100);
          String str;
          c = 0;
          while (Serial.available() > 0) {
            c = Serial.read();
            str += c;
          }
          BT.fmTunePreset(str);
        }
        break;
      case 'J':
        {
          delay(100);
          String str;
          c = 0;
          while (Serial.available() > 0) {
            c = Serial.read();
            str += c;
          }
          BT.fmTuneFreq(str);
        }
        break;
      case 'K':
        BT.fmGetFreq2();
        break;
      case 'L':
        BT.fmGetPreset();
        break;
      case 'M':
        {
          delay(100);
          String str;
          c = 0;
          while (Serial.available() > 0) {
            c = Serial.read();
            str += c;
          }
          BT.fmGetFreqOfPreset(str);
        }
        break;
      case 'N':
        BT.getAddress();
        break;
      case 'O':
        BT.getPinCode();
        break;
      case 'P':
        BT.getName();
        break;
      case 'Q':
        BT.getConnectionStatus();
        break;
      case 'R':
        BT.getMusicStatus();
        break;
      case 'S':
        BT.getHFPStatus();
        break;
      case 'T':
        {
          delay(100);
          String str;
          c = 0;
          while (Serial.available() > 0) {
            c = Serial.read();
            str += c;
          }
          BT.changeName(str);
        }
        break;
      case 'U':
        BT.voicesOn();
        break;
      case 'V':
        BT.voicesOff();
        break;
      case 'X':
        BT.getVoicesState();
        break;
      case 'Y':
        BT.goBackOn();
        break;
      case 'Z':
        BT.goBackOff();
        break;
      case 'W':
        BT.getGoBack();
        break;
      case '0':
        BT.callOn();
        break;
      case '1':
        BT.callOff();
        break;
      case '2':
        BT.getCall();
        break;
      case '3':
        BT.reboot();
        break;
      case '4':
        printAllInfo();
        break;
    }
  }

  BT.getNextEventFromBT();

  if (BTState != BT.BTState) {
    printBTstate();
    BTState = BT.BTState;
  }

  if (CallState != BT.CallState) {
    printCallState();
    CallState = BT.CallState;
  }

  if (MusicState != BT.MusicState) {
    printMusicState();
    MusicState = BT.MusicState;
  }

  if (PowerState != BT.PowerState) {
    printPowerState();
    PowerState = BT.PowerState;
  }

  if (InputSelected != BT.InputSelected) {
    printInputSelected();
    InputSelected = BT.InputSelected;
  }

  if (MusicMode != BT.MusicMode) {
    printMusicMode();
    MusicMode = BT.MusicMode;
  }

  if (CurrentFrequency != BT.CurrentFrequency) {
    printCurrentFreqency();
    CurrentFrequency = BT.CurrentFrequency;
  }

  if (CurrentPreset != BT.CurrentPreset) {
    printCurrentPreset();
    CurrentPreset = BT.CurrentPreset;
  }

  if (currentVolume != BT.currentVolume) {
    printCurrentVolume();
    currentVolume = BT.currentVolume;
  }
}

void printAllInfo() {
  Serial.println(BT.BT_NAME);
  Serial.print("Pin: "); Serial.println(BT.BT_PIN);
  Serial.print("BT address: "); Serial.println(BT.BT_ADDR);
  printInputSelected();
  printMusicState();
  printBTstate();
  printCallState();
  printCurrentFreqency();
  printCurrentPreset();
  printCurrentVolume();
  printCurrentMusicMode();
}

void printCallState() {
  switch (CallState) {
    case BT.IncomingCall:
      Serial.print("Incomming call: ");
      break;
    case BT.OutgoingCall:
      Serial.print("Outgoing call: ");
      break;
    case BT.CallInProgress:
      Serial.print("Calling: ");
      break;
    case BT.Idle:
      Serial.print("Call ended.");
      break;
  }
  if (CallState != BT.Idle)
    Serial.println(BT.CallerID);
}

void printCurrentMusicMode() {
  Serial.print(F("Current mode: "));
  Serial.println(BT.MusicMode);
}

void printCurrentVolume() {
  Serial.print(F("Current volume level: "));
  Serial.println(BT.currentVolume);
}

void printCurrentFreqency() {
  Serial.print(F("Tunner frequency: "));
  Serial.print(BT.CurrentFrequency);
  Serial.println("MHz");
}

void printCurrentPreset() {
  Serial.print(F("Current preset: "));
  Serial.println(BT.CurrentPreset);
}

void printMusicMode() {
  switch (BT.MusicMode) {
    case (BT.PlayAll):
      Serial.println(F("Music play all"));
      break;
    case (BT.PlayOne):
      Serial.println(F("Music play one"));
      break;
  }
}

void printBTstate() {
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
}

void printMusicState() {
  BT.getCurrentInput();
  switch (BT.MusicState) {
    case (BT.Playing):
      //Serial.println(F("Playing music"));
      if (BT.InputSelected == BT.SD || BT.InputSelected == BT.USB) {
        BT.cardUsbGetSongsCount(); //get number of song on card or USB and currently played song:
        if (BT.InputSelected == BT.SD) BT.cardGetCurrentPlayingSongNumber();
        if (BT.InputSelected == BT.USB) BT.usbGetCurrentPlayingSongNumber();
        Serial.print("Playing song "); Serial.print(BT.CurrentlyPlayingSong); Serial.print(" of "); Serial.print(BT.NumberOfSongs); Serial.println(".");
      }
      break;
    case (BT.Idle):
      Serial.println(F("Music stoped"));
      break;
  }
}

void printInputSelected() {
  switch (BT.InputSelected) {
    case (BT.AUX):
      Serial.println(F("AUX selected"));
      break;
    case (BT.SD):
      Serial.println(F("SD/TF Card selected"));
      break;
    case (BT.BT):
      Serial.println(F("BlueTooth selected"));
      break;
    case (BT.USB):
      Serial.println(F("USB selected"));
      break;
    case (BT.FM):
      Serial.println(F("FM selected"));
      void printFMFreq();
      break;
  }
}

void printPowerState() {
  switch (PowerState) {
    case BT.On:
      Serial.println("Module On");
      break;
    case BT.Off:
      Serial.println("Module Off");
      break;
  }
}

