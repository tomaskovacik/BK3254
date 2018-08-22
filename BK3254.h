/*
        GNU GPL v3
        (C) Tomas Kovacik [nail at nodomain dot sk]
        https://github.com/tomaskovacik/

        BK3254 module library

        supports SW and HW serial

        to enable SW serial set USE_SW_SERIAL to 1
        to enable debug output set DEBUG to 1, this is using HW Serial (hardcoded)

*/


#ifndef BK3254_h
#define BK3254_h
#include <Arduino.h>

#define USE_SW_SERIAL 1

#define DEBUG 1

// UART COMMANDS

#define BK3254_PAIRING "BT+PR" //Pairing   
#define BK3254_PAIRING_DEVICE "BT+AC" //The last paired device connected (connect to last device?)  
#define BK3254_DISCONNECT "BT+DC" //Disconect   
#define BK3254_CALL_ANSWARE "BT+CA" //Answare the call  
#define BK3254_CALL_REJECT "BT+CJ" //To reject a call  
#define BK3254_CALL_HANGUP "BT+CE" //Hang up the phone   
#define BK3254_CALL_REDIAL "BT+CR" //Last number redial  
#define BK3254_MUSIC_TOGGLE_PLAY_PAUSE "COM+PR" //Music Play / Pause  
#define BK3254_MUSIC_NEXT_TRACK "COM+PN" //next track/ FM next station   
#define BK3254_FM_NEXT_STATION "COM+PN" //next track/ FM next station   
#define BK3254_MUSIC_PREVIOUS_TRACK "COM+PV" //previous piece/ FM On one   
#define BK3254_FM_PREVIOUS_STATION "COM+PV" //previous piece/ FM On one   
#define BK3254_VOLUME_UP "COM+VP" //Volume Up   
#define BK3254_VOLUME_DOWN "COM+VD" //Volume down   
#define BK3254_VOLUME_SET "COM+VOL" //VOL+x: 0x00 - 0xAF  Set the volume  correct: VOLx\n / error: ERR\n
#define BK3254_VOLUME_GET_CURRENT "COM+MVOL" //Query current volume  correct: VOLx\n (x:0-15) / error: ERR\n
#define BK3254_SHUTDOWN "COM+PWD" //Shutdown  
#define BK3254_STANDBY "COM+PWDS" //Soft-Off  
#define BK3254_POWERUP "COM+PWOS" //Soft Power   ???
#define BK3254_INPUT_SWITCH "COM+MC" //Switching to the next operating mode  
#define BK3254_INPUT_BLUETOOTH "COM+MBT" //Bluetooth mode  
#define BK3254_INPUT_TF "COM+MSD" //TF/SDcard Mode (if available)   
#define BK3254_INPUT_AUX "COM+MAX" //AUX Mode (if available)   
#define BK3254_INPUT_FM "COM+MFM" //FM Mode (if available)  
#define BK3254_INPUT_USB "COM+MUD" //USB Disk mode (if available)  
#define BK3254_INPUT_GET_CURRENT "COM+IQ" //Query the current mode  
#define BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ALL "COM+MPM0" //Repeat All Tracks (TF/USB disk mode)  correct: PLAY_ALL\n / error: ERR\n
#define BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ONE "COM+MPM1" //Single loop (TF/USB disk mode)  correct: PLAY_ONE\n / error: ERR\n
#define BK3254_MUSIC_PLAYBACK_MODE_GET_CURRENT "COM+MPMC" //The current inquiry MP3 Play Mode (TF/USB disk mode)  correct: PLAY_ALL\n / PLAY_ONE\n
#define BK3254_MUSIC_PLAY_SONG_NUMBER "COM+SMP" //SMP+XXXX, Play selections (TF/USB disk mode)  XXXX: 0001-9999, 0001 Represents the 1 first
#define BK3254_TF_GET_SONG_NUMBER "COM+MRMP3" //Query currently playing MP3 Song number   correct: music_mun = x\n , x: 1-9999 / error: ERR\n ???
#define BK3254_TF_USB_GET_NUMBER_OF_SONGS "COM+MMMP3" //Query current mode MP3 The number of songs (TF/USB disk mode)   correct: MMMPx\n,x: 1-1999 / error: ERR\n
#define BK3254_USB_GET_SONG_NUMBER "COM+MRUSB" //Query currently playing USB Disc song number  correct: music_mun = x\n,x: 1-1999 / error: ERR\n
#define BK3254_FM_START_SEARCH "FM+SC" //FM start station search   
#define BK3254_FM_STOP_SEARCH "FM+ST" //FM Stop station search  
#define BK3254_FM_GET_FREQ "FM+GF" //Get the current radio frequency   FM_FQ = 875 ~ 1081
#define BK3254_FM_TUNE_PRESET "COM+SFM" //SFM+XX,Select FM preset 01-99  correct: FM_FQ = 998\n / error: ERR\n
#define BK3254_FM_TUNE_FREQ "COM+SETFM" //SETFM+XXX, XXX : 875 to 1081   set up FM frequency to XXX  correct: OK\n / error: ERR\n
#define BK3254_FM_GET_FREQ2 "COM+MRFM" //Query current FM frequency (FM Mode)  correct: FM_FQ = xxx\n. xxx: 875-1081(87.5-108.1Mhz) / error: ERR\n ?? wht is diference to FM+GF ?
#define BK3254_FM_GET_PRESET "COM+MMFM" //Query currently selected preset (FM Mode)   correct: MFMxx \ n,xx: 01-99 / error: ERR\n
#define BK3254_FM_GET_FREQ_OF_PRESET "COM+MFFM" //MFFM+XX, Inquire FM of xx No. A frequency corresponding to (FM Mode)   correct: FM_FQ = xxx\n, error: ERR\n

//Query / feedback commands

#define BK3254_GET_ADDRESS "AT+MR" //Queries Bluetooth address   AD: 191919191919\r\n
#define BK3254_GET_PIN_CODE "AT+MP" //PIN Code query  PN: 0000\r\n
#define BK3254_GET_NAME "AT+MN" //Bluetooth name query  NA: BK3254\r\n
#define BK3254_GET_CONNECTION_STATUS "AT+MO" //Bluetooth connection status inquiry   connection succeeded: C1\r\n / no connection: C0\r\n
#define BK3254_MUSIC_GET_STATUS "AT+MV" //Bluetooth playback status inquiry   Play: MB\r\n / time out: MA\r\n / disconnect: M0\r\n
#define BK3254_GET_HFP_STATUS "AT+MY" //Bluetooth inquiry HFP status  disconnect: M0\r\n / connection: M1\r\n / Caller: M2\r\n / Outgoing: M3\r\n / calling: M4\r\n

#if defined(USE_SW_SERIAL)
#if ARDUINO >= 100
#include <SoftwareSerial.h>
#else
#include <NewSoftSerial.h>
#endif
#endif


class BK3254
{
  public:

    enum STATES
    {
      Playing, //MA
      Idle, //MB
      IncomingCall, //IR- or M2
      OutgoingCall, //PR- or M3
      CallInProgress, //M4
      Connected, // M1
      Disconnected, //M0
      On,
      Off,
      Pairing,
      ShutdownInProgress
    };

    uint8_t BTState = Disconnected;
    uint8_t CallState = Disconnected;
    uint8_t MusicState = Idle;
    uint8_t PowerState = Off;

    String CallerID;
    String BT_ADDR;
    String BT_NAME;
    String BT_PIN;

#if defined(USE_SW_SERIAL)
#if ARDUINO >= 100
    BK3254(SoftwareSerial *ser, uint8_t resetPin);
#else
    BK3254(NewSoftSerial  *ser, uint8_t resetPin);
#endif
#else
    BK3254(HardwareSerial *ser, uint8_t resetPin);
#endif
    void begin(uint32_t baudrate = 9600);
    ~BK3254();
    uint8_t sendData(String cmd); //AT+
    uint8_t sendCOMData(String cmd); //COM+
    uint8_t sendFMData(String cmd); //FM+
    uint8_t sendBTData(String cmd); //BT+
    void resetModule();
    uint8_t getNextEventFromBT();
    uint8_t pairingInit();
    uint8_t connectLastDevice();
    uint8_t disconnect();
    uint8_t callAnsware();
    uint8_t callReject();
    uint8_t callHangUp();
    uint8_t callRedial();
    uint8_t musicTogglePlayPause();
    uint8_t musicNextTrack();
    uint8_t fmNextTrack();
    uint8_t musicPreviousTrack();
    uint8_t fmPreviousTrack();
    uint8_t volumeUp();
    uint8_t volumeDown();
    uint8_t volumeSet(uint8_t volume);
    uint8_t volumeGet();
    uint8_t shutdown();
    uint8_t standby();
    uint8_t powerup();
    uint8_t switchInput();
    uint8_t switchInputToBluetooth();
    uint8_t switchInputToCard();
    uint8_t switchInputToAux();
    uint8_t switchInputToFm();
    uint8_t switchInputToUsb();
    uint8_t getCurrentInput();
    uint8_t musicModeRepeatAll();
    uint8_t musicModeRepeatOne();
    uint8_t musicGetCurrentMode();
    uint8_t musicPlaySong(uint16_t number);
    uint8_t cardGetCurrentPlayingSongNumber();
    uint8_t cardUsbGetSongsCount();
    uint8_t usbGetCurrentPlayingSongNumber();
    uint8_t fmStartSearch();
    uint8_t fmStopSearch();
    uint8_t fmGetFreq();
    uint8_t fmTunePreset(uint8_t preset);
    uint8_t fmTuneFreq(uint16_t freq);
    uint8_t fmGetFreq2();
    uint8_t fmGetPreset();
    uint8_t fmGetFreqOfPreset(uint16_t preset);
    uint8_t getAddress();
    uint8_t getPinCode();
    uint8_t getName();
    uint8_t getConnectionSatus();
    uint8_t getMusicGetStatus();
    uint8_t getHfpStatus();
    
  private:
    uint8_t _reset;
    uint8_t decodeReceivedString(String receivedString);
    void DBG(String text);
    void resetHigh();
    void resetLow();

#if  defined(USE_SW_SERIAL)
#if ARDUINO >= 100
    SoftwareSerial *btSerial;
#else
    NewSoftSerial  *btSerial;
#endif
#else
    HardwareSerial *btSerial;
#endif

};
#endif

