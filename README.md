# IMPORTANT NOTE

take care what module you buy, where are version which did not have support for all features,read description of what you buy, for example here from aliexpress:

<img src="https://raw.githubusercontent.com/tomaskovacik/BK3254/master/bk3254_only_BT.png">


# Library for BK3254 based bluetooth audio module (F-6888)

Supported commands based on this datasheet translate by www.onlinedoctranslator.com:

https://github.com/tomaskovacik/kicad-library/blob/master/library/datasheet/F-6888_bk3254/BK3254_V1.2_HYT.zh-CN.en.pdf



## HOW TO INSTALL

Follow this link to arduino.cc: https://www.arduino.cc/en/Guide/Libraries#toc5

## SUPPORTED UART COMMANDS

|Serial command |Parameter Description | Instruction Description Function | Responce|
|---------------|----------------------|----------------------------------|---------|
|COM+SNAME+XXX\r\n |XXX: New name, max16chars | Modify the bluetooth name, take efect after restart of chip | correct: OK\n / error: ERR\n|
|BT+PR\r\n | | Pairing|
|BT+AC\r\n | | The last paired device connected (connect to last device?)|
|BT+DC\r\n | | Disconect|
|BT+CA\r\n | | Answare the call|
|BT+CJ\r\n | | To reject a call|
|BT+CE\r\n | | Hang up the phone|
|BT+CR\r\n | | Last number redial|
|COM+PP\r\n | | Music Play / Pause|
|COM+PN\r\n | | next track/ FM next station|
|COM+PV\r\n | | previous piece/ FM On one|
|COM+VP\r\n | | Volume Up|
|COM+VD\r\n | | Volume down|
|COM+VOLx\r\n | x: 0x00 - 0xAF | Set the volume | correct: VOLx\n / error: ERR\n|
|COM+MVOL\r\n | | Query current volume | correct: VOLx\n (x:0-15) / error: ERR\n|
|COM+PWD\r\n | | Shutdown|
|COM+PWDS\r\n | | Soft-Off|
|COM+PWOS\r\n | | Soft Power|
|COM+MC\r\n | | Switching to the next operating mode|
|COM+MBT\r\n | | Bluetooth mode|
|COM+MSD\r\n | | TF/SDcard Mode (if available)|
|COM+MAX\r\n | | AUX Mode (if available)|
|COM+MFM\r\n | | FM Mode (if available)|
|COM+MUD\r\n | | USB Disk mode (if available)|
|COM+IQ\r\n | | Query the current mode|
|COM+MPM0\r\n | | Repeat All Tracks (TF/USB disk mode) | correct: PLAY_ALL\n / error: ERR\n|
|COM+MPM1\r\n | | Single loop (TF/USB disk mode) | correct: PLAY_ONE\n / error: ERR\n|
|COM+MPMC\r\n | | The current inquiry MP3 Play Mode (TF/USB disk mode) | correct: PLAY_ALL\n / PLAY_ONE\n|
|COM+SMPXXXX\r\n | | Play selections (TF/USB disk mode) | XXXX: 0001-9999, 0001 Represents the 1 first|
|COM+MRMP3\r\n | | Query currently playing MP3 Song number | correct: music_mun = x\n , x: 1-9999 / error: ERR\n|
|COM+MMMP3\r\n | | Query current mode MP3 The number of songs (TF/USB disk mode) | correct: MMMPx\n,x: 1-1999 / error: ERR\n|
|COM+MRUSB\r\n | | Query currently playing USB Disc song number | correct: music_mun = x\n,x: 1-1999 / error: ERR\n|
|FM+SC\r\n | | FM start station search|
|FM+ST\r\n | | FM Stop station search|
|FM+GF\r\n | | Get the current radio frequency | FM_FQ = 875 ~ 1081|
|COM+SFMXX\r\n | | Select FM preset 01-99 | correct: FM_FQ = 998\n / error: ERR\n|
|COM+SETFMXXXX\r\n | XXX : 875 to 1081 | set up FM frequency to XXXX (0875-1080) | correct: OK\n / error: ERR\n|
|COM+MRFM\r\n | | Query current FM frequency (FM Mode) | correct: FM_FQ = xxx\n. xxx: 0875-1081(87.5-108.1Mhz) / error: ERR\n|
|COM+MMFM\r\n | | Query currently selected preset (FM Mode) | correct: MFMxx \ n,xx: 01-99 / error: ERR\n|
|COM+MFFMXX\r\n | | Inquire FM of xx No. A frequency corresponding to (FM Mode) | correct: FM_FQ = xxx\n, error: ERR\n|


## Query / feedback command

|Serial command | description | Bluetooth return information|
|---------------|-------------|-----------------------------|
|AT+MR\r\n | Queries Bluetooth address | AD: 191919191919\r\n|
|AT+MP\r\n | PIN Code query | PN: 0000\r\n|
|AT+MN\r\n | Bluetooth name query | NA: BK3254\r\n|
|AT+MO\r\n | Bluetooth connection status inquiry | connection succeeded: C1\r\n / no connection: C0\r\n|
|AT+MV\r\n | Bluetooth playback status inquiry | Play: MB\r\n / time out: MA\r\n / disconnect: M0\r\n|
|AT+MY\r\n | Bluetooth inquiry HFP status | disconnect: M0\r\n / connection: M1\r\n / Caller: M2\r\n / Outgoing: M3\r\n / calling: M4\r\n|


## BLUETOOTH STATE SEND BY MODULE

|Serial command | description|
|---------------|------------|
|ERROR\n | error|
|OK\n | |
|II\r\n | connection succeeded|
|IA\r\n | disconnect|
|PLAY_ALL\n | Repeat All Tracks (TF/SDcard Mode)|
|PLAY_ONE\n | Repeat One Track (TF/SDcard Mode)|
|VOLx\n | The current volume x level|
|FM_FQ = 1081\n | Tunner frequency|
|music_mun = x\n | Song number|
|IRx\n | Received key value by IR|
|SY_PO\n | Bluetooth turned on|
|ON\r\n | Bluetooth turned on|
|SY_PF\n | Bluetooth off|
|BT_AC\n | Bluetooth Even being back|
|BT_WP\n | Bluetooth In pairing state|
|BT_WC\n | Bluetooth connection is in wait state|
|BT_CN\n | Bluetooth connected|
|BT_PA\n | Bluetooth Now Playing|
|BT_IC\n | Bluetooth A call|
|BT_OC\n | Bluetooth Telephone shot|
|BT_EC\n | Bluetooth He is busy|
|SD_PA\n | SD Card playing status|
|SD_PU\n | SD Card is paused|
|UD_PA\n | U plate Playing status|
|UD_PU\n | U plate In a suspended state|
|FM_PA\n | FM You are listening state|
|FM_PU\r\n | FM In a suspended state|
|FM_SC\n | FM The state of being seized Taiwan|
|AX_PA\n | AUX Playing status|
|AX_PU\n | AUX In a suspended state|

