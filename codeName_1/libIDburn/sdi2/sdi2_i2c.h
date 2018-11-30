
#ifndef _SDI2_I2C_H
#define _SDI2_I2C_H

#include "sdi2_typedef.h"
#include "sdi2_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief I2C设备组 */
typedef enum
{
    I2C_BLOCK0 = 0,
    I2C_BLOCK1,
    I2C_BLOCK2,
    I2C_BLOCK3,
    I2C_BLOCK4,
    I2C_BLOCK_MAX
}I2CBlockIndex_E;

/**@brief I2C总线的通信速率类型定义 */
typedef enum
{
    I2C_SPEED_50K = 1,
    I2C_SPEED_100K,
    I2C_SPEED_200K,
    I2C_SPEED_300K,
    I2C_SPEED_400K,
    I2C_SPEED_MAX
}I2CSpeed_E;

typedef struct
{
    I2CBlockIndex_E   BlockIndex;
    I2CSpeed_E        I2CSpeed;
    SDI_INT32         TimeOut;  /*  Unit is ms  */
    SDI_INT8            BoadID;
}I2COpenParam_S;

 /**
@brief 打开一个I2C设备；
@param[in] param 描述I2C设备打开属性的结构体指针；
@param[out] handle 打开I2C设备后生成的I2C句柄；
@return 成功返回0；失败返回-1；
*/
SDI_Error_Code SDII2COpen(I2COpenParam_S *param, SDI_HANDLE *handle);

 /**
@brief 关闭一个I2C设备；
@param[in] handle 打开的I2C设备句柄；
@return 成功返回0；失败返回-1；
*/ 
SDI_Error_Code SDII2CClose(SDI_HANDLE handle);

 /**
@brief 通过I2C总线从设备读取数据；
@param[in] handle I2C设备句柄；
@param[in] devAddr I2C的设备地址；
@param[in] buf 接收读取的数据的BUF的首地址指针；
@param[in] len 读取数据的长度；
@note 需要读取的数据长度必须小于等于BUF的长度；
@return 成功返回0；失败返回-1；
*/
SDI_Error_Code SDII2CRead(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *buf, SDI_INT32 len);

 /**
@brief 通过I2C总线向设备写入数据；
@param[in] handle I2C设备句柄；
@param[in] devAddr I2C的设备地址；
@param[in] buf 待写入的数据BUF指针；
@param[in] len 待写入的数据长度；
@note 参数len必须小于等于BUF的长度；
@return 成功返回0；失败返回-1；
*/ 
SDI_Error_Code SDII2CWrite(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *buf, SDI_INT32 len);

 /**
@brief 通过I2C总线从设备的某个特定位置读取数据；
@param[in] handle I2C设备句柄；
@param[in] devAddr I2C的设备地址；
@param[in] regAddr 存放要读取的数据的设备内偏移地址指针；
@param[in] alen 存放偏移地址的BUF长度；
@param[in] buf 接收读取的数据的BUF的首地址指针；
@param[in] len 读取数据的长度；
@note 需要读取的数据长度必须小于等于BUF的长度, 使用此接口在第一次传输完成后不带STOP信号。；
@return 成功返回0；失败返回-1；
*/
SDI_Error_Code SDII2CReadWithRegAddr(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *regAddr, SDI_INT32 alen, SDI_UINT8 *buf, SDI_INT32 len);

 /**
@brief 通过I2C总线从设备的某个特定位置开始写入数据；
@param[in] handle I2C设备句柄；
@param[in] devAddr I2C的设备地址；
@param[in] regAddr 存放要写入的数据的设备内偏移地址指针；
@param[in] alen 存放偏移地址的BUF长度；
@param[in] buf 存放待写入的数据的BUF指针；
@param[in] len 待写入数据的长度；
@note 参数len必须小于等于BUF的长度，使用此接口在第一次传输完成后不带STOP信号。；
@return 成功返回0；失败返回-1；
*/
SDI_Error_Code SDII2CWriteWithRegAddr(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *regAddr, SDI_INT32 alen, SDI_UINT8 *buf, SDI_INT32 len);

#ifdef __cplusplus
}
#endif

#endif //_SDI2_I2C_H