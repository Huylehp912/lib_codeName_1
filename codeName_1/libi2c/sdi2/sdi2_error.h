/**@defgroup ERROR ERROR 定义各个模块的错误代码基本值及通用出错代码

@brief Error模块对应头文件sdi2_error.h，定义了各个模块的错误代码基本值、通用
成功代码SDI_SUCCESS及通用出错代码SDI_FAILURE，没有接口需要实现。

一般情况下，SDI所有的函数均返回本模块定义的SDI_Error_Code类型的错误代码值，
该类错误代码值由两部分组成，其高16位为模块代码，在本模块中定义（即错误代码基本
值）；低16位为具体错误代码，在具体模块中定义。

@note 除非在模块及接口中对错误代码值如FEATURE_NOT_SUPPORTED、NO_MEMORY等进行了
特别说明，否则错误代码值仅用于调试，Eastwin仅会判断其结果是否成功，而不会根据错
误代码值做出不同的后续操作。
@version 2.0.1 2009/07/27 初稿
@{
*/

#ifndef _SDI2_ERROR_H_
#define _SDI2_ERROR_H_

#include "sdi2_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SDI_SUCCESS   (0)     		///< 通用成功代码,所有一般成功均用该值表示

#define WATCHDOG_DIS_INIT   0x10101010

#define SDI_FAILURE   (0xFFFFFFFF)    ///< 一般失败代码,未定义的出错代码可使用该值，但建议返回实际的错误代码值，而不应该使用该值

typedef SDI_UINT32    SDI_Error_Code;  ///< 平台公共返回值类型

/**@brief 各个模块错误代码基本值枚举定义

@note 每个模块的错误代码值都会包含四个基本的错误代码类型:BAD_PARAMETER，NO_MEMORY,FEATURE_NOT_SUPPORTED,UNKNOWN_ERROR
*/
enum
{
	SDI_AOUT_ERROR_BASE			= 1 << 16,      ///< AOUT模块的错误代码基本值
	SDI_AUDIO_ERROR_BASE			= 2 << 16,		///< AUDIO模块的错误代码基本值
	SDI_VIDEO_ERROR_BASE			= 3 << 16,		///< VIDEO模块的错误代码基本值
	SDI_SCREEN_ERROR_BASE			= 4 << 16, 		///< SCREEN模块的错误代码基本值
	SDI_DESCRAMBLE_ERROR_BASE		= 5 << 16,		///< DESCRAMBLE模块的错误代码基本值
	SDI_INJECT_ERROR_BASE			= 6 << 16,		///< INJECTER模块的错误代码基本值
	SDI_RECORD_ERROR_BASE			= 7 << 16,		///< RECORD模块的错误代码基本值
	SDI_OSG_ERROR_BASE			= 8 << 16,		///< OSG模块的错误代码基本值
	SDI_SECTION_ERROR_BASE		= 9 << 16,		///< SECTION模块的错误代码基本值
	SDI_SMC_ERROR_BASE			= 10 << 16,		///< SMC模块的错误代码基本值
	SDI_OS_ERROR_BASE				= 11 << 16,		///< OS模块的错误代码基本值
	SDI_FS_ERROR_BASE				= 12 << 16,		///< FS模块的错误代码基本值
	SDI_PLAYER_ERROR_BASE			= 13 << 16,		///< PLAYER模块的错误代码基本值
	SDI_TUNER_ERROR_BASE			= 14 << 16,		///< TUNER模块的错误代码基本值
	SDI_FLASH_ERROR_BASE			= 15 << 16,		///< FLASH模块的错误代码基本值
	SDI_DEMUX_ERROR_BASE			= 16 << 16,		///< DEMUX模块的错误代码基本值
	SDI_EEPROM_ERROR_BASE			= 17 << 16,		///< EEPROM模块的错误代码基本值
	SDI_TOOLSET_ERROR_BASE		= 18 << 16,		///< TOOLSET模块的错误代码基本值
	SDI_PANEL_ERROR_BASE			= 19 << 16,		///< PANEL模块的错误代码基本值
	SDI_INPUT_ERROR_BASE			= 20 << 16,		///< INPUT模块的错误代码基本值
	SDI_IPCFG_ERROR_BASE			= 21 << 16,		///< IPCFG模块的错误代码基本值
	SDI_OTA_ERROR_BASE			= 22 << 16,     ///< OTA模块的错误代码基本值
	SDI_EW200S_ERROR_BASE			= 23 << 16,		///< Eastwin200服务层错误代码基本值
	
	SDI_MAX_ERROR_BASE							///< 边界值
};

#ifdef __cplusplus
}
#endif
/** @} */
#endif  //_SDI2_ERROR_H_

