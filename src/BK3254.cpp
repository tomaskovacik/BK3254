/*
        GNU GPL v3
        (C) Tomas Kovacik [nail at nodomain dot sk]
        https://github.com/tomaskovacik/

        BK3254 module library
*/

#include "BK3254.h"
#include <Arduino.h>

#if defined(USE_SW_SERIAL)
#include <SoftwareSerial.h>
#endif



#if defined(USE_SW_SERIAL)
#if ARDUINO >= 100
BK3254::BK3254(SoftwareSerial *ser, uint8_t resetPin)
#else
BK3254::BK3254(NewSoftSerial *ser, uint8_t resetPin)
#endif
#else
BK3254::BK3254(HardwareSerial *ser, uint8_t resetPin)
#endif
{
  btSerial = ser;
  _reset = resetPin;
}

/*
   Destructor
*/
BK3254::~BK3254() {
  btSerial->end();
}

void BK3254::begin(uint32_t baudrate) {
  btSerial->begin(baudrate);
  pinMode(_reset, OUTPUT);
  BK3254::resetHigh();
}

void BK3254::resetLow() {
  digitalWrite(_reset, LOW);
}

void BK3254::resetHigh() {
  digitalWrite(_reset, HIGH);
}

/*
   debug output
*/
#if defined DEBUG
void BK3254::DBG(String text) {
  Serial.print(text);;
}
#endif


void BK3254::resetModule() {
#if defined DEBUG
  DBG(F("reseting module"));
#endif
  resetLow();
  delay(100);
  resetHigh();
}

uint8_t BK3254::getNextEventFromBT() {
  char c;
  String receivedString;
  delay(200);//delay needed to fillup buffers otherwise this will return false
  while (btSerial -> available() > 0 && c != '\n') { //read serial buffer until \n
    c = (btSerial -> read());
    if (c == 0xA) {
      if (receivedString == "") { //nothing before enter was received
  #if defined DEBUG
        DBG(F("received only empty string\n running again myself...\n"));
  #endif
        return BK3254::getNextEventFromBT();
      }
      return decodeReceivedString(receivedString);
    }
    //append received buffer with received character
    if (c != 0xD) receivedString += c;  // skip \r
  }
  return 0;
}

uint8_t BK3254::sendData(String cmd) {
  String Command = "AT+" + cmd + "\r\n";
#if defined DEBUG
  DBG(F("sending "));DBG(Command);
#endif
  btSerial -> print(Command);
  return BK3254::getNextEventFromBT();
}

uint8_t BK3254::sendCOMData(String cmd) { 
  BK3254::getNextEventFromBT();
  String Command = "COM+" + cmd + "\r\n";
#if defined DEBUG
  DBG(F("sending "));DBG(Command);
#endif
  btSerial -> print(Command);
  return BK3254::getNextEventFromBT();
}

uint8_t BK3254::sendBTData(String cmd) {

  BK3254::getNextEventFromBT();
  String Command = "BT+" + cmd + "\r\n";
#if defined DEBUG
  DBG(F("sending "));DBG(Command);
#endif
  btSerial -> print(Command);
  return BK3254::getNextEventFromBT();
}

uint8_t BK3254::sendFMData(String cmd) {
  BK3254::getNextEventFromBT();
  String Command = "FM+" + cmd + "\r\n";
#if defined DEBUG
  DBG(F("sending "));DBG(Command);
#endif
  delay(100);
  btSerial -> print(Command);
  return BK3254::getNextEventFromBT();
}

/*
  AX_PA\n   AUX Playing status
  AX_PU\n   AUX In a suspended state
  BT_AC\n   Bluetooth Even being back
  BT_CN\n   Bluetooth connected
  BT_EC\n   Bluetooth He is busy
  BT_IC\n   Bluetooth A call
  BT_WP\n   Bluetooth In pairing state
  BT_WC\n   Bluetooth connection is in wait state
  BT_OC\n   Bluetooth Telephone shot
  BT_PA\n   Bluetooth Now Playing
  EEROR\n   error
  FM_FQ = 1081\n  Tunner frequency
  FM_PA\n   FM You are listening state
  FM_PU\r\n   FM In a suspended state
  FM_SC\n   FM The state of being seized Taiwan
  IA\r\n  disconnect
  II\r\n  connection succeeded
  IRx\n   Received key value by IR
  music_mun = x\n   Song number
  OK\n
  ON\r\n  Bluetooth turned on
  PLAY_ALL\n  Repeat All Tracks (TF/SDcard Mode)
  PLAY_ONE\n   Repeat One Track (TF/SDcard Mode)
  SD_PA\n   SD Card playing status
  SD_PU\n   SD Card is paused
  SY_PO\n   Bluetooth turned on
  SY_PF\n   Bluetooth off
  UD_PA\n   U plate Playing status
  UD_PU\n   U plate In a suspended state
  VOLx\n  The current volume x level

  AD: 191919191919\r\n
  PN: 0000\r\n
  NA: BK3254\r\n

  connection succeeded: C1\r\n
  no connection: C0\r\n

  Play: MB\r\n /
  Idle: MA\r\n
  disconnect: M0\r\n

  disconnect: M0\r\n
  connection: M1\r\n
  Caller: M2\r\n
  Outgoing: M3\r\n
  calling: M4\r\n
  IR-"+123456789"
*/
uint8_t BK3254::decodeReceivedString(String receivedString) {

#if defined DEBUG
  DBG(receivedString + "\n");
#endif

  if (memcmp(&receivedString[0], "AX_PA", 5) == 0) {
#if defined DEBUG
    DBG(F("Playing status\n"));
#endif
    InputSelected = AUX;
    MusicState = Playing;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "AX_PU", 5) == 0) {
#if defined DEBUG
    DBG(F("AUX In a suspended state\n"));
#endif
    InputSelected = AUX;
    MusicState = Idle;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "BT_AC", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth Even being back\n"));
#endif
    InputSelected = BT;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "BT_CN", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth connected\n"));
#endif
    InputSelected = BT;
    BTState = Connected;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "BT_EC", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth He is busy\n"));
#endif
    InputSelected = BT;
    CallState = Busy;//is this ok?
    PowerState = On;
  } else if (memcmp(&receivedString[0], "BT_IC", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth A call\n"));
#endif
    InputSelected = BT;
    CallState = IncomingCall;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "BT_WP", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth In pairing state\n"));
#endif
    InputSelected = BT;
    BTState = Pairing;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "BT_WC", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth connection is in wait state\n"));
#endif
    InputSelected = BT;
    BTState = Connecting;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "BT_OC", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth Telephone shot\n"));
#endif
    InputSelected = BT;
    CallState = OutgoingCall;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "BT_PA", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth Now Playing\n"));
#endif
    InputSelected = BT;
    CallState = Idle;
    MusicState = Playing;
    BTState = Connected;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "ERR", 3) == 0) {
#if defined DEBUG
    DBG(F("Error"));
#endif
    PowerState = On;
    receivedString="";
#if defined DEBUG
   DBG(F("Return false\n"));
#endif
    return 0;
  } else if (memcmp(&receivedString[0], "FM_FQ=", 6) == 0) {
    CurrentFrequency = receivedString.substring(6).toInt();
#if defined DEBUG
    DBG(F("Tunner frequency: "));DBG((String)CurrentFrequency + "MHz\n");
#endif
    InputSelected = FM;
    BTState = Disconnected;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "FM_PA", 5) == 0) {
#if defined DEBUG
    DBG(F("You are listening state\n"));
#endif
    InputSelected = FM;
    MusicState = Playing;
    BTState = Disconnected;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "FM_PU", 5) == 0) {
#if defined DEBUG
    DBG(F("FM In a suspended state\n"));
#endif
    InputSelected = FM;
    MusicState = Idle;
    BTState = Disconnected;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "FM_SC", 5) == 0) {
#if defined DEBUG
    DBG(F("FM The state of being seized Taiwan\n"));
#endif
    InputSelected = FM;
    BTState = Disconnected;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "IA", 2) == 0) {
#if defined DEBUG
    DBG(F("Disconnect\n"));
#endif
    InputSelected = BT;
    BTState = Disconnected;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "II", 2) == 0) {
#if defined DEBUG
    DBG(F("Connection succeeded\n"));
#endif
    InputSelected = BT;
    BTState = Connected;
    PowerState = On;
  } else if (memcmp(&receivedString[0], "IR-", 3) == 0) {
#if defined DEBUG
    DBG(F("Incoming call\n"));
#endif
    InputSelected = BT;
    BTState = Connected;
    CallerID = BK3254::returnCallerID(receivedString);
    PowerState = On;
  } else if (memcmp(&receivedString[0], "IR", 2) == 0) {
#if defined DEBUG
    DBG(F("Infrared command received\n"));
#endif
    PowerState = On;
  } else if (memcmp(&receivedString[0], "PR-", 3) == 0) {
#if defined DEBUG
    DBG(F("Outgoing call\n"));
#endif
    InputSelected = BT;
    BTState = Connected;
    CallerID = BK3254::returnCallerID(receivedString);
    PowerState = On;
  } else if (memcmp(&receivedString[0], "MMMP", 4) == 0) {
    NumberOfSongs = receivedString.substring(4).toInt();
#if defined DEBUG
    DBG(F("Number of songs: "));DBG((String)NumberOfSongs + "\n");
#endif
  } else if (memcmp(&receivedString[0], "music_mun=", 10) == 0) {
    CurrentlyPlayingSong = receivedString.substring(10).toInt();
#if defined DEBUG
    DBG(F("Song number currently playing: "));DBG(String(CurrentlyPlayingSong) + "\n");
#endif
  } else if (memcmp(&receivedString[0], "OK", 2) == 0) {
#if defined DEBUG
    DBG(F("Success\n"));
#endif
  } else if (memcmp(&receivedString[0], "ON", 2) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth turned on\n"));
#endif
    PowerState = On;
  } else if (memcmp(&receivedString[0], "PLAY_ALL", 8) == 0 || memcmp(&receivedString[0], "PLAY_M0", 7) == 0) {
#if defined DEBUG
    DBG(F("Repeat All Tracks (TF/SDcard Mode)\n"));
#endif
    ModeOfPlay = RepeatAll;
  } else if (memcmp(&receivedString[0], "PLAY_ONE", 8) == 0 || memcmp(&receivedString[0], "PLAY_M1", 7) == 0) {
#if defined DEBUG
    DBG(F("Repeat One Track (TF/SDcard Mode)\n"));
#endif
    ModeOfPlay = RepeatOne;
  } else if (memcmp(&receivedString[0], "PLAY_M2", 7) == 0) {
#if defined DEBUG
    DBG(F("Repeat None (TF/SDcard Mode)\n"));
#endif
    ModeOfPlay = RepeatNone;
  } else if (memcmp(&receivedString[0], "SD_PA", 5) == 0) {
#if defined DEBUG
    DBG(F("SD Card playing status\n"));
#endif
    InputSelected = SD;
    MusicState = Playing;
  } else if (memcmp(&receivedString[0], "SD_PU", 5) == 0) {
#if defined DEBUG
    DBG(F("SD Card is paused\n"));
#endif
    InputSelected = SD;
    MusicState = Idle;
  } else if (memcmp(&receivedString[0], "SY_PO", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth turned on\n"));
#endif
    PowerState = On;
    BTState = Disconnected; //init all values
    CallState = Idle;
    MusicState = Idle;
    CallerID = "";
    BT_ADDR = "";
    BT_NAME = "";
    BT_PIN = "";
    CurrentFrequency = 0;
    CurrentPreset = 0;
  } else if (memcmp(&receivedString[0], "SY_PF", 5) == 0) {
#if defined DEBUG
    DBG(F("Bluetooth off\n"));
#endif
    PowerState = Off; //reset all values:
    BTState = Disconnected;
    CallState = Idle;
    MusicState = Idle;
    CallerID = "";
    BT_ADDR = "";
    BT_NAME = "";
    BT_PIN = "";
    CurrentFrequency = 0;
    CurrentPreset = 0;
  } else if (memcmp(&receivedString[0], "UD_PA", 5) == 0) {
#if defined DEBUG
    DBG(F("USB Playing status\n"));
#endif
    InputSelected = USB;
    BTState = Disconnected;
    MusicState = Playing;
  } else if (memcmp(&receivedString[0], "UD_PU", 5) == 0) {
#if defined DEBUG
    DBG(F("USB In a suspended state\n"));
#endif
    InputSelected = USB;
    BTState = Disconnected;
    MusicState = Idle;
  } else if (memcmp(&receivedString[0], "VOL", 3) == 0) {
    currentVolume = receivedString.substring(3).toInt();
#if defined DEBUG
    DBG(F("The current volume level: "));DBG((String)currentVolume + "\n");
#endif
  } else if (memcmp(&receivedString[0], "AD:", 3) == 0) {
    BT_ADDR = receivedString.substring(5);
#if defined DEBUG
    DBG(F("BT ADDRESS: "));DBG(BT_ADDR + "\n");
#endif
  } else if (memcmp(&receivedString[0], " PN: ", 5) == 0) {
    BT_PIN = receivedString.substring(5);
#if defined DEBUG
    DBG(F("Pin received:"));DBG(BT_PIN + "\n");
#endif
  } else if (memcmp(&receivedString[0], "NA: ", 4) == 0) {
    BT_NAME = BK3254::returnBtModuleName(receivedString);
#if defined DEBUG
    DBG(F("BT name received: "));DBG(BT_NAME + "\n");
#endif
  } else if (memcmp(&receivedString[0], "C1", 2) == 0) {
#if defined DEBUG
    DBG(F("Connection succeeded\n"));
#endif
    BTState = Connected;
  } else if (memcmp(&receivedString[0], "C0", 2) == 0) {
#if defined DEBUG
    DBG(F("No connection\n"));
#endif
    BTState = Disconnected;
  } else if (memcmp(&receivedString[0], "MB", 2) == 0) {
#if defined DEBUG
    DBG(F("Play\n"));
#endif
    MusicState = Playing;
  } else if (memcmp(&receivedString[0], "MA", 2) == 0) {
#if defined DEBUG
    DBG(F("Idle\n"));
#endif
    MusicState = Idle;
  } else if (memcmp(&receivedString[0], "M0", 2) == 0) {
#if defined DEBUG
    DBG(F("Disconnect\n"));
#endif
    BTState = Disconnected;
  } else if (memcmp(&receivedString[0], "M1", 2) == 0) {
#if defined DEBUG
    DBG(F("Connection\n"));
#endif
    BTState = Connected;
  } else if (memcmp(&receivedString[0], "M2", 2) == 0) {
#if defined DEBUG
    DBG(F("Caller"));
#endif
    BTState = CallInProgress;
  } else if (memcmp(&receivedString[0], "M3", 2) == 0) {
#if defined DEBUG
    DBG(F("Outgoing\n"));
#endif
    BTState = OutgoingCall;
  } else if (memcmp(&receivedString[0], "M4", 2) == 0) {
#if defined DEBUG
    DBG(F("Calling\n"));
#endif
    BTState = IncomingCall;
  } else if (memcmp(&receivedString[0], "MFM", 3) == 0) {
#if defined DEBUG
   DBG(F("Current preset: "));
#endif
    CurrentPreset = receivedString.substring(3).toInt();
#if defined DEBUG
   DBG(CurrentPreset);DBG(F("\n"));
#endif

  } else if (memcmp(&receivedString[0], "MUSICPLYFINISH", 14) == 0 ) {
    MusicState = Idle;
#if defined DEBUG
   DBG(F("MUSICPLYFINISH\n"));
#endif
  }
  receivedString="";
#if defined DEBUG
   DBG(F("Return true\n"));
#endif
  return 1;
}

String BK3254::returnCallerID(String receivedString) {
#if defined DEBUG
  DBG(F("Calling: "));DBG(receivedString.substring(4, (receivedString.length() - 2)) + "\n");
#endif
  return receivedString.substring(4, (receivedString.length() - 2)); //start at 4 cose: IR-"+123456789" or PR-"+123456789" and one before end to remove " and \0
}

String BK3254::returnBtModuleName(String receivedString) {
#if defined DEBUG
  DBG(F("Bluetooth module name: "));DBG(receivedString.substring(4) + "\n");
#endif
  return receivedString.substring(4);
}

uint16_t BK3254::returnFreq(String receivedString) {
  //FM_FQ=893
#if defined DEBUG
  DBG(receivedString);
#endif
  return (uint16_t)(receivedString.toInt());
}

/*
  #define BK3254_PAIRING "SNAME" //change name
  #define BK3254_VOICES_ON "TONEON"
  #define BK3254_VOICES_OFF "TONEOFF"
  #define BK3254_GET_VOICES_STATE "MTONE"
  #define BK3254_GOBACKON "GOBACKON"
  #define BK3254_GOBACKOFF "GOBACKOFF"
  #define BK3254_GET_GOBACK_STATE "MGOBACK"
  #define BK3254_CALLON "CALLON"
  #define BK3254_CALLOFF "CALLOFF"
  #define BK3254_GET_CALL_STATE "MCALL"
  #define BK3254_REBOOT "REBOOT"

  these works onl on boards with V1.2 firmware
  SPIN sould works only on V1.3 based on pdf name ... on 1.2 it disconect BT
*/

uint8_t BK3254::voicesOn() {
  return BK3254::sendCOMData(BK3254_VOICES_ON);
}

uint8_t BK3254::voicesOff() {
  return BK3254::sendCOMData(BK3254_VOICES_OFF);
}

uint8_t BK3254::getVoicesState() {
  return BK3254::sendCOMData(BK3254_GET_VOICES_STATE);
}

uint8_t BK3254::goBackOn() {
  return BK3254::sendCOMData(BK3254_GOBACKON);
}

uint8_t BK3254::goBackOff() {
  return BK3254::sendCOMData(BK3254_GOBACKOFF);
}

uint8_t BK3254::getGoBack() {
  return BK3254::sendCOMData(BK3254_GET_GOBACK_STATE);
}

uint8_t BK3254::callOn() {
  return BK3254::sendCOMData(BK3254_CALLON);
}

uint8_t BK3254::callOff() {
  return BK3254::sendCOMData(BK3254_CALLOFF);
}

uint8_t BK3254::getCall() {
  return BK3254::sendCOMData(BK3254_GET_CALL_STATE);
}

uint8_t BK3254::autoPlayOn() {
  return BK3254::sendCOMData(BK3254_AUTOPLAYON);
}

uint8_t BK3254::autoPlayOff() {
  return BK3254::sendCOMData(BK3254_AUTOPLAYOFF);
}

uint8_t BK3254::getAutoPlay() {
  return BK3254::sendCOMData(BK3254_GET_AUTOPLAY_STATE);
}

uint8_t BK3254::reboot() {
  return BK3254::sendCOMData(BK3254_REBOOT);
}

/*

*/
uint8_t BK3254::changePin(String newPin) {//this command did not work on my module ...
  if (newPin.length() - 2 > 16) { //count for termination char
#if defined DEBUG
    DBG(F("Pin to long, max 16chars"));
#endif
    return false;
  } else {
#if defined DEBUG
    DBG(F("Writing pin\n"));
#endif
    return BK3254::sendCOMData(BK3254_CHANGE_PIN + newPin);
  }
}

/*

*/
uint8_t BK3254::changeName(String newName) {//this command did not work on my module ...
  if (newName.length() - 2 > 16) { //count for termination char
#if defined DEBUG
    DBG(F("name to long, max 16chars"));
#endif
    return false;
  } else {
#if defined DEBUG
    DBG(F("Writing name\n"));
#endif
    return BK3254::sendCOMData(BK3254_CHANGE_NAME + newName);
  }
}

uint8_t BK3254::pairingInit() { //BK3254_PAIRING "BT+PR" //Pairing
  return BK3254::sendBTData(BK3254_PAIRING);
}

uint8_t BK3254::connectLastDevice() {//   BK3254_PAIRING_DEVICE "BT+AC" //The last paired device connected (connect to last device?)
  return BK3254::sendBTData(BK3254_PAIRING_DEVICE);
}

uint8_t BK3254::disconnect() {// BK3254_DISCONNECT "BT+DC" //Disconect
  return BK3254::sendBTData(BK3254_DISCONNECT);
}


uint8_t BK3254::callAnsware() { //BK3254_CALL_ANSWARE "BT+CA" //Answare the call
  return BK3254::sendBTData(BK3254_CALL_ANSWARE);
}

uint8_t BK3254::callReject() { //BK3254_CALL_REJECT "BT+CJ" //To reject a call
  return BK3254::sendBTData(BK3254_CALL_REJECT);
}

uint8_t BK3254::callHangUp() { //BK3254_CALL_HANGUP "BT+CE" //Hang up the phone
  return BK3254::sendBTData(BK3254_CALL_HANGUP);
}

uint8_t BK3254::callRedial() { //BK3254_CALL_REDIAL "BT+CR" //Last number redial
  return BK3254::sendBTData(BK3254_CALL_REDIAL);
}

uint8_t BK3254::musicTogglePlayPause() { //BK3254_MUSIC_TOGGLE_PLAY_PAUSE "COM+PR" //Music Play / Pause
  return BK3254::sendCOMData(BK3254_MUSIC_TOGGLE_PLAY_PAUSE);
}

uint8_t BK3254::musicNextTrack() { //BK3254_MUSIC_NEXT_TRACK "COM+PN" //next track/ FM next station
  return BK3254::sendCOMData(BK3254_MUSIC_NEXT_TRACK);
}

uint8_t BK3254::musicPreviousTrack() { //BK3254_MUSIC_PREVIOUS_TRACK "COM+PV" //previous piece/ FM On one
  return BK3254::sendCOMData(BK3254_MUSIC_PREVIOUS_TRACK);
}

uint8_t BK3254::volumeUp() { //BK3254_VOLUME_UP "COM+VP" //Volume Up
  return BK3254::sendCOMData(BK3254_VOLUME_UP);
}

uint8_t BK3254::volumeDown() { //BK3254_VOLUME_DOWN "COM+VD" //Volume down
  return BK3254::sendCOMData(BK3254_VOLUME_DOWN);
}

uint8_t BK3254::volumeSet(String volume) { //BK3254_VOLUME_SET "COM+VOL" //VOL+x: 0x00 - 0xAF  Set the volume  correct: VOLx\n / error: ERR\n
  return BK3254::sendCOMData(BK3254_VOLUME_SET + volume);
}

uint8_t BK3254::volumeGet() { //BK3254_VOLUME_GET_CURRENT "COM+MVOL" //Query current volume  correct: VOLx\n (x:0-15) / error: ERR\n
  return BK3254::sendCOMData(BK3254_VOLUME_GET_CURRENT);
}

uint8_t BK3254::shutdown() { //BK3254_SHUTDOWN "COM+PWD" //Shutdown
  return BK3254::sendCOMData(BK3254_SHUTDOWN);
}

uint8_t BK3254::standby() { //BK3254_STANDBY "COM+PWDS" //Soft-Off
  return BK3254::sendCOMData(BK3254_STANDBY);
}

uint8_t BK3254::powerup() { //BK3254_POWERUP "COM+PWOS" //Soft Power   ???
  return BK3254::sendCOMData(BK3254_POWERUP);
}

uint8_t BK3254::switchInput() { //BK3254_INPUT_SWITCH "COM+MC" //Switching to the next operating mode
  return BK3254::sendCOMData(BK3254_INPUT_SWITCH);
}

uint8_t BK3254::switchInputToBluetooth() { //BK3254_INPUT_BLUETOOTH "COM+MBT" //Bluetooth mode
  return BK3254::sendCOMData(BK3254_INPUT_BLUETOOTH);
}

uint8_t BK3254::switchInputToCard() { //BK3254_INPUT_TF "COM+MSD" //TF/SDcard Mode (if available)
  return BK3254::sendCOMData(BK3254_INPUT_TF);
}

uint8_t BK3254::switchInputToAux() { //BK3254_INPUT_AUX "COM+MAX" //AUX Mode (if available)
  return BK3254::sendCOMData(BK3254_INPUT_AUX);
}

uint8_t BK3254::switchInputToFm() { //BK3254_INPUT_FM "COM+MFM" //FM Mode (if available)
  return BK3254::sendCOMData(BK3254_INPUT_FM);
}

uint8_t BK3254::switchInputToUsb() { //BK3254_INPUT_USB "COM+MUD" //USB Disk mode (if available)
  return BK3254::sendCOMData(BK3254_INPUT_USB);
}

uint8_t BK3254::getCurrentInput() { //BK3254_INPUT_GET_CURRENT "COM+IQ" //Query the current mode
  return BK3254::sendCOMData(BK3254_INPUT_GET_CURRENT);
}

uint8_t BK3254::musicModeRepeatAll() { //BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ALL "COM+MPM0" //Repeat All Tracks (TF/USB disk mode)  correct: PLAY_ALL\n / error: ERR\n;  from firmware 1.4: correct: PLAY_M0 \ n
  return BK3254::sendCOMData(BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ALL);
}

uint8_t BK3254::musicModeRepeatOne() { //BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ONE "COM+MPM1" //Single loop (TF/USB disk mode)  correct: PLAY_ONE\n / error: ERR\n ;from firmware 1.4: correct: PLAY_M1 \ n
  return BK3254::sendCOMData(BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ONE);
}

uint8_t BK3254::musicModeRepeatNone() { //BK3254_MUSIC_PLAYBACK_MODE_REPEAT_NONE  //No single loop (TF/USB disk mode)  correct: PLAY_M2\n / error: ERR\n
  return BK3254::sendCOMData(BK3254_MUSIC_PLAYBACK_MODE_REPEAT_NONE);
}

uint8_t BK3254::musicGetCurrentMode() { //BK3254_MUSIC_PLAYBACK_MODE_GET_CURRENT "COM+MPMC" //The current inquiry MP3 Play Mode (TF/USB disk mode)  correct: PLAY_ALL\n / PLAY_ONE\n
  return BK3254::sendCOMData(BK3254_MUSIC_PLAYBACK_MODE_GET_CURRENT);
}

uint8_t BK3254::musicPlaySong(uint16_t number) { //BK3254_MUSIC_PLAY_SONG_NUMBER "COM+SMP" //SMP+XXXX, Play selections (TF/USB disk mode)  XXXX: 0001-9999, 0001 Represents the 1 first
  return BK3254::sendCOMData(BK3254_MUSIC_PLAY_SONG_NUMBER + (String)number);
}

uint8_t BK3254::cardGetCurrentPlayingSongNumber() { //BK3254_TF_GET_SONG_NUMBER "COM+MRMP3" //Query currently playing MP3 Song number   correct: music_mun = x\n , x: 1-9999 / error: ERR\n ???
  return BK3254::sendCOMData(BK3254_TF_GET_SONG_NUMBER);
}

uint8_t BK3254::cardUsbGetSongsCount() { //BK3254_TF_USB_GET_NUMBER_OF_SONGS "COM+MMMP3" //Query current mode MP3 The number of songs (TF/USB disk mode)   correct: MMMPx\n,x: 1-1999 / error: ERR\n
  return BK3254::sendCOMData(BK3254_TF_USB_GET_NUMBER_OF_SONGS);
}

uint8_t BK3254::usbGetCurrentPlayingSongNumber() { //BK3254_USB_GET_SONG_NUMBER "COM+MRUSB" //Query currently playing USB Disc song number  correct: music_mun = x\n,x: 1-1999 / error: ERR\n
  return BK3254::sendCOMData(BK3254_USB_GET_SONG_NUMBER);
}

uint8_t BK3254::fmStartSearch() { //BK3254_FM_START_SEARCH "FM+SC" //FM start station search
  return BK3254::sendFMData(BK3254_FM_START_SEARCH);
}

uint8_t BK3254::fmStopSearch() { //BK3254_FM_STOP_SEARCH "FM+ST" //FM Stop station search
  return BK3254::sendFMData(BK3254_FM_STOP_SEARCH);
}

uint8_t BK3254::fmGetFreq() { //BK3254_FM_GET_FREQ "FM+GF" //Get the current radio frequency   FM_FQ = 875 ~ 1081
  return BK3254::sendFMData(BK3254_FM_GET_FREQ);
}

uint8_t BK3254::fmTunePreset(String preset) { //BK3254_FM_TUNE_PRESET "COM+SFM" //SFM+XX,Select FM preset 01-99  correct: FM_FQ = 998\n / error: ERR\n
  return BK3254::sendCOMData(BK3254_FM_TUNE_PRESET + preset);
}

uint8_t BK3254::fmTuneFreq(String freq) { //BK3254_FM_TUNE_FREQ "COM+SETFM" //SETFM+XXX, XXX : 875 to 1081   set up FM frequency to XXX  correct: OK\n / error: ERR\n
  return BK3254::sendCOMData(BK3254_FM_TUNE_FREQ + freq);
}

uint8_t BK3254::fmGetFreq2() { //BK3254_FM_GET_FREQ2 "COM+MRFM" //Query current FM frequency (FM Mode)  correct: FM_FQ = xxx\n. xxx: 875-1081(87.5-108.1Mhz) / error: ERR\n ?? wht is diference to FM+GF ?
  return BK3254::sendCOMData(BK3254_FM_GET_FREQ2);
}

uint8_t BK3254::fmGetPreset() { //BK3254_FM_GET_PRESET "COM+MMFM" //Query currently selected preset (FM Mode)   correct: MFMxx \ n,xx: 01-99 / error: ERR\n
  return BK3254::sendCOMData(BK3254_FM_GET_PRESET);
}

uint8_t BK3254::fmGetFreqOfPreset(String preset) { //BK3254_FM_GET_FREQ_OF_PRESET "COM+MFFM" //MFFM+XX, Inquire FM of xx No. A frequency corresponding to (FM Mode)   correct: FM_FQ = xxx\n, error: ERR\n
  return BK3254::sendCOMData(BK3254_FM_GET_FREQ_OF_PRESET + preset);
}
//Query / feedback commands

uint8_t BK3254::getAddress() { //BK3254_GET_ADDRESS "AT+MR" //Queries Bluetooth address   AD: 191919191919\r\n
  return BK3254::sendData(BK3254_GET_ADDRESS);
}

uint8_t BK3254::getPinCode() { //BK3254_GET_PIN_CODE "AT+MP" //PIN Code query  PN: 0000\r\n
  return BK3254::sendData(BK3254_GET_PIN_CODE);
}

uint8_t BK3254::getName() { //BK3254_GET_NAME "AT+MN" //Bluetooth name query  NA: BK3254\r\n
  return BK3254::sendData(BK3254_GET_NAME);
}

uint8_t BK3254::getConnectionStatus() { //BK3254_GET_CONNECTION_STATUS "AT+MO" //Bluetooth connection status inquiry   connection succeeded: C1\r\n / no connection: C0\r\n
  return BK3254::sendData(BK3254_GET_CONNECTION_STATUS);
}

uint8_t BK3254::getMusicStatus() { //BK3254_MUSIC_GET_STATUS "AT+MV" //Bluetooth playback status inquiry   Play: MB\r\n / time out: MA\r\n / disconnect: M0\r\n
  return BK3254::sendData(BK3254_GET_MUSIC_STATUS);
}

uint8_t BK3254::getHFPStatus() { //BK3254_GET_HFP_STATUS "AT+MY" //Bluetooth inquiry HFP status  disconnect: M0\r\n / connection: M1\r\n / Caller: M2\r\n / Outgoing: M3\r\n / calling: M4\r\n
  return BK3254::sendData(BK3254_GET_HFP_STATUS);
}

String BK3254::decodeState(uint16_t state){
    switch (state){
    case Playing:
        return F("Playing");
        break;
    case Idle:
        return F("Idle");
        break;
   case IncomingCall:
        return F("IncomingCall");
        break;
   case OutgoingCall:
        return F("OutgoingCall");
        break;
   case CallInProgress:
        return F("CallInProgress");
        break;
   case Connected:
        return F("Connected");
        break;
   case Disconnected:
        return F("Disconnected");
        break;
   case On:
        return F("On");
        break;
   case Off:
        return F("Off");
        break;
   case Pairing:
        return F("Pairing");
        break;
   case ShutdownInProgress:
        return F("ShutdownInProgress");
        break;
   case BT:
        return F("BT");
        break;
   case AUX:
        return F("AUX");
        break;
   case USB:
        return F("USB");
        break;
   case SD:
        return F("SD");
        break;
   case Connecting:
        return F("Connecting");
        break;
   case Busy:
        return F("Busy");
        break;
   case RepeatAll:
        return F("RepeatAll");
    break;
    case RepeatOne:
        return F("RepeatOne");
    break;
    case RepeatNone:
        return F("RepeatNone");
    break;
    case FM:
        return F("FM");
    break;
    }

}
