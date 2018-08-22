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

void BK3254::resetModule() {
  DBG("reseting module");
  resetLow();
  delay(100);
  resetHigh();
}

/*
   debug output
*/
void BK3254::DBG(String text) {
  if (DEBUG) /*return "DBG: ");*/ Serial.print(text);;
}

uint8_t BK3254::getNextEventFromBT() {
  char c;
  String receivedString = "";
  while (btSerial -> available() > 0) {
    c = (btSerial -> read());
    //Serial.write(c);Serial.print(" ");Serial.println(c,HEX);
    if (c == 0xD) {
      if (receivedString == "") { //nothing before enter was received
        //DBG("received only empty string\n running again myself...\n");
        BK3254::getNextEventFromBT();
      }
      receivedString = receivedString + c;
      decodeReceivedString(receivedString);
      break;
    }
    //append received buffer with received character
    receivedString = receivedString + c;  // cose += c did not work ...
  }
}

uint8_t BK3254::sendData(String cmd) {
  String Command = "AT+" + cmd + "\r\n";
  DBG("sending " + Command);
  delay(100);
  btSerial -> print(Command);
}

uint8_t BK3254::sendCOMData(String cmd) {
  String Command = "COM+" + cmd + "\r\n";
  DBG("sending " + Command);
  delay(100);
  btSerial -> print(Command);
}

uint8_t BK3254::sendBTData(String cmd) {
  String Command = "BT+" + cmd + "\r\n";
  DBG("sending " + Command);
  delay(100);
  btSerial -> print(Command);
}

uint8_t BK3254::sendFMData(String cmd) {
  String Command = "FM+" + cmd + "\r\n";
  DBG("sending " + Command);
  delay(100);
  btSerial -> print(Command);
}

uint8_t BK3254::decodeReceivedString(String receivedString) {
  DBG(receivedString);
  DBG("\n");
  //  switch (receivedString[0]) {
  //
  //  }
  return 1;
}

uint8_t BK3254::pairingInit() { //BK3254_PAIRING "BT+PR" //Pairing
  BK3254::sendBTData(BK3254_PAIRING);
  BTState = Pairing;
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::connectLastDevice() {//   BK3254_PAIRING_DEVICE "BT+AC" //The last paired device connected (connect to last device?)
  BK3254::sendBTData(BK3254_PAIRING_DEVICE);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::disconnect() {// BK3254_DISCONNECT "BT+DC" //Disconect
  BK3254::sendBTData(BK3254_DISCONNECT);
  BK3254::getNextEventFromBT();
}


uint8_t BK3254::callAnsware() { //BK3254_CALL_ANSWARE "BT+CA" //Answare the call 
  BK3254::sendBTData(BK3254_CALL_ANSWARE);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::callReject() { //BK3254_CALL_REJECT "BT+CJ" //To reject a call  
  BK3254::sendBTData(BK3254_CALL_REJECT);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::callHangUp() { //BK3254_CALL_HANGUP "BT+CE" //Hang up the phone   
  BK3254::sendBTData(BK3254_CALL_HANGUP);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::callRedial() { //BK3254_CALL_REDIAL "BT+CR" //Last number redial  
  BK3254::sendBTData(BK3254_CALL_REDIAL);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::musicTogglePlayPause() { //BK3254_MUSIC_TOGGLE_PLAY_PAUSE "COM+PR" //Music Play / Pause 
  BK3254::sendCOMData(BK3254_MUSIC_TOGGLE_PLAY_PAUSE);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::musicNextTrack() { //BK3254_MUSIC_NEXT_TRACK "COM+PN" //next track/ FM next station  
  BK3254::sendCOMData(BK3254_MUSIC_NEXT_TRACK);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmNextTrack() { //BK3254_FM_NEXT_STATION "COM+PN" //next track/ FM next station   
  BK3254::sendCOMData(BK3254_FM_NEXT_STATION);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::musicPreviousTrack() { //BK3254_MUSIC_PREVIOUS_TRACK "COM+PV" //previous piece/ FM On one   
  BK3254::sendCOMData(BK3254_MUSIC_PREVIOUS_TRACK);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmPreviousTrack() { //BK3254_FM_PREVIOUS_STATION "COM+PV" //previous piece/ FM On one   
  BK3254::sendCOMData(BK3254_FM_PREVIOUS_STATION);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::volumeUp() { //BK3254_VOLUME_UP "COM+VP" //Volume Up   
  BK3254::sendCOMData(BK3254_VOLUME_UP);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::volumeDown() { //BK3254_VOLUME_DOWN "COM+VD" //Volume down   
  BK3254::sendCOMData(BK3254_VOLUME_DOWN);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::volumeSet(uint8_t volume) { //BK3254_VOLUME_SET "COM+VOL" //VOL+x: 0x00 - 0xAF  Set the volume  correct: VOLx\n / error: ERR\n
  BK3254::sendCOMData(BK3254_VOLUME_SET+(char)volume);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::volumeGet() { //BK3254_VOLUME_GET_CURRENT "COM+MVOL" //Query current volume  correct: VOLx\n (x:0-15) / error: ERR\n
  BK3254::sendCOMData(BK3254_VOLUME_GET_CURRENT);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::shutdown() { //BK3254_SHUTDOWN "COM+PWD" //Shutdown
  BK3254::sendCOMData(BK3254_SHUTDOWN);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::standby() { //BK3254_STANDBY "COM+PWDS" //Soft-Off  
  BK3254::sendCOMData(BK3254_STANDBY);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::powerup() { //BK3254_POWERUP "COM+PWOS" //Soft Power   ???
  BK3254::sendCOMData(BK3254_POWERUP);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::switchInput() { //BK3254_INPUT_SWITCH "COM+MC" //Switching to the next operating mode 
  BK3254::sendCOMData(BK3254_INPUT_SWITCH);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::switchInputToBluetooth() { //BK3254_INPUT_BLUETOOTH "COM+MBT" //Bluetooth mode 
  BK3254::sendCOMData(BK3254_INPUT_BLUETOOTH);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::switchInputToCard() { //BK3254_INPUT_TF "COM+MSD" //TF/SDcard Mode (if available)
  BK3254::sendCOMData(BK3254_INPUT_TF);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::switchInputToAux() { //BK3254_INPUT_AUX "COM+MAX" //AUX Mode (if available)
  BK3254::sendCOMData(BK3254_INPUT_AUX);
  BK3254::getNextEventFromBT();
}    

uint8_t BK3254::switchInputToFm() { //BK3254_INPUT_FM "COM+MFM" //FM Mode (if available)
  BK3254::sendCOMData(BK3254_INPUT_FM);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::switchInputToUsb() { //BK3254_INPUT_USB "COM+MUD" //USB Disk mode (if available)
  BK3254::sendCOMData(BK3254_INPUT_USB);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::getCurrentInput() { //BK3254_INPUT_GET_CURRENT "COM+IQ" //Query the current mode
  BK3254::sendCOMData(BK3254_INPUT_GET_CURRENT);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::musicModeRepeatAll() { //BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ALL "COM+MPM0" //Repeat All Tracks (TF/USB disk mode)  correct: PLAY_ALL\n / error: ERR\n
  BK3254::sendCOMData(BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ALL);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::musicModeRepeatOne() { //BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ONE "COM+MPM1" //Single loop (TF/USB disk mode)  correct: PLAY_ONE\n / error: ERR\n
  BK3254::sendCOMData(BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ONE);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::musicGetCurrentMode() { //BK3254_MUSIC_PLAYBACK_MODE_GET_CURRENT "COM+MPMC" //The current inquiry MP3 Play Mode (TF/USB disk mode)  correct: PLAY_ALL\n / PLAY_ONE\n
  BK3254::sendCOMData(BK3254_MUSIC_PLAYBACK_MODE_GET_CURRENT);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::musicPlaySong(uint16_t number) { //BK3254_MUSIC_PLAY_SONG_NUMBER "COM+SMP" //SMP+XXXX, Play selections (TF/USB disk mode)  XXXX: 0001-9999, 0001 Represents the 1 first
  BK3254::sendCOMData(BK3254_MUSIC_PLAY_SONG_NUMBER+(String)number);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::cardGetCurrentPlayingSongNumber() { //BK3254_TF_GET_SONG_NUMBER "COM+MRMP3" //Query currently playing MP3 Song number   correct: music_mun = x\n , x: 1-9999 / error: ERR\n ???
  BK3254::sendCOMData(BK3254_TF_GET_SONG_NUMBER);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::cardUsbGetSongsCount() { //BK3254_TF_USB_GET_NUMBER_OF_SONGS "COM+MMMP3" //Query current mode MP3 The number of songs (TF/USB disk mode)   correct: MMMPx\n,x: 1-1999 / error: ERR\n
  BK3254::sendCOMData(BK3254_TF_USB_GET_NUMBER_OF_SONGS);
  BK3254::getNextEventFromBT();
}
 
uint8_t BK3254::usbGetCurrentPlayingSongNumber() { //BK3254_USB_GET_SONG_NUMBER "COM+MRUSB" //Query currently playing USB Disc song number  correct: music_mun = x\n,x: 1-1999 / error: ERR\n
  BK3254::sendCOMData(BK3254_USB_GET_SONG_NUMBER);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmStartSearch() { //BK3254_FM_START_SEARCH "FM+SC" //FM start station search
  BK3254::sendFMData(BK3254_FM_START_SEARCH);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmStopSearch() { //BK3254_FM_STOP_SEARCH "FM+ST" //FM Stop station search
  BK3254::sendFMData(BK3254_FM_STOP_SEARCH);
  BK3254::getNextEventFromBT();
}
   
uint8_t BK3254::fmGetFreq() { //BK3254_FM_GET_FREQ "FM+GF" //Get the current radio frequency   FM_FQ = 875 ~ 1081
  BK3254::sendFMData(BK3254_FM_GET_FREQ);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmTunePreset(uint8_t preset) { //BK3254_FM_TUNE_PRESET "COM+SFM" //SFM+XX,Select FM preset 01-99  correct: FM_FQ = 998\n / error: ERR\n
  BK3254::sendCOMData(BK3254_FM_TUNE_PRESET+(char)preset);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmTuneFreq(uint16_t freq) { //BK3254_FM_TUNE_FREQ "COM+SETFM" //SETFM+XXX, XXX : 875 to 1081   set up FM frequency to XXX  correct: OK\n / error: ERR\n
  BK3254::sendCOMData(BK3254_FM_TUNE_FREQ+(String)freq);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmGetFreq2() { //BK3254_FM_GET_FREQ2 "COM+MRFM" //Query current FM frequency (FM Mode)  correct: FM_FQ = xxx\n. xxx: 875-1081(87.5-108.1Mhz) / error: ERR\n ?? wht is diference to FM+GF ?
  BK3254::sendCOMData(BK3254_FM_GET_FREQ2);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmGetPreset() { //BK3254_FM_GET_PRESET "COM+MMFM" //Query currently selected preset (FM Mode)   correct: MFMxx \ n,xx: 01-99 / error: ERR\n
  BK3254::sendCOMData(BK3254_FM_GET_PRESET);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::fmGetFreqOfPreset(uint16_t preset) { //BK3254_FM_GET_FREQ_OF_PRESET "COM+MFFM" //MFFM+XX, Inquire FM of xx No. A frequency corresponding to (FM Mode)   correct: FM_FQ = xxx\n, error: ERR\n
  BK3254::sendCOMData(BK3254_FM_GET_FREQ_OF_PRESET+(String)preset);
  BK3254::getNextEventFromBT();
}

//Query / feedback commands

uint8_t BK3254::getAddress() { //BK3254_GET_ADDRESS "AT+MR" //Queries Bluetooth address   AD: 191919191919\r\n
  BK3254::sendData(BK3254_GET_ADDRESS);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::getPinCode() { //BK3254_GET_PIN_CODE "AT+MP" //PIN Code query  PN: 0000\r\n
  BK3254::sendData(BK3254_GET_PIN_CODE);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::getName() { //BK3254_GET_NAME "AT+MN" //Bluetooth name query  NA: BK3254\r\n
  BK3254::sendData(BK3254_GET_NAME);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::getConnectionSatus() { //BK3254_GET_CONNECTION_STATUS "AT+MO" //Bluetooth connection status inquiry   connection succeeded: C1\r\n / no connection: C0\r\n
  BK3254::sendData(BK3254_GET_CONNECTION_STATUS);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::getMusicGetStatus() { //BK3254_MUSIC_GET_STATUS "AT+MV" //Bluetooth playback status inquiry   Play: MB\r\n / time out: MA\r\n / disconnect: M0\r\n
  BK3254::sendData(BK3254_MUSIC_GET_STATUS);
  BK3254::getNextEventFromBT();
}

uint8_t BK3254::getHfpStatus() { //BK3254_GET_HFP_STATUS "AT+MY" //Bluetooth inquiry HFP status  disconnect: M0\r\n / connection: M1\r\n / Caller: M2\r\n / Outgoing: M3\r\n / calling: M4\r\n
  BK3254::sendData(BK3254_GET_HFP_STATUS);
  BK3254::getNextEventFromBT();
}

