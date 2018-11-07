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
//probably works only on v1.2
#define BK3254_CHANGE_NAME "SNAME+" //change name
#define BK3254_VOICES_ON "TONEON"
#define BK3254_VOICES_OFF "TONEOFF"
#define BK3254_GET_VOICES_STATE "MTONE"
#define BK3254_GOBACKON "GOBACKON"
#define BK3254_GOBACKOFF "GOBACKOFF"
#define BK3254_MGOBACK "MGOBACK"
#define BK3254_CALLON "CALLON"
#define BK3254_CALLOFF "CALLOFF"
#define BK3254_MCALL "MCALL"
#define BK3254_REBOOT "REBOOT"
//probably work only with V1.3 based on this: https://github.com/tomaskovacik/kicad-library/blob/master/library/datasheet/F-6888_bk3254/BK3254_V1.3_HYT.zh-CN.en.pdf
#define BK3254_SPIN "SPIN+"

//works with v1.1 for shure:
#define BK3254_PAIRING "PR" //Pairing   
#define BK3254_PAIRING_DEVICE "AC" //The last paired device connected (connect to last device?)  
#define BK3254_DISCONNECT "DC" //Disconect   
#define BK3254_CALL_ANSWARE "CA" //Answare the call  
#define BK3254_CALL_REJECT "CJ" //To reject a call  
#define BK3254_CALL_HANGUP "CE" //Hang up the phone   
#define BK3254_CALL_REDIAL "CR" //Last number redial  
#define BK3254_MUSIC_TOGGLE_PLAY_PAUSE "PP" //Music Play / Pause  
#define BK3254_MUSIC_NEXT_TRACK "PN" //next track/ FM next station   
#define BK3254_MUSIC_PREVIOUS_TRACK "PV" //previous piece/ FM On one   
#define BK3254_VOLUME_UP "VP" //Volume Up   
#define BK3254_VOLUME_DOWN "VD" //Volume down   
#define BK3254_VOLUME_SET "VOL" //VOL+x: 0x00 - 0xAF  Set the volume  correct: VOLx\n / error: ERR\n
#define BK3254_VOLUME_GET_CURRENT "MVOL" //Query current volume  correct: VOLx\n (x:0-15) / error: ERR\n
#define BK3254_SHUTDOWN "PWD" //Shutdown  
#define BK3254_STANDBY "PWDS" //Soft-Off  
#define BK3254_POWERUP "PWOS" //Soft Power   ???
#define BK3254_INPUT_SWITCH "MC" //Switching to the next operating mode  
#define BK3254_INPUT_BLUETOOTH "MBT" //Bluetooth mode  
#define BK3254_INPUT_TF "MSD" //TF/SDcard Mode (if available)   
#define BK3254_INPUT_AUX "MAX" //AUX Mode (if available)   
#define BK3254_INPUT_FM "MFM" //FM Mode (if available)  
#define BK3254_INPUT_USB "MUD" //USB Disk mode (if available)  
#define BK3254_INPUT_GET_CURRENT "IQ" //Query the current mode  
#define BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ALL "MPM0" //Repeat All Tracks (TF/USB disk mode)  correct: PLAY_ALL\n / error: ERR\n
#define BK3254_MUSIC_PLAYBACK_MODE_REPEAT_ONE "MPM1" //Single loop (TF/USB disk mode)  correct: PLAY_ONE\n / error: ERR\n
#define BK3254_MUSIC_PLAYBACK_MODE_GET_CURRENT "MPMC" //The current inquiry MP3 Play Mode (TF/USB disk mode)  correct: PLAY_ALL\n / PLAY_ONE\n
#define BK3254_MUSIC_PLAY_SONG_NUMBER "SMP" //SMP+XXXX, Play selections (TF/USB disk mode)  XXXX: 0001-9999, 0001 Represents the 1 first
#define BK3254_TF_GET_SONG_NUMBER "MRMP3" //Query currently playing MP3 Song number   correct: music_mun = x\n , x: 1-9999 / error: ERR\n ???
#define BK3254_TF_USB_GET_NUMBER_OF_SONGS "MMMP3" //Query current mode MP3 The number of songs (TF/USB disk mode)   correct: MMMPx\n,x: 1-1999 / error: ERR\n
#define BK3254_USB_GET_SONG_NUMBER "MRUSB" //Query currently playing USB Disc song number  correct: music_mun = x\n,x: 1-1999 / error: ERR\n
#define BK3254_FM_START_SEARCH "SC" //FM start station search   
#define BK3254_FM_STOP_SEARCH "ST" //FM Stop station search  
#define BK3254_FM_GET_FREQ "GF" //Get the current radio frequency   FM_FQ = 875 ~ 1081
#define BK3254_FM_TUNE_PRESET "SFM" //SFM+XX,Select FM preset 01-99  correct: FM_FQ = 998\n / error: ERR\n
#define BK3254_FM_TUNE_FREQ "SETFM" //SETFM+XXX, XXX : 875 to 1081   set up FM frequency to XXX  correct: OK\n / error: ERR\n
#define BK3254_FM_GET_FREQ2 "MRFM" //Query current FM frequency (FM Mode)  correct: FM_FQ = xxx\n. xxx: 875-1081(87.5-108.1Mhz) / error: ERR\n ?? wht is diference to FM+GF ?
#define BK3254_FM_GET_PRESET "MMFM" //Query currently selected preset (FM Mode)   correct: MFMxx \ n,xx: 01-99 / error: ERR\n
#define BK3254_FM_GET_FREQ_OF_PRESET "MFFM" //MFFM+XX, Inquire FM of xx No. A frequency corresponding to (FM Mode)   correct: FM_FQ = xxx\n, error: ERR\n

//Query / feedback commands

#define BK3254_GET_ADDRESS "MR" //Queries Bluetooth address   AD: 191919191919\r\n
#define BK3254_GET_PIN_CODE "MP" //PIN Code query  PN: 0000\r\n
#define BK3254_GET_NAME "MN" //Bluetooth name query  NA: BK3254\r\n
#define BK3254_GET_CONNECTION_STATUS "MO" //Bluetooth connection status inquiry   connection succeeded: C1\r\n / no connection: C0\r\n
#define BK3254_GET_MUSIC_STATUS "MV" //Bluetooth playback status inquiry   Play: MB\r\n / time out: MA\r\n / disconnect: M0\r\n
#define BK3254_GET_HFP_STATUS "MY" //Bluetooth inquiry HFP status  disconnect: M0\r\n / connection: M1\r\n / Caller: M2\r\n / Outgoing: M3\r\n / calling: M4\r\n

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
      Playing,             //0x00
      Idle,                //0x01
      IncomingCall,        //0x02
      OutgoingCall,        //0x03
      CallInProgress,      //0x04
      Connected,           //0x05
      Disconnected,        //0x06
      On,                  //0x07
      Off,                 //0x08
      Pairing,             //0x09
      ShutdownInProgress,  //0x0A
      BT,                  //0x0B
      AUX,                 //0x0C
      USB,                 //0x0D
      SD,                  //0x0E
      Connecting,          //0x0F
      Busy,                //0x10
      PlayAll,             //0x11
      PlayOne,             //0x12
      FM                   //0x13
    };

    uint16_t BTState = Disconnected;
    uint16_t CallState = Idle;
    uint16_t MusicState = Idle;
    uint16_t PowerState = Off;
    uint16_t InputSelected = BT;
    uint16_t MusicMode = PlayOne;
    uint16_t currentVolume=8;
    uint16_t NumberOfSongs=0;
    uint16_t CurrentlyPlayingSong;
    uint16_t CurrentFrequency = 0;
    uint8_t CurrentPreset = 0;
    
    String CallerID="";
    String BT_ADDR="";
    String BT_NAME="";
    String BT_PIN="";
    

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
    uint8_t volumeSet(String volume);
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
    uint8_t fmTunePreset(String preset);
    uint8_t fmTuneFreq(String freq);
    uint8_t fmGetFreq2();
    uint8_t fmGetPreset();
    uint8_t fmGetFreqOfPreset(String preset);
    uint8_t getAddress();
    uint8_t getPinCode();
    uint8_t getName();
    uint8_t getConnectionStatus();
    uint8_t getMusicStatus();
    uint8_t getHFPStatus();
    uint8_t changeName(String newName);
    uint8_t changePin(String newPin);
    //??
    // from F-6888_BK3254_product_information.zh_CN.rtf

    uint8_t voicesOn();
    uint8_t voicesOff();
    uint8_t getVoicesState();
    uint8_t goBackOn();
    uint8_t goBackOff();
    uint8_t getGoBack();
    uint8_t callOn();
    uint8_t callOff();
    uint8_t getCall();
    uint8_t reboot();

    //??
  private:
    uint8_t _reset;
    uint8_t decodeReceivedString(String receivedString);
    uint8_t decodeReceivedStringOld(String receivedString);
    void DBG(String text);
    void resetHigh();
    void resetLow();
    String returnCallerID(String receivedString);
    String returnBtModuleName(String receivedString);
    uint16_t returnFreq(String receivedString);

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

