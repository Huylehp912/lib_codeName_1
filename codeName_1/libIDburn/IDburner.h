/*
 *  Descripition: burn ID 
 *
 *  Copyright : SDMC Inc.      Jul 13, 2013
 *
 *  Created by Ronny <Ronny@nuedc.net.cn>
 */

#ifndef __IDBURNER_H__
#define __IDBURNER_H__

#define MAC_ADDR_START 0x04
#define MAC_ADDR_LENGTH 0x06

#define MAC2_ADDR_START 0x40

#ifdef NEW_SN_LENGTH
#define USER_DEVICE_ID_ADDR_START 0x0F
#define USER_DEVICE_ID_ADDR_LENGTH 0x19
#elif NEW_SN_LENGTH32
#define USER_DEVICE_ID_ADDR_START 0x0F
#define USER_DEVICE_ID_ADDR_LENGTH 0x20
#else
#define USER_DEVICE_ID_ADDR_START 0x10
#define USER_DEVICE_ID_ADDR_LENGTH 0x25
#endif

#define USER_PRIVATE_ID_ADDR_START 0x28
#define USER_PRIVATE_ID_ADDR_LENGTH 0x08

#define USER_HARDWARE_VERSION_ID_START 0x30
#define USER_HARDWARE_VERSION_ID_LENGTH 0x08

#define USER_TUNER_TYPE_ADDR_TYPE 0x39 //用于判断tuner的类型
#define USER_TUNER_TYPE_ADDR_LENGTH 1

#define ACTIVE_CODE_ADDR_START 0x50
#define ACTIVE_CODE_ADDR_LENGTH 0x10

#define DM2016_DEV_ADDR 0xa0

#define EEPROM_MAX_SIZE			0x98
#define EEPROM_DEVICE_ADDR		0xa0
#define EEPROM_WRITE_DELAY_MS	20
#define MAX_I2C_MSG 2


#define D_SUCCESS 0x0
#define WRITE_DATA_DELAY 20000

//~ #define __PLATFORM_MESSAGE__

#ifdef __PLATFORM_MESSAGE__
#define  LOG_TAG    "IDBURNER"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define DPrintf LOGE
#define DError LOGE
#define DInfo LOGI
#else
#define DPrintf printf
#define DError printf
#define DInfo printf
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/***********************************************
*** activeCode 16 byte
************************************************/
int readActivecode(char* activeCode);
int writeActivecode(char* activeCode);

/***********************************************
*** sn 8 byte 
************************************************/
int readSN(char* sn);
int writeSN(char* sn);

/***********************************************
*** chipId 8 byte 
************************************************/
int readChipID(char* chipId);
int writeChipID(char* chipId);

/***********************************************
***Function: write mac to hardware dm2016
***input:
***  data: in data buffer, 6Bytes, be sure it's clean
***return:
***  =0: on success
***  <0: on error
************************************************/
int writeMacAddr(const char *data);

/***********************************************
***Function: read mac from hardware dm2016
***input:
***  data: out data buffer,at least 6Bytes, be sure it's clean
***return:
***  =0: on success
***  <0: on error
************************************************/
int readMacAddr(char *data);

/***********************************************
***Function: write mac to hardware dm2016
***input:
***  data: in data buffer, 6Bytes, be sure it's clean
***return:
***  =0: on success
***  <0: on error
************************************************/
int writeMac2Addr(const char *data);

/***********************************************
***Function: read mac from hardware dm2016
***input:
***  data: out data buffer,at least 6Bytes, be sure it's clean
***return:
***  =0: on success
***  <0: on error
************************************************/
int readMac2Addr(char *data);

/***********************************************
***Function: read device id from hardware
***input:
***  data: out data buffer, at least 24Bytes, be sure it's clean
***return:
***  =0: on success
***  <0: on error
************************************************/
int readUserDeviceID(char *data);

/***********************************************
***Function: write device id to hardware
***input:
***  data: in data buffer, 24Bytes
***return:
***  =0: on success
***  <0: on error
************************************************/
int writeUserDeviceID(const char *data);

/***********************************************
***Function: read user private id to hardware
***input:
***  data: out data buffer, at least 8 Bytes
***return:
***  =0: on success
***  <0: on error
************************************************/
int readUserPrivateID(char *data);

/***********************************************
***Function: write user private id to hardware
***input:
***  data: in data buffer, 8 Bytes
***return:
***  =0: on success
***  <0: on error
************************************************/
int writeUserPrivateID(const char *data);

/***********************************************
***Function: read user hardware version id from hardware
***input:
***  data: out data buffer, at least 8 Bytes
***return:
***  =0: on success
***  <0: on error
************************************************/
int readUserHardwareVersionID(char *data);

/***********************************************
***Function: write user hardware version id to eeprom
***input:
***  data: in data buffer, 8 Bytes
***return:
***  =0: on success
***  <0: on error
************************************************/
int writeUserHardwareVersionID(const char *data);

/***********************************************
***Function: write RSA private key to hardware
***input:
***  keyPath: in ,key file full path, limit max 256 Bytes
***  macAddr: in ,mac addr string, fixed 6 Bytes
***return:
***  =0: on success
***  <0: on error
***notes:
************************************************/
int edsv_keyBurn(const char *keyPath, const char *macAddr);

/***********************************************
***Function: checking writed RSA private key on hardware
***input:
***  keyPath: in ,key file full path, limit max 256 Bytes
***  macAddr: in ,mac addr string, fixed 6 Bytes
***return:
***  =0: on success
***  <0: on error
***notes:
************************************************/
int edsv_keyCheck(const char *keyPath, const char *macAddr);

/***********************************************
***Function: test ddr and hardware on board
***input:
***  nCount: in ,test times
***return:
***  =0: on success
***  <0: on error
***  -1: test error
***  -2: no memery error
***notes:
************************************************/
int ddrTest(int nCount);

#ifdef  __cplusplus
}
#endif

#endif

