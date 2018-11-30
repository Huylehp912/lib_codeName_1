
#ifndef _SDI2_I2C_H
#define _SDI2_I2C_H

#include "sdi2_typedef.h"
#include "sdi2_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief I2C�豸�� */
typedef enum
{
    I2C_BLOCK0 = 0,
    I2C_BLOCK1,
    I2C_BLOCK2,
    I2C_BLOCK3,
    I2C_BLOCK4,
    I2C_BLOCK_MAX
}I2CBlockIndex_E;

/**@brief I2C���ߵ�ͨ���������Ͷ��� */
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
@brief ��һ��I2C�豸��
@param[in] param ����I2C�豸�����ԵĽṹ��ָ�룻
@param[out] handle ��I2C�豸�����ɵ�I2C�����
@return �ɹ�����0��ʧ�ܷ���-1��
*/
SDI_Error_Code SDII2COpen(I2COpenParam_S *param, SDI_HANDLE *handle);

 /**
@brief �ر�һ��I2C�豸��
@param[in] handle �򿪵�I2C�豸�����
@return �ɹ�����0��ʧ�ܷ���-1��
*/ 
SDI_Error_Code SDII2CClose(SDI_HANDLE handle);

 /**
@brief ͨ��I2C���ߴ��豸��ȡ���ݣ�
@param[in] handle I2C�豸�����
@param[in] devAddr I2C���豸��ַ��
@param[in] buf ���ն�ȡ�����ݵ�BUF���׵�ַָ�룻
@param[in] len ��ȡ���ݵĳ��ȣ�
@note ��Ҫ��ȡ�����ݳ��ȱ���С�ڵ���BUF�ĳ��ȣ�
@return �ɹ�����0��ʧ�ܷ���-1��
*/
SDI_Error_Code SDII2CRead(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *buf, SDI_INT32 len);

 /**
@brief ͨ��I2C�������豸д�����ݣ�
@param[in] handle I2C�豸�����
@param[in] devAddr I2C���豸��ַ��
@param[in] buf ��д�������BUFָ�룻
@param[in] len ��д������ݳ��ȣ�
@note ����len����С�ڵ���BUF�ĳ��ȣ�
@return �ɹ�����0��ʧ�ܷ���-1��
*/ 
SDI_Error_Code SDII2CWrite(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *buf, SDI_INT32 len);

 /**
@brief ͨ��I2C���ߴ��豸��ĳ���ض�λ�ö�ȡ���ݣ�
@param[in] handle I2C�豸�����
@param[in] devAddr I2C���豸��ַ��
@param[in] regAddr ���Ҫ��ȡ�����ݵ��豸��ƫ�Ƶ�ַָ�룻
@param[in] alen ���ƫ�Ƶ�ַ��BUF���ȣ�
@param[in] buf ���ն�ȡ�����ݵ�BUF���׵�ַָ�룻
@param[in] len ��ȡ���ݵĳ��ȣ�
@note ��Ҫ��ȡ�����ݳ��ȱ���С�ڵ���BUF�ĳ���, ʹ�ô˽ӿ��ڵ�һ�δ�����ɺ󲻴�STOP�źš���
@return �ɹ�����0��ʧ�ܷ���-1��
*/
SDI_Error_Code SDII2CReadWithRegAddr(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *regAddr, SDI_INT32 alen, SDI_UINT8 *buf, SDI_INT32 len);

 /**
@brief ͨ��I2C���ߴ��豸��ĳ���ض�λ�ÿ�ʼд�����ݣ�
@param[in] handle I2C�豸�����
@param[in] devAddr I2C���豸��ַ��
@param[in] regAddr ���Ҫд������ݵ��豸��ƫ�Ƶ�ַָ�룻
@param[in] alen ���ƫ�Ƶ�ַ��BUF���ȣ�
@param[in] buf ��Ŵ�д������ݵ�BUFָ�룻
@param[in] len ��д�����ݵĳ��ȣ�
@note ����len����С�ڵ���BUF�ĳ��ȣ�ʹ�ô˽ӿ��ڵ�һ�δ�����ɺ󲻴�STOP�źš���
@return �ɹ�����0��ʧ�ܷ���-1��
*/
SDI_Error_Code SDII2CWriteWithRegAddr(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *regAddr, SDI_INT32 alen, SDI_UINT8 *buf, SDI_INT32 len);

#ifdef __cplusplus
}
#endif

#endif //_SDI2_I2C_H