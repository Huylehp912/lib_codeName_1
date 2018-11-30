/**@defgroup ERROR ERROR �������ģ��Ĵ���������ֵ��ͨ�ó������

@brief Errorģ���Ӧͷ�ļ�sdi2_error.h�������˸���ģ��Ĵ���������ֵ��ͨ��
�ɹ�����SDI_SUCCESS��ͨ�ó������SDI_FAILURE��û�нӿ���Ҫʵ�֡�

һ������£�SDI���еĺ��������ر�ģ�鶨���SDI_Error_Code���͵Ĵ������ֵ��
����������ֵ����������ɣ����16λΪģ����룬�ڱ�ģ���ж��壨������������
ֵ������16λΪ���������룬�ھ���ģ���ж��塣

@note ������ģ�鼰�ӿ��жԴ������ֵ��FEATURE_NOT_SUPPORTED��NO_MEMORY�Ƚ�����
�ر�˵��������������ֵ�����ڵ��ԣ�Eastwin�����ж������Ƿ�ɹ�����������ݴ�
�����ֵ������ͬ�ĺ���������
@version 2.0.1 2009/07/27 ����
@{
*/

#ifndef _SDI2_ERROR_H_
#define _SDI2_ERROR_H_

#include "sdi2_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SDI_SUCCESS   (0)     		///< ͨ�óɹ�����,����һ��ɹ����ø�ֵ��ʾ

#define WATCHDOG_DIS_INIT   0x10101010

#define SDI_FAILURE   (0xFFFFFFFF)    ///< һ��ʧ�ܴ���,δ����ĳ�������ʹ�ø�ֵ�������鷵��ʵ�ʵĴ������ֵ������Ӧ��ʹ�ø�ֵ

typedef SDI_UINT32    SDI_Error_Code;  ///< ƽ̨��������ֵ����

/**@brief ����ģ�����������ֵö�ٶ���

@note ÿ��ģ��Ĵ������ֵ��������ĸ������Ĵ����������:BAD_PARAMETER��NO_MEMORY,FEATURE_NOT_SUPPORTED,UNKNOWN_ERROR
*/
enum
{
	SDI_AOUT_ERROR_BASE			= 1 << 16,      ///< AOUTģ��Ĵ���������ֵ
	SDI_AUDIO_ERROR_BASE			= 2 << 16,		///< AUDIOģ��Ĵ���������ֵ
	SDI_VIDEO_ERROR_BASE			= 3 << 16,		///< VIDEOģ��Ĵ���������ֵ
	SDI_SCREEN_ERROR_BASE			= 4 << 16, 		///< SCREENģ��Ĵ���������ֵ
	SDI_DESCRAMBLE_ERROR_BASE		= 5 << 16,		///< DESCRAMBLEģ��Ĵ���������ֵ
	SDI_INJECT_ERROR_BASE			= 6 << 16,		///< INJECTERģ��Ĵ���������ֵ
	SDI_RECORD_ERROR_BASE			= 7 << 16,		///< RECORDģ��Ĵ���������ֵ
	SDI_OSG_ERROR_BASE			= 8 << 16,		///< OSGģ��Ĵ���������ֵ
	SDI_SECTION_ERROR_BASE		= 9 << 16,		///< SECTIONģ��Ĵ���������ֵ
	SDI_SMC_ERROR_BASE			= 10 << 16,		///< SMCģ��Ĵ���������ֵ
	SDI_OS_ERROR_BASE				= 11 << 16,		///< OSģ��Ĵ���������ֵ
	SDI_FS_ERROR_BASE				= 12 << 16,		///< FSģ��Ĵ���������ֵ
	SDI_PLAYER_ERROR_BASE			= 13 << 16,		///< PLAYERģ��Ĵ���������ֵ
	SDI_TUNER_ERROR_BASE			= 14 << 16,		///< TUNERģ��Ĵ���������ֵ
	SDI_FLASH_ERROR_BASE			= 15 << 16,		///< FLASHģ��Ĵ���������ֵ
	SDI_DEMUX_ERROR_BASE			= 16 << 16,		///< DEMUXģ��Ĵ���������ֵ
	SDI_EEPROM_ERROR_BASE			= 17 << 16,		///< EEPROMģ��Ĵ���������ֵ
	SDI_TOOLSET_ERROR_BASE		= 18 << 16,		///< TOOLSETģ��Ĵ���������ֵ
	SDI_PANEL_ERROR_BASE			= 19 << 16,		///< PANELģ��Ĵ���������ֵ
	SDI_INPUT_ERROR_BASE			= 20 << 16,		///< INPUTģ��Ĵ���������ֵ
	SDI_IPCFG_ERROR_BASE			= 21 << 16,		///< IPCFGģ��Ĵ���������ֵ
	SDI_OTA_ERROR_BASE			= 22 << 16,     ///< OTAģ��Ĵ���������ֵ
	SDI_EW200S_ERROR_BASE			= 23 << 16,		///< Eastwin200��������������ֵ
	
	SDI_MAX_ERROR_BASE							///< �߽�ֵ
};

#ifdef __cplusplus
}
#endif
/** @} */
#endif  //_SDI2_ERROR_H_

