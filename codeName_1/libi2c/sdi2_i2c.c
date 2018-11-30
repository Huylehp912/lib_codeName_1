#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include "sdi2/sdi2_i2c.h"
#include <android/log.h>

#ifndef LOG_TAG
#define  LOG_TAG    "i2c_lib"
#endif

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define RW_BUF_MAXSIZE  256

/**@brief I2C设备句柄 */
typedef struct
{
    int32_t         dev;    /* 打开的I2C设备文件描述符 */
    I2CBlockIndex_E index;  /* I2C设备组索引 */
    I2COpenParam_S  param;  /* 打开的I2C设备属性 */
}I2CHandle_S;

SDI_Error_Code SDII2COpen(I2COpenParam_S *param, SDI_HANDLE *handle)
{
    SDI_INT32 ret = 0;
    SDI_UINT8 temp[16]={0};
    I2CHandle_S *i2c_handle = NULL;
    
    if(param == NULL)
    {
        LOGE("%s::%d:: Invalid param\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }

    i2c_handle = (I2CHandle_S *)malloc(sizeof(I2CHandle_S));
    if(i2c_handle == NULL)
    {
        LOGE("%s::%d::Malloc error.\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    memset(i2c_handle, 0, sizeof(I2CHandle_S));
    memcpy(&i2c_handle->param, param, sizeof(I2COpenParam_S));
    
    if(i2c_handle->param.BlockIndex >= I2C_BLOCK_MAX)
    {
        LOGE("%s::%d:: Invalid param\n", __FUNCTION__, __LINE__);
        goto err;
    }

    if((i2c_handle->param.I2CSpeed != I2C_SPEED_100K)&&(i2c_handle->param.I2CSpeed != I2C_SPEED_400K))
    {
        LOGE("Only 100kbps and 400kbps are supported in currentplatform.\n");
        LOGE("Select 100kbps as default speed.\n");
        i2c_handle->param.I2CSpeed = I2C_SPEED_100K;
    }

	#if 0 // modified by Ronny 
    if(i2c_handle->param.I2CSpeed == I2C_SPEED_400K)
    {
        i2c_handle->param.BlockIndex = I2C_BLOCK0;
    }
    
    if(i2c_handle->param.I2CSpeed == I2C_SPEED_100K)
    {
        i2c_handle->param.BlockIndex = I2C_BLOCK1;
    }
	#endif
    
    sprintf(temp, "/dev/i2c-%u", i2c_handle->param.BlockIndex);

    LOGE("open i2c device: %s\n", temp);
    
    i2c_handle->dev = -1;
    i2c_handle->dev = open((const char*)temp, O_RDWR);
    if(i2c_handle->dev < 0)
    {
        perror("I2C dev open");
        goto err;
    }

    if(i2c_handle->param.TimeOut > 0)
    {
        if(i2c_handle->param.TimeOut < 10) i2c_handle->param.TimeOut = 10;
        ret = ioctl(i2c_handle->dev, I2C_TIMEOUT, i2c_handle->param.TimeOut / 10);
        if(ret != 0)
        {
            LOGE("set timeout error, %ld\n", ret);
        }
    }

    *handle = (SDI_HANDLE *)i2c_handle;
    return SDI_SUCCESS;
    
err:
   if(i2c_handle->dev > 0)  close(i2c_handle->dev);
   if(i2c_handle != NULL)   free(i2c_handle);
   *handle = NULL;
   return SDI_FAILURE;  
}

SDI_Error_Code SDII2CClose(SDI_HANDLE handle)
{
    I2CHandle_S *i2c_handle = (I2CHandle_S *)handle;
    if((i2c_handle == NULL)||(i2c_handle->dev <= 0))
    {
        LOGE("%s::%d:: Invalid Handle\n", __FUNCTION__, __LINE__);
        return -1;
    }

    close(i2c_handle->dev);
    free(i2c_handle);

    return SDI_SUCCESS;
}

SDI_Error_Code SDII2CRead(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *buf, SDI_INT32 len)
{
    SDI_INT32 ret = 0;
    I2CHandle_S *i2c_handle = (I2CHandle_S *)handle;
    struct i2c_rdwr_ioctl_data data;
    
    if((i2c_handle == NULL)||(i2c_handle->dev <= 0))
    {
        LOGE("%s::%d:: Invalid Handle\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }

    if(buf == NULL)
    {
        LOGE("%s::%d:: Invalid param\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    
    memset(&data, 0, sizeof(struct i2c_rdwr_ioctl_data));

    data.nmsgs = 1;
    data.msgs  = (struct i2c_msg*)malloc(data.nmsgs * sizeof(struct i2c_msg));

    if(data.msgs == NULL)
    {
        LOGE("%s::%d:: Malloc error\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    memset(data.msgs, 0, (data.nmsgs * sizeof(struct i2c_msg)));

    data.msgs[0].flags = I2C_M_RD;
	data.msgs[0].addr  = devAddr >> 1;
    data.msgs[0].buf   = buf;
	data.msgs[0].len   = len;
    
    ret = ioctl(i2c_handle->dev, I2C_RDWR, (unsigned long)&data);
    
    if(ret < 0)
    {
        perror("ioctl");
        if(data.msgs)   free(data.msgs);
        return SDI_FAILURE;
    }
    else
    {
        if(data.msgs)   free(data.msgs);
        return SDI_SUCCESS;
    }
}

SDI_Error_Code SDII2CWrite(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *buf, SDI_INT32 len)
{
    SDI_INT32 ret = 0;
    I2CHandle_S *i2c_handle = (I2CHandle_S *)handle;
    struct i2c_rdwr_ioctl_data data;
    
    if((i2c_handle == NULL)||(i2c_handle->dev <= 0))
    {
        LOGE("%s::%d:: Invalid Handle\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }

    if(buf == NULL)
    {
        LOGE("%s::%d:: Invalid param\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    
    memset(&data, 0, sizeof(struct i2c_rdwr_ioctl_data));

    data.nmsgs = 1;
    data.msgs  = (struct i2c_msg*)malloc(data.nmsgs * sizeof(struct i2c_msg));

    if(data.msgs == NULL)
    {
        LOGE("%s::%d:: Malloc error\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    memset(data.msgs, 0, (data.nmsgs * sizeof(struct i2c_msg)));
   
    data.msgs[0].flags = 0;//I2C_M_NOSTART;
	data.msgs[0].addr  = devAddr >> 1;
    data.msgs[0].buf   = buf;
	data.msgs[0].len   = len;
	
    //LOGE("data.msgs[0].addr: 0x%02x\n", data.msgs[0].addr);
    //LOGE("data.msgs[0].buf[0]: 0x%02x(regaddr)\n", data.msgs[0].buf[0]);
    //LOGE("data.msgs[0].len: 0x%02x(length)\n", data.msgs[0].len);
    
    ret = ioctl(i2c_handle->dev, I2C_RDWR, (unsigned long)&data);
    if(ret < 0)
    {
        perror("ioctl");
        if(data.msgs)   free(data.msgs);
        return SDI_FAILURE;
    }

    if(data.msgs)   free(data.msgs);
    return SDI_SUCCESS;
}

SDI_Error_Code SDII2CReadWithRegAddr(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *regAddr, SDI_INT32 alen, SDI_UINT8 *buf, SDI_INT32 len)
{
    SDI_INT32 ret = 0;
    I2CHandle_S *i2c_handle = (I2CHandle_S *)handle;
    struct i2c_rdwr_ioctl_data data;
    
    if((i2c_handle == NULL)||(i2c_handle->dev <= 0))
    {
        LOGE("%s::%d:: Invalid Handle\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }

    if((regAddr == NULL)||(buf == NULL)||(alen < 0))
    {
        LOGE("%s::%d:: Invalid param\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    
    memset(&data, 0, sizeof(struct i2c_rdwr_ioctl_data));

    data.nmsgs = 2;
    data.msgs  = (struct i2c_msg*)malloc(data.nmsgs * sizeof(struct i2c_msg));

    if(data.msgs == NULL)
    {
        LOGE("%s::%d:: Malloc error\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    memset(data.msgs, 0, (data.nmsgs * sizeof(struct i2c_msg)));

    data.msgs[0].flags = 0;
	data.msgs[0].addr  = devAddr >> 1;
    data.msgs[0].buf   = regAddr;
	data.msgs[0].len   = alen;

    data.msgs[1].flags = I2C_M_RD;
	data.msgs[1].addr  = devAddr >> 1;
    data.msgs[1].buf   = buf;
	data.msgs[1].len   = len;

    //LOGE("data.msgs[1].buf[0] = 0x%02x, addr 0x%x\n", data.msgs[1].buf[0], data.msgs[1].buf);
    
    ret = ioctl(i2c_handle->dev, I2C_RDWR, (unsigned long)&data);

    //LOGE("data.msgs[1].buf[0] = 0x%02x, addr 0x%x\n", data.msgs[1].buf[0], data.msgs[1].buf);
    
    if(ret < 0)
    {
        perror("ioctl");
        if(data.msgs)   free(data.msgs);
        return SDI_FAILURE;
    }
    else
    {
        if(data.msgs)   free(data.msgs);
        return SDI_SUCCESS;
    }
    
}

SDI_Error_Code SDII2CWriteWithRegAddr(SDI_HANDLE handle, SDI_UINT8 devAddr, SDI_UINT8 *regAddr, SDI_INT32 alen, SDI_UINT8 *buf, SDI_INT32 len)
{
    SDI_INT32 ret = 0;
    I2CHandle_S *i2c_handle = (I2CHandle_S *)handle;
    struct i2c_rdwr_ioctl_data data;
    SDI_UINT8 wrbuf[RW_BUF_MAXSIZE] = {0};
    
    if((i2c_handle == NULL)||(i2c_handle->dev <= 0))
    {
        LOGE("%s::%d:: Invalid Handle\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }

    if((regAddr == NULL)||(buf == NULL)||(alen <= 0))
    {
        LOGE("%s::%d:: Invalid param\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    
    memset(&data, 0, sizeof(struct i2c_rdwr_ioctl_data));

    data.nmsgs = 1;
    data.msgs  = (struct i2c_msg*)malloc(data.nmsgs * sizeof(struct i2c_msg));

    if(data.msgs == NULL)
    {
        LOGE("%s::%d:: Malloc error\n", __FUNCTION__, __LINE__);
        return SDI_FAILURE;
    }
    memset(data.msgs, 0, (data.nmsgs * sizeof(struct i2c_msg)));

    memcpy(wrbuf,     regAddr, alen);
    memcpy(wrbuf+alen,    buf, len);
    
    data.msgs[0].flags = 0;//I2C_M_NOSTART;
	data.msgs[0].addr  = devAddr >> 1;
    data.msgs[0].buf   = wrbuf;
	data.msgs[0].len   = alen+len;
	
    //LOGE("data.msgs[0].addr: 0x%02x\n", data.msgs[0].addr);
    //LOGE("data.msgs[0].buf[0]: 0x%02x(regaddr)\n", data.msgs[0].buf[0]);
    //LOGE("data.msgs[0].len: 0x%02x(length)\n", data.msgs[0].len);
    
    ret = ioctl(i2c_handle->dev, I2C_RDWR, (unsigned long)&data);
    if(ret < 0)
    {
		LOGE("%s::%d:: Malloc error\n", __FUNCTION__, __LINE__);
        perror("ioctl");
        if(data.msgs)
		{
			free(data.msgs);
		}
		
        return SDI_FAILURE;
    }

    if(data.msgs)
	{
		free(data.msgs);
	}
	
    return SDI_SUCCESS;

}

