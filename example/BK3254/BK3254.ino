/*
       GNU GPL v3
       (C) Tomas Kovacik [nail at nodomain dot sk]
       https://github.com/tomaskovacik/

       example for library for A2DP bluetooth modules based on BEKEN corp chip BK3254 and BK3266
*/

#include "BK3254.h"

#define resetBTpin 5

BK3254::bluetooth BTState;
BK3254::call CallState;
BK3254::music MusicState;
BK3254::power PowerState;
BK3254::input InputSelected;
BK3254::playmode ModeOfPlay;
uint16_t CurrentFrequency;
uint8_t CurrentPreset;
uint8_t currentVolume;
String CallerID = "";
uint16_t time = 0;
uint16_t timeout = 500;

SoftwareSerial swSerial(7, 6); //rxPin, txPin, inverse_logic

BK3254 BT(&swSerial, resetBTpin);

#define INITVOLUME "1"

void getInitStates() {
  time = millis();
  while (BT.getName() != 1 && time - millis() < timeout);
  time = millis();
  while (BT.getConnectionStatus() != 1 && time - millis() < timeout);
  time = millis();
  while (BT.getPinCode() != 1 && time - millis() < timeout);
  time = millis();
  while (BT.getAddress() != 1 && time - millis() < timeout);
  time = millis();
  while (BT.getMusicStatus() != 1 && time - millis() < timeout);
  time = millis();
  while (BT.getHFPStatus() != 1 && time - millis() < timeout);
}

void setup() {
  BT.begin();
  Serial.begin(115200);
  Serial.println(F("press h for help"));
  delay(1000);
  getInitStates();
  delay(100);
  time = millis();
  while (BT.volumeSet(INITVOLUME) != 1 && time - millis() < timeout);
}

void printInputSelected();
void printMusicState();
void printBTstate();
void printMusicState();
void printPowerState();
void printModeOfPlay();
void printAllInfo();
void printCurrentModeOfPlay();
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
        Serial.println(F("fmTunePreset XX=01-99        IX"));
        Serial.println(F("fmTuneFreq  (XXXX=0981-1080    JXXXX"));
        Serial.println(F("fmGetFreq2             K"));
        Serial.println(F("fmGetPreset            L"));
        Serial.println(F("fmGetFreqOfPreset  XX=01-99    MX"));
        Serial.println(F("getAddress             N"));
        Serial.println(F("getPinCode             O"));
        Serial.println(F("getName                P"));
        Serial.println(F("getConnectionStatus    Q"));
        Serial.println(F("getMusicStatus         R"));
        Serial.println(F("getHFPStatus           S"));
        Serial.println(F("changeName             T"));
        Serial.println(F("voicesOn               U"));
        Serial.println(F("voicesOff              V"));
        Serial.println(F("getVoicesState         X"));
        Serial.println(F("goBackOn               Y"));
        Serial.println(F("goBackOff              Z"));
        Serial.println(F("getGoBack              W"));
        Serial.println(F("callOn                 0"));
        Serial.println(F("callOff                1"));
        Serial.println(F("getCall                2"));
        Serial.println(F("reboot                 3"));
        Serial.println(F("print all info         4"));
        Serial.println(F("change pin             5+PIN"));
        Serial.println(F("Get autoplay status    6"));
        Serial.println(F("Autoplay On            7"));
        Serial.println(F("Autoplay Off           8"));
        Serial.println(F("getSWVersion           9"));
        Serial.println(F("getEqualizerStatus     ."));
        Serial.println(F("getSongTime            ,"));
        Serial.println(F("getSongName            /"));
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
          if (BT.changeName(str)) Serial.println(F("BT name changed, reboot required to take efect."));
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
      case '5':
        {
          delay(100);
          String str;
          c = 0;
          while (Serial.available() > 0) {
            c = Serial.read();
            str += c;
          }
          BT.changePin(str);
        }
        break;
      case '6':
        {
          BT.getAutoPlay();
        }
        break;
      case '7':
        {
          BT.autoPlayOn();
        }
        break;
      case '8':
        {
          BT.autoPlayOff();
        }
        break;
      case '9':
        BT.getSWVersion();
        break;
      case '.':
        BT.getEqualizerStatus();
        break;
      case ',':
        BT.getSongTime();
        break;
      case '/':
        BT.getSongName();
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

  if (ModeOfPlay != BT.ModeOfPlay) {
    printModeOfPlay();
    ModeOfPlay = BT.ModeOfPlay;
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
  delay(100);//just in case
}

void printAllInfo() {
  Serial.print(F("BT name: ")); Serial.println(BT.BT_NAME);
  Serial.print(F("Pin: ")); Serial.println(BT.BT_PIN);
  Serial.print(F("BT address: ")); Serial.println(BT.BT_ADDR);
  printInputSelected();
  printMusicState();
  printBTstate();
  printCallState();
  printCurrentFreqency();
  printCurrentPreset();
  printCurrentVolume();
  printCurrentModeOfPlay();
}

void printCallState() {
  Serial.print(F("Current mode: "));
  Serial.println(BT.decodeCallState(BT.CallState));
  if (BT.CallState != BT.Idle)
    Serial.println(BT.CallerID);
}

void printCurrentModeOfPlay() {
  Serial.print(F("Current mode: "));
  Serial.println(BT.decodePlayMode(BT.ModeOfPlay));
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

void printModeOfPlay() {
  Serial.print(F("INPUT: "));
  Serial.println(BT.decodePlayMode(BT.ModeOfPlay));
}

void printBTstate() {
  Serial.print(F("INPUT: "));
  Serial.println(BT.decodeBluetoothState(BT.BTState));
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
        Serial.print(F("Playing song ")); Serial.print(BT.CurrentlyPlayingSong); Serial.print(F(" of ")); Serial.print(BT.NumberOfSongs); Serial.println(".");
      }
      break;
    case (BT.Stopped):
      Serial.println(F("Music stopped"));
      break;
  }
}

void printInputSelected() {
  Serial.print(F("INPUT: "));
  Serial.println(BT.decodeInput(BT.InputSelected));
}


void printPowerState() {
  Serial.print(F("Module: "));
  Serial.println(BT.decodePowerState(BT.PowerState));
}
